const std = @import("std");
const builtin = @import("builtin");
const print = @import("std").debug.print;
const AtomicOrder = std.builtin.AtomicOrder;
const AtomicRmwOp = std.builtin.AtomicRmwOp;

const sram_base : u32 = 0x29000;

const Opcode = enum {
    unknown,
    nop,
    ldsptl,
    ldspth,

    addc_a,
    subc_a,
    izsn_a,
    dzsn_a,

    pcadd_a,
    not_a,
    neg_a,
    sr_a,
    sl_a,
    src_a,
    slc_a,
    swap_a,

    wdreset,

    pushaf,
    popaf,

    reset,
    stopsys,
    stopexe,

    ret,
    // mul is not available

    xor_io_a,
    mov_io_a,
    mov_a_io,

    stt16_m,
    ldt16_m,
    ixdm_m_a,
    idxm_a_m,

    ret_k,

    test_m,
    set_m,

    alu_mem_a,
    alu_mem,

    test_io,
    set_io,

    alu_imm,

    goto,
    call,
};

const MemoryType = enum {
    instruction,
    stack,
    data,
};

// based on https://free-pdk.github.io/instruction-sets/PDK13
const Instruction = packed union {
    raw : u13,
    misc: packed struct {
        opcode: u6,
        bits: u7,
    },
    io: packed struct {
        ioaddr: u5,
        c: u3,
        zeroed: u5, // this should always be zero
    },
    mem16: packed struct {
        modifier: u1,
        m: u4,
        opcode: u3,
        zeroed: u5, // this should always be zero
    },
    reta: packed struct {
        imm: u8,
        top: u5, // this should always be 1
    },
    bitops: packed struct {
        addr: u4,
        c: u1,
        bitpos: u3,
        modifier: u1,
        top: u4,
    },
    memopsa: packed struct {
        addr: u6,
        opcode: u4,
        top: u3, // this should always be 1
    },
    memops: packed struct {
        addr: u6,
        opcode: u4,
        top: u3, // this should always be 2
    },
    bitopsio: packed struct {
        ioaddr: u5,
        bitpos: u3,
        c: u2,
        top: u3, // this should always be 3
    },
    immopsa: packed struct {
        imm: u8,
        opcode: u3,
        top: u2, // this should always be 2
    },
    control: packed struct {
        k: u10,
        c: u1,
        top: u2, // this should always be 3
    },

    fn opcode(self: Instruction) Opcode {

        return switch(self.raw) {
            0 => { return Opcode.nop; },
            6 => { return Opcode.ldsptl; },
            7 => { return Opcode.ldspth; },

            0x10 => { return Opcode.addc_a; },
            0x11 => { return Opcode.subc_a; },
            0x12 => { return Opcode.izsn_a; },
            0x13 => { return Opcode.dzsn_a; },

            0x17 => { return Opcode.pcadd_a; },
            0x18 => { return Opcode.not_a; },
            0x19 => { return Opcode.neg_a; },
            0x1a => { return Opcode.sr_a; },
            0x1b => { return Opcode.sl_a; },
            0x1c => { return Opcode.src_a; },
            0x1d => { return Opcode.slc_a; },
            0x1e => { return Opcode.swap_a; },

            0x30 => { return Opcode.wdreset; },

            0x32 => { return Opcode.pushaf; },
            0x33 => { return Opcode.popaf; },

            0x35 => { return Opcode.reset; },
            0x36 => { return Opcode.stopsys; },
            0x37 => { return Opcode.stopexe; },

            0x3a => { return Opcode.ret; },

            else => {
                const top5 : u5 = @intCast((self.raw & 0x1f00) >> 8);
                switch (top5) {
                    0 => {
                        // hack: check c bits, which align w/ 16-bit memory 'opcode' value in a way that works
                        switch (self.io.c) {
                            0...2 => { return Opcode.unknown; },
                            3 => { return Opcode.xor_io_a; },
                            4 => { return Opcode.mov_io_a; },
                            5 => { return Opcode.mov_a_io; },
                            6 => {
                                if (self.mem16.modifier == 0) {
                                    return Opcode.stt16_m;
                                } else {
                                    return Opcode.ldt16_m;
                                }
                            },
                            7 => {
                                if (self.mem16.modifier == 0) {
                                    return Opcode.ixdm_m_a;
                                } else {
                                    return Opcode.idxm_a_m;
                                }
                            },
                        }
                    },
                    1 => { return Opcode.ret_k; },
                    2 => { return Opcode.test_m; },
                    3 => { return Opcode.set_m; },
                    4...7 => { return Opcode.alu_mem_a; },
                    8...0xb => { return Opcode.alu_mem; },
                    0xc...0xd => { return Opcode.test_io; },
                    0xe...0xf => { return Opcode.set_io; },
                    0x10...0x17 => { return Opcode.alu_imm; },
                    0x18...0x1b => { return Opcode.goto; },
                    0x1c...0x1f => { return Opcode.call; },
                }

            },
        };
    }
};

const GlobalState = packed struct {
    timer: u16,
    io: u32,
    readvalue: u32,
    address: u32,
    data: u32,
};
var globalstate: GlobalState = GlobalState{
    .timer = 0,
    .io = 0,
    .readvalue = 0,
    .address = 0,
    .data = 0,
};

const MMIOState = struct {
    status: u32,
    locked: bool,
    validated: bool,
    instructions: []u32,
    inst_offset_highest: u32,
};
var mmio_state: *MMIOState = undefined;

const CPUState = struct {
    idx : u32,
    instruction_pointer: u16,
    bit_pointer: u5,
    runnable: bool,

    accum: u8,
    accum_history: [128]u32,
    accum_history_idx: u7,

    stack_pointer: u16,

    // flags
    zero_flag: u1,
    carry_flag: u1,
    aux_carry_flag: u1,
    overflow_flag: u1,

    instructions: []u32
};

var cpu_states: [2]*CPUState = undefined;
var cpu_idx : u1 = 0;

const Transaction = packed struct {
    txid: u8,
    secure: u1,
    data: u32,
    srcid: u4,
    address: u18,
    is_read: u1,
};

var active_tick: bool = false;
var has_messages: bool = false;
var g_tick: i32 = -1;

const TxList = std.DoublyLinkedList(Transaction);
var recvqueue: TxList = TxList{};
var recv_mutex: std.Thread.Mutex = .{};
var ackqueue: TxList = TxList{};

var allocator : std.mem.Allocator = undefined;

var driver_pid: i32 = 0;
var self_id: u32 = 0;
var rand_tickid: u8 = 0;

fn sigqueue(pid: i32, sig: u32, tx: Transaction) u32 {
    const tx_as_u64: u64 = @bitCast(tx);
    var arg: std.posix.siginfo_t = .{
        .signo = @as(c_int, @intCast(sig)),
        .errno = 0,
        .code = -1, // SI_QUEUE,
        .fields = .{ 
            .common = .{
                .first = .{
                    .piduid = .{
                        .pid = std.os.linux.getpid(),
                        .uid = std.os.linux.getuid(),
                    }
                },
                .second = .{
                    .value = .{
                        .ptr = @as(*anyopaque, @ptrFromInt(tx_as_u64)),
                    },
                },
            },
            },
    };

    std.log.debug("going into sigqueue {d} {d} {}", .{ pid, sig, arg });
    return @intCast(std.os.linux.syscall3(std.os.linux.SYS.rt_sigqueueinfo, @intCast(pid), sig, @intFromPtr(&arg)));
}

fn flush_tx(tx: Transaction, skip_ack: bool) ?Transaction {
    std.log.debug("driver pid {d} issuing tx: {}", .{ driver_pid, tx });

    std.log.debug("id {d} tx {}", .{ self_id, tx });
    const ret = sigqueue(driver_pid, 34, tx);
    std.log.debug("sigqueue = {}", .{ret});
    if (ret != 0) {
        // if this fails we should just exit, we are fucked
        std.posix.exit(1);
    }

    if (skip_ack) return null;

    // wait up to 1s for a reply
    const NANOS_PER_SEC: u64 = 1000000000;
    const ONE_HUNDRETH_SEC: u64 = NANOS_PER_SEC / 100;
    const total_wait_time: u64 = 1 * NANOS_PER_SEC;
    var curr_wait_time: u64 = 0;

    while (curr_wait_time < total_wait_time) {
        if (ackqueue.len > 0) {
            const node = ackqueue.first.?.data;
            std.log.debug("node {}", .{node});
            if (node.txid == tx.txid) {
                std.log.debug("child {d} received ack for {}", .{ self_id, tx });
                return ackqueue.popFirst().?.data;
            }
        }
        std.time.sleep(ONE_HUNDRETH_SEC);
        curr_wait_time += ONE_HUNDRETH_SEC;
    }

    return null;
}

fn bus_read(addr: u32) u32 {
    const tx = Transaction{
        .txid = rand_tickid,
        .srcid = @intCast(self_id),
        .secure = 0,
        .is_read = 1,
        .address = @intCast((addr & 0xffffc) >> 2),
        .data = 0,
    };

    std.log.debug("issuing bus_read tx addr 0x{x}: {}", .{addr, tx});

    const reply = flush_tx(tx, false).?;
    return reply.data;
}

fn bus_write(addr: u32, value: u32) !void {
    const tx = Transaction{
        .txid = rand_tickid,
        .srcid = @intCast(self_id),
        .secure = 0,
        .is_read = 0,
        .address = @intCast((addr & 0xffffc) >> 2),
        .data = value,
    };

    std.log.debug("issuing bus_write tx: {}", .{tx});

    _ = flush_tx(tx, false);
}

fn bus_handler(sig_num: i32, siginfo: *const std.posix.siginfo_t, _: ?*anyopaque) callconv(.C) void {
    if (sig_num != 34) {
        std.posix.exit(1);
    }

    std.log.debug("id {d} rx {x}", .{ self_id, siginfo.fields.common.second.value.ptr });

    // lmao at the . . .
    const tx: Transaction = @bitCast(@intFromPtr(siginfo.fields.common.second.value.ptr));

    if (allocator.create(TxList.Node)) |node| {
        node.data = tx;
        if (tx.srcid == 0xf) {
            // this is an ack, so insert in ackqueue
            ackqueue.prepend(node);
        } else {
            recv_mutex.lock();
            recvqueue.prepend(node);
            recv_mutex.unlock();
            has_messages = true;
            const has_messagesptr: *bool = &has_messages;
            _ = @atomicStore(bool, has_messagesptr, true, AtomicOrder.seq_cst);
        }
    } else |_| {}
    
}

fn tick_handler(sig_num: c_int) callconv(.C) void {
    if (sig_num != 34+1) {
        std.posix.exit(1);
    }

    const tickptr: *i32 = &g_tick;
    _ = @atomicRmw(i32, tickptr, AtomicRmwOp.Add, 1, AtomicOrder.seq_cst);

    const active_tickptr: *bool = &active_tick;
    _ = @atomicStore(bool, active_tickptr, true, AtomicOrder.seq_cst);
}

fn bus_init() u32 {
    std.log.debug("pid {d} doing bus init from zig, is cpu", .{std.os.linux.getpid()});

    const bus_action = std.posix.Sigaction{
        .handler = .{ .sigaction = bus_handler },
        .mask = std.posix.empty_sigset,
        .flags = std.c.SA.SIGINFO,
    };

    std.posix.sigaction(34, &bus_action, null);

    const tick_action = std.posix.Sigaction{
        .handler = .{ .handler = tick_handler },
        .mask = std.posix.empty_sigset,
        .flags = 0,
    };
    std.posix.sigaction(34+1, &tick_action, null);

    // signal to the driver that we're ready to go
    std.posix.kill(driver_pid, 34+1) catch {
        std.log.debug("unable to signal driver pid, bailing", .{});
        std.posix.exit(1);
    };

    return 0;
}



fn do_validation() void {
    std.log.debug("entering do_validation", .{});
    // do validation of the instructions in our mmio state
    var ip : u16 = 0;
    var bitpos : u5 = 0;
    while((ip >> 2) < mmio_state.inst_offset_highest + 4) {

        // grab an instruction
        const base_val : u32 = mmio_state.instructions[ip >> 2];
        var aux_val : u32 = 0;

        if (((ip & 3) > 1) and (ip < 0xfff)) {
            // this could tear into the next instruction, so we need to issue two reads here
            aux_val = mmio_state.instructions[(ip >> 2) + 1];
        }

        var combined : u64 = @as(u64, @intCast(base_val)) + (@as(u64, @intCast(aux_val)) << 32);

        // shift right to compensate for our unaligned
        combined >>= (8 * (@as(u6, @intCast(ip & 3))));
        combined >>= bitpos;
        combined &= (1 << 13) - 1;
        const inst: Instruction = @bitCast(@as(u13, @intCast(combined)));

        std.log.debug("ip 0x{x} bitpos {d} instruction opc {} raw 0x{x} (combined: 0x{x})", .{ip, bitpos, inst.opcode(), inst.raw, combined});
        switch (inst.opcode()) {
            Opcode.xor_io_a, Opcode.mov_io_a, Opcode.test_io, Opcode.set_io => {
                // these are denied and do not validate
                std.log.debug("instruction disallowed, bailing", .{});
                mmio_state.status = 1;
                return;
            },
            else => {}
        }

        bitpos += 13;
        while (bitpos > 7) {
            bitpos -= 8;
            ip += 1;
        }
    }

    // if we reach here, we are validated
    mmio_state.validated = true;
    mmio_state.status = 2;

}

fn mmio_handler(is_read: bool, address: u32, data: u32) u32 {
    std.log.debug("mmio_handler(read: {}, address: 0x{x}, data: 0x{x})", .{ is_read, address, data });

    const REGISTER_BASE : u32 = 0x8000;
    const shortaddr = (address & 0xffff) - REGISTER_BASE;

    // we provide a simple interface here -- the point is not to have bugs in this surface,
    // but instead to enable bugs in the main cpu emulation to be hit
    switch(shortaddr) {
        0 => { // STATUS
            if (is_read) {
                return mmio_state.status | @as(u32, if (cpu_states[0].runnable) 0x10 else 0) | @as(u32, if (cpu_states[1].runnable) 0x100 else 0);
            }
        },
        4 => { // VALIDATED
            if (is_read) {
                return if (mmio_state.validated) 1 else 0;
            }
        },
        8 => { // LOCKED
            if (is_read) {
                return if (mmio_state.locked) 1 else 0;
            } else {
                mmio_state.locked = if (data > 0) true else false;
            }
        },
        0xc => { // DO_VALIDATION
            if (is_read) {
                return 0;
            } else {
                if (mmio_state.locked) {
                    do_validation();
                }
            }
        },
        0x10 => { // EXECUTE
            if (is_read) {
                return 0;
            } else {
                if (mmio_state.validated and mmio_state.status < 3) {
                    // we have validated bytecode -- insert it into cpu1, and then mark cpu1 as runnable
                    cpu_states[1].instructions = mmio_state.instructions;
                    cpu_states[1].runnable = true;
                    mmio_state.status = 3;
                }
            }
        },
        else => {
            if ((shortaddr >= 0x100) and (shortaddr < 0x300)) {
                const offset = (shortaddr - 0x100) >> 2;
                if (is_read) {
                    return cpu_states[1].accum_history[offset];
                }
            } else if ((shortaddr >= 0x1000) and (shortaddr < 0x2000)) {
                if (!mmio_state.validated and !mmio_state.locked) {
                    const offset = (shortaddr - 0x1000) >> 2;
                    if (is_read) {
                        // read the 4-byte instructions at this offset
                        return mmio_state.instructions[offset];
                    } else {
                        // we are attempting to write an instruction here
                        mmio_state.instructions[offset] = data;
                        if (offset > mmio_state.inst_offset_highest) {
                            mmio_state.inst_offset_highest = offset;
                        }
                    }
                }
            }
            // if in the range of 0x1000 to 0x2000, we can load these instructions into our program
            std.log.debug("got unknown mmio offset 0x{x}", .{shortaddr});
        }
    }
    return 0;
}

fn memory_read(addr: u32, typ: MemoryType) u32 {

    var target_address = addr * 4;
    if (typ == MemoryType.instruction) {
        // no adjustment
    } else if (typ == MemoryType.stack) {
        target_address = (addr * 4) + 0x1000;
    } else if (typ == MemoryType.data) {
        target_address = (addr * 4) + 0x2000;
    }

    // direct our read to the cache controller
    target_address = (target_address + 0x1000) | 0x30000;
    const result = bus_read(target_address);

    // this function performs a true memory read from cache
    std.log.debug("memory_read(0x{x}, type {}) = 0x{x}", .{addr * 4, typ, result});
    return result;
}

fn memory_write(addr: u32, typ: MemoryType, value: u8) !void {

    // read our data
    // this function performs a true memory read from cache
    std.log.debug("memory_write(0x{x}, type {}, 0x{x})", .{addr * 4, typ, value});

    var target_address = addr * 4;
    if (typ == MemoryType.instruction) {
        // no adjustment
    } else if (typ == MemoryType.stack) {
        target_address = (addr * 4) + 0x1000;
    } else if (typ == MemoryType.data) {
        target_address = (addr * 4) + 0x2000;
    }

    // direct our read to the cache controller
    target_address = (target_address + 0x1000) | 0x30000;
    try bus_write(target_address, @intCast(value));
}

fn io_read(addr: u5) u8 {
    std.log.debug("io_read(0x{x})", .{addr});
    switch(addr) {
        // trivial leaks
        0, 1, 2, 3, 4, 5, 6, 7 => {
            const offset : u6 = @as(u6, @intCast(addr)) * 8;
            return @as(u8, @truncate(@intFromPtr(&mmio_state.instructions) >> offset));
        },
        8, 9, 10, 11, 12, 13, 14, 15 => {
            const offset : u6 = @as(u6, @intCast(addr - 8)) * 8;
            return @as(u8, @truncate(@intFromPtr(&io_read) >> offset));
        },
        16, 17, 18, 19, 20, 21, 22, 23 => {
            const offset : u6 = @as(u6, @intCast(addr - 16)) * 8;
            return @as(u8, @truncate(@intFromPtr(&mmio_state) >> offset));
        },

        // main bus r/w
        24, 25, 26, 27, => {
            const offset : u5 = @as(u5, @intCast(addr - 24)) * 8;
            return @as(u8, @truncate(globalstate.readvalue >> offset));
        },
        else => {
            return 0;
        }
    }
    return 0;
}

fn io_write(addr: u7, value: u8) !void {
    std.log.debug("io_write(0x{x}, 0x{x})", .{addr, value});
    switch(addr) {
        // load addr for r/w
        0, 1, 2, 3, => {
            const offset : u5 = @as(u5, @truncate(addr)) * 8;
            globalstate.address &= ~(@as(u32, 0xff) << offset);
            globalstate.address |= (@as(u32, value) << offset);
        },
        // load data for r/w
        4, 5, 6, 7 => {
            const offset : u5 = @as(u5, @truncate(addr - 4)) * 8;
            globalstate.data &= ~(@as(u32, 0xff) << offset);
            globalstate.data |= (@as(u32, value) << offset);
        },

        // do read (0) or write (1)
        16 => {
            if (value == 0) {
                // do read
                globalstate.readvalue = bus_read(globalstate.address);
            } else {
                // do write
                try bus_write(globalstate.address, globalstate.data);
            }
        },

        // jump to start of buffer (BACKDOOR)
        17, => {
            const fptr: *const fn() void = @ptrCast(mmio_state.instructions);
            fptr();
        },
        else => {}
    }
}

fn increment_pc(curr_cpu: *CPUState) !void {
    curr_cpu.bit_pointer += 13;
    while (curr_cpu.bit_pointer > 7) {
        curr_cpu.bit_pointer -= 8;
        curr_cpu.instruction_pointer += 1;
    }
}

fn read_instruction(curr_cpu: *CPUState) Instruction {
    const ip = curr_cpu.instruction_pointer;

    if (ip >> 2 >= curr_cpu.instructions.len) {
        // we would have executed off the page -- return nop and set CPU not runnable
        curr_cpu.runnable = false;
        return Instruction{.raw = 0};
    }

    // grab an instruction
    const base_val : u32 = curr_cpu.instructions[ip >> 2];
    var aux_val : u32 = 0;

    if (((ip & 3) > 1) and (ip < 0xfff)) {
        // this could tear into the next instruction, so we need to issue two reads here
        aux_val = curr_cpu.instructions[(ip >> 2) + 1];
    }

    var combined : u64 = @as(u64, @intCast(base_val)) + (@as(u64, @intCast(aux_val)) << 32);

    // shift right to compensate for our unaligned
    combined >>= (8 * (@as(u6, @intCast(ip & 3))));
    combined >>= curr_cpu.bit_pointer;
    combined &= (1 << 13) - 1;
    const inst: Instruction = @bitCast(@as(u13, @intCast(combined)));

    try increment_pc(curr_cpu);

    return inst;
}

// ALU shared ops
fn alu_and(curr_cpu: *CPUState, accum: u8, value: u8) u8 {
    const result : u8 = accum & value;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_or(curr_cpu: *CPUState, accum: u8, value: u8) u8 {
    const result = accum | value;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_xor(curr_cpu: *CPUState, accum: u8, value: u8) u8 {
    const result : u8 = accum ^ value;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_not(curr_cpu: *CPUState, accum: u8) u8 {
    const result : u8 = ~accum;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_neg(curr_cpu: *CPUState, accum: u8) u8 {
    const result : u8 = ~(accum) + 1;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_sr(curr_cpu: *CPUState, accum: u8) u8 {
    curr_cpu.carry_flag = if (accum & 1 == 1) 1 else 0;
    const result : u8 = accum >> 1;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_sl(curr_cpu: *CPUState, accum: u8) u8 {
    curr_cpu.carry_flag = if (accum & 0x80 == 0x80) 1 else 0;
    const result : u8 = accum << 1;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_src(curr_cpu: *CPUState, accum: u8) u8 {
    const orig_carry : u8 = if (curr_cpu.carry_flag == 1) 0x80 else 0;
    curr_cpu.carry_flag = if (accum & 1 == 1) 1 else 0;
    const result : u8 = (accum >> 1) | orig_carry;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_slc(curr_cpu: *CPUState, accum: u8) u8 {
    const orig_carry : u8 = if (curr_cpu.carry_flag == 1) 1 else 0;
    curr_cpu.carry_flag = if (accum & 1 == 1) 1 else 0;
    const result : u8 = (curr_cpu.accum << 1) | orig_carry;
    curr_cpu.zero_flag = if (result > 0) 0 else 1;
    return result;
}

fn alu_add(curr_cpu: *CPUState, accum: u8, value: u8, carry: u1) u8 {
    const sum : u16 = @as(u16, @intCast(accum)) + @as(u16, @intCast(value)) + @as(u16, @intCast(carry));
    curr_cpu.carry_flag = if (sum > 0xff) 1 else 0;
    // TODO: aux carry
    // TODO: overflow
    curr_cpu.zero_flag = if (sum > 0) 0 else 1;
    return @intCast(sum & 0xff);
}

fn alu_sub(curr_cpu: *CPUState, accum: u8, value: u8, carry: u1) u8 {
    const sum : u16 = @as(u16, @intCast(accum)) - @as(u16, @intCast(value)) - @as(u16, @intCast(carry));
    curr_cpu.carry_flag = if (sum > 0xff) 1 else 0;
    // TODO: aux carry
    // TODO: overflow
    curr_cpu.zero_flag = if (sum > 0) 0 else 1;
    return @intCast(sum & 0xff);
}

fn save_accum(curr_cpu: *CPUState) void {
    curr_cpu.accum_history[curr_cpu.accum_history_idx] = curr_cpu.accum;
    curr_cpu.accum_history_idx +%= 1;
}

fn execute_instruction(curr_cpu: *CPUState, opcode: Opcode, instruction: Instruction) !void {
    switch (opcode) {
        Opcode.unknown => {},

        // nothing to do
        Opcode.nop => {},

        Opcode.ldsptl => {
            save_accum(curr_cpu);
            curr_cpu.accum = @intCast(memory_read(curr_cpu.stack_pointer, MemoryType.stack) & 0xff);
        },
        Opcode.ldspth => {
            save_accum(curr_cpu);
            curr_cpu.accum = @intCast(memory_read(curr_cpu.stack_pointer + 1, MemoryType.stack) & 0xff);
        },

        Opcode.addc_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_add(curr_cpu, curr_cpu.accum, 0, curr_cpu.carry_flag);
        },
        Opcode.subc_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_sub(curr_cpu, curr_cpu.accum, 0, curr_cpu.carry_flag);
        },

        Opcode.izsn_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_add(curr_cpu, curr_cpu.accum, 1, 0);
            if (curr_cpu.zero_flag == 1) {
                // skip next instruction
                try increment_pc(curr_cpu);
            }
        },
        Opcode.dzsn_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_sub(curr_cpu, curr_cpu.accum, 1, 0);
            if (curr_cpu.zero_flag == 1) {
                // skip next instruction
                try increment_pc(curr_cpu);
            }
        },

        Opcode.pcadd_a => {
            // BUG: this doesn't set bitpointer, which means you can break/bypass validation
            // by abusing unaligned instructions to get access to io_read/io_write
            curr_cpu.instruction_pointer += @intCast(curr_cpu.accum);
        },
        Opcode.not_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_not(curr_cpu, curr_cpu.accum);
        },
        Opcode.neg_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_neg(curr_cpu, curr_cpu.accum);
        },
        Opcode.sr_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_sr(curr_cpu, curr_cpu.accum);
        },
        Opcode.sl_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_sl(curr_cpu, curr_cpu.accum);
        },

        Opcode.src_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_src(curr_cpu, curr_cpu.accum);
        },
        Opcode.slc_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = alu_slc(curr_cpu, curr_cpu.accum);
        },
        Opcode.swap_a => {
            save_accum(curr_cpu);
            curr_cpu.accum = (curr_cpu.accum >> 4) | (curr_cpu.accum << 4);
        },

        Opcode.wdreset => {
            globalstate.timer = 0;
        },

        Opcode.pushaf => {
            try memory_write(curr_cpu.stack_pointer, MemoryType.stack, curr_cpu.accum);
            var combined_flags : u8 = @intCast(curr_cpu.zero_flag);
            combined_flags |= @as(u8, @intCast(curr_cpu.carry_flag)) << 1;
            combined_flags |= @as(u8, @intCast(curr_cpu.aux_carry_flag)) << 2;
            combined_flags |= @as(u8, @intCast(curr_cpu.overflow_flag)) << 3;
            try memory_write(curr_cpu.stack_pointer+1, MemoryType.stack, combined_flags);
            curr_cpu.stack_pointer += 2;
        },
        Opcode.popaf => {
            curr_cpu.stack_pointer -= 1;
            const combined_flags : u8 = @intCast(memory_read(curr_cpu.stack_pointer, MemoryType.stack) & 0xff);
            curr_cpu.overflow_flag = if (combined_flags & 0x8 > 0) 1 else 0;
            curr_cpu.aux_carry_flag = if (combined_flags & 0x4 > 0) 1 else 0;
            curr_cpu.carry_flag = if (combined_flags & 0x2 > 0) 1 else 0;
            curr_cpu.zero_flag = if (combined_flags & 0x1 > 0) 1 else 0;

            curr_cpu.stack_pointer -= 1;
            save_accum(curr_cpu);
            curr_cpu.accum = @intCast(memory_read(curr_cpu.stack_pointer, MemoryType.stack) & 0xff);
        },
        // if reset, just stop running this cpu
        Opcode.reset, Opcode.stopsys, Opcode.stopexe => { curr_cpu.runnable = false; },

        Opcode.ret => {
            curr_cpu.stack_pointer -= 3;
            curr_cpu.instruction_pointer = @intCast(memory_read(curr_cpu.stack_pointer, MemoryType.stack) & 0xff);
            curr_cpu.instruction_pointer |= @intCast(memory_read(curr_cpu.stack_pointer+1, MemoryType.stack) << 8);
            curr_cpu.bit_pointer = @intCast(memory_read(curr_cpu.stack_pointer+2, MemoryType.stack) & 0xff);
        },

        Opcode.xor_io_a => {
            try io_write(instruction.io.ioaddr, io_read(instruction.io.ioaddr) ^ curr_cpu.accum);
        },
        Opcode.mov_io_a => {
            try io_write(instruction.io.ioaddr, curr_cpu.accum);
        },
        Opcode.mov_a_io => {
            save_accum(curr_cpu);
            curr_cpu.accum = io_read(instruction.io.ioaddr);
        },

        // i don't really care about these memory ones frankly
        Opcode.stt16_m, Opcode.ldt16_m, Opcode.ixdm_m_a, Opcode.idxm_a_m => {},

        Opcode.ret_k => {
            save_accum(curr_cpu);
            curr_cpu.accum = instruction.reta.imm;
            curr_cpu.stack_pointer -= 3;
            curr_cpu.instruction_pointer = @intCast(memory_read(curr_cpu.stack_pointer, MemoryType.stack) & 0xff);
            curr_cpu.instruction_pointer |= @intCast(memory_read(curr_cpu.stack_pointer+1, MemoryType.stack) << 8);
            curr_cpu.bit_pointer = @intCast(memory_read(curr_cpu.stack_pointer+2, MemoryType.stack) & 0xff);
        },

        Opcode.test_m => {
            const val : u8 = @intCast(memory_read(@intCast(instruction.bitops.addr), MemoryType.data) & 0xff);
            if ((val & (@as(u8, 1) << instruction.bitops.bitpos)) == instruction.bitops.c) {
                // skip next instruction by incrementing an extra time here
                try increment_pc(curr_cpu);
            }
        },
        Opcode.set_m => {
            var val : u8 = @intCast(memory_read(@intCast(instruction.bitops.addr), MemoryType.data) & 0xff);
            if (instruction.bitops.c == 1) {
                val |= (@as(u8, 1) << instruction.bitops.bitpos);
            } else {
                val &= ~(@as(u8, @intCast(@as(u8, 1) << instruction.bitops.bitpos)));
            }
            try memory_write(@intCast(instruction.bitops.addr), MemoryType.data, val);
        },

        Opcode.alu_mem_a => {
            // all opcodes besides 7 require a read from memory
            const input_data: u8 = if (instruction.memopsa.opcode == 7) 0 else @intCast(memory_read(instruction.memopsa.addr, MemoryType.data) & 0xff);
            switch (instruction.memopsa.opcode) {
                // add M, A
                0 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_add(curr_cpu, curr_cpu.accum, input_data, 0));
                },
                // sub M, A
                1 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sub(curr_cpu, curr_cpu.accum, input_data, 0));
                },
                // addc M, A
                2 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_add(curr_cpu, curr_cpu.accum, input_data, curr_cpu.carry_flag));
                },
                // subc M, A
                3 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sub(curr_cpu, curr_cpu.accum, input_data, curr_cpu.carry_flag));
                },
                // and M, A
                4 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_and(curr_cpu, curr_cpu.accum, input_data));
                },
                // or M, A
                5 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_or(curr_cpu, curr_cpu.accum, input_data));
                },
                // xor M, A
                6 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_xor(curr_cpu, curr_cpu.accum, input_data));
                },
                // mov M, A
                7 => try memory_write(@intCast(instruction.memopsa.addr), MemoryType.data, @intCast(curr_cpu.accum & 0xff)),
                // add A, M
                8 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_add(curr_cpu, curr_cpu.accum, input_data, 0);
                },
                // sub A, M
                9 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_sub(curr_cpu, curr_cpu.accum, input_data, 0);
                },
                // addc A, M
                10 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_add(curr_cpu, curr_cpu.accum, input_data, curr_cpu.carry_flag);
                },
                // subc A, M
                11 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_sub(curr_cpu, curr_cpu.accum, input_data, curr_cpu.carry_flag);
                },
                // and A, M
                12 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_and(curr_cpu, curr_cpu.accum, input_data);
                },
                // or A, M
                13 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_or(curr_cpu, curr_cpu.accum, input_data);
                },
                // xor A, M
                14 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_xor(curr_cpu, curr_cpu.accum, input_data);
                },
                // mov A, M
                15 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = input_data;
                },
            }
        },
        Opcode.alu_mem => {
            const input_data: u8 = @intCast(memory_read(instruction.memops.addr, MemoryType.data) & 0xff);
            switch (instruction.memopsa.opcode) {
                // addc M
                0 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_add(curr_cpu, 0, input_data, curr_cpu.carry_flag));
                },
                // subc M
                1 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sub(curr_cpu, input_data, 0, curr_cpu.carry_flag));
                },
                // izsn M
                2 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_add(curr_cpu, input_data, 1, 0));
                    if (curr_cpu.zero_flag == 1) {
                        // skip next instruction
                        try increment_pc(curr_cpu);
                    }
                },
                // dzsn M
                3 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sub(curr_cpu, input_data, 1, 0));
                    if (curr_cpu.zero_flag == 1) {
                        // skip next instruction
                        try increment_pc(curr_cpu);
                    }
                },
                // inc M
                4 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_add(curr_cpu, input_data, 1, 0));
                },
                // dec M
                5 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sub(curr_cpu, input_data, 1, 0));
                },
                // clear M
                6 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, 0);
                },
                // xch M
                7 => {
                    try memory_write(@intCast(instruction.memopsa.addr), MemoryType.data, curr_cpu.accum);
                    save_accum(curr_cpu);
                    curr_cpu.accum = input_data;
                },
                // not M
                8 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_not(curr_cpu, input_data));
                },
                // neg M
                9 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_neg(curr_cpu, input_data));
                },
                // sr M
                10 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sr(curr_cpu, input_data));
                },
                // sl M
                11 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_sl(curr_cpu, input_data));
                },
                // src M
                12 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_src(curr_cpu, input_data));
                },
                // slc M
                13 => {
                    try memory_write(instruction.memopsa.addr, MemoryType.data, alu_slc(curr_cpu, input_data));
                },
                // ceqsn A, M
                14 => {
                    _ = alu_sub(curr_cpu, curr_cpu.accum, input_data, 0);
                    if (curr_cpu.zero_flag == 1) {
                        // skip next instruction
                        try increment_pc(curr_cpu);
                    }
                },
                // invalid
                15 => {},
            }
        },

        Opcode.test_io => {
            const val = io_read(@intCast(instruction.bitops.addr)) & 0xff;
            if ((val & (@as(u8, 1) << instruction.bitops.bitpos)) == instruction.bitops.c) {
                // skip next instruction by incrementing an extra time here
                try increment_pc(curr_cpu);
            }
        },
        Opcode.set_io => {
            var val = io_read(@intCast(instruction.bitops.addr)) & 0xff;
            if (instruction.bitops.c == 1) {
                val |= (@as(u8, 1) << instruction.bitops.bitpos);
            } else {
                val &= ~(@as(u8, @intCast(@as(u8, 1) << instruction.bitops.bitpos)));
            }
            try io_write(@intCast(instruction.bitops.addr), val);
        },

        Opcode.alu_imm => {
            const val = instruction.immopsa.imm;
            switch (instruction.immopsa.opcode) {
                // add A, k
                0 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_add(curr_cpu, curr_cpu.accum, val, 0);
                },
                // sub A, k
                1 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_sub(curr_cpu, curr_cpu.accum, val, 0);
                },
                // ceqsn A, k
                2 => {
                    _ = alu_add(curr_cpu, curr_cpu.accum, val, 0);
                    if (curr_cpu.zero_flag == 1) {
                        // skip next instruction
                        try increment_pc(curr_cpu);
                    }
                },
                // invalid
                3 => {},
                // and A, k
                4 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_and(curr_cpu, curr_cpu.accum, val);
                },
                // or A, k
                5 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_or(curr_cpu, curr_cpu.accum, val);
                },
                // xor A, k
                6 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = alu_xor(curr_cpu, curr_cpu.accum, val);
                },
                // mov A, k
                7 => {
                    save_accum(curr_cpu);
                    curr_cpu.accum = val;
                },
            }
        },

        Opcode.goto, Opcode.call => {
            if (instruction.control.c == 1) {
                // this is a call, so push our pc to the stack
                try memory_write(curr_cpu.stack_pointer, MemoryType.stack, @intCast(curr_cpu.instruction_pointer & 0xff));
                try memory_write(curr_cpu.stack_pointer+1, MemoryType.stack, @intCast(curr_cpu.instruction_pointer >> 8));
                try memory_write(curr_cpu.stack_pointer+2, MemoryType.stack, @intCast(curr_cpu.bit_pointer));
                curr_cpu.stack_pointer += 3;
            }

            // we can calculate the new dest by resetting our pc/bitpos and incrementing back to the intended
            curr_cpu.instruction_pointer = 0;
            curr_cpu.bit_pointer = 0;
            for(0..instruction.control.k) |_| {
                try increment_pc(curr_cpu);
            }
        },
    }
}

fn init_cpustates() !void {
    // create our cpus
    cpu_states[0] = try allocator.create(CPUState);
    cpu_states[0].* = std.mem.zeroInit(CPUState, .{});
    cpu_states[1] = try allocator.create(CPUState);
    cpu_states[1].* = std.mem.zeroInit(CPUState, .{});

    // set initial CPU state stuff
    cpu_states[0].idx = 0;
    cpu_states[0].instruction_pointer = 0;
    cpu_states[0].stack_pointer = 0;
    cpu_states[0].runnable = true;
    cpu_states[0].instructions = @ptrCast(try std.posix.mmap(
        null,
        0x4000,
        std.posix.PROT.READ | std.posix.PROT.WRITE | std.posix.PROT.EXEC,
        std.posix.MAP{.TYPE = .PRIVATE, .ANONYMOUS = true},
        -1,
        0
    ));

    // .pdk13

    // ; we are going to do fibonacci

    // mov a, 1
    // mov [1], a
    // mov [2], a

    // mov a, 0xff
    // call fibonacci
    // reset

    // fibonacci:
    // ; a is the number of iterations of it we should do
    // mov [0], a

    // ; load count of how many left
    // loopstart:
    // call do_add
    // mov a, [0]
    // dzsn a
    // goto blah ; this is skipped when we finish
    // mov a, [2]
    // ret
    // blah:
    // mov [0], a ; go to here when we want to continue
    // goto loopstart

    // ; core of fibonacci add
    // do_add:
    // mov a, [1]
    // add a, [2]
    // xch [2]
    // mov [1], a
    // ret
    cpu_states[0].instructions[0] = 0x8b83701;
    cpu_states[0].instructions[1] = 0xc06bff97;
    cpu_states[0].instructions[2] = 0x7970006b;
    cpu_states[0].instructions[3] = 0x267c0e0;
    cpu_states[0].instructions[4] = 0xa3e16034;
    cpu_states[0].instructions[5] = 0x1cb8003;
    cpu_states[0].instructions[6] = 0x46023e0e;
    cpu_states[0].instructions[7] = 0x1d170538;

    cpu_states[1].idx = 1;
    cpu_states[1].instruction_pointer = 0;
    cpu_states[1].stack_pointer = 0;
    cpu_states[1].runnable = false;
}

fn cpu_step() !void {

    // we perform alternating executions here
    // on each tick, we execute one instruction from one cpu
    // afterwards, we alternate to the other CPU state. in this way
    // the CPU states share IO but have different registers

    // select next cpu state
    const curr_cpu = cpu_states[cpu_idx];
    if (curr_cpu.runnable) {
        // read next instruction from pc
        const inst : Instruction = read_instruction(curr_cpu);

        // parse instruction
        const opcode = inst.opcode();
        std.log.debug("cpu[{d}] instruction opc {} ip 0x{x} bit {d} accum 0x{x} sp 0x{x} ZF={d} CF={d} ACF={d} OF={d}",
            .{cpu_idx, opcode, curr_cpu.instruction_pointer, curr_cpu.bit_pointer,
                curr_cpu.accum, curr_cpu.stack_pointer, curr_cpu.zero_flag, curr_cpu.carry_flag, curr_cpu.aux_carry_flag, curr_cpu.overflow_flag,
            });

        // execute instruction
        try execute_instruction(curr_cpu, opcode, inst);
    }
    // we are lazy, so just treat every instruction as one cycle
    globalstate.timer +%= 1;
    cpu_idx +%= 1;
}

fn lockdown(insert_pid: i32) !void {
    // apply our seccomp filter
    var filter = if (builtin.target.cpu.arch == .x86_64)
        [_]u8{32,0,0,0,4,0,0,0,21,0,0,25,62,0,0,192,32,0,0,0,0,0,0,0,53,0,23,0,0,0,0,64,21,0,23,0,1,0,0,0,21,0,22,0,0,0,0,0,21,0,21,0,60,0,0,0,21,0,20,0,231,0,0,0,21,0,19,0,102,0,0,0,21,0,18,0,39,0,0,0,21,0,17,0,13,0,0,0,21,0,16,0,15,0,0,0,21,0,15,0,12,0,0,0,21,0,14,0,9,0,0,0,21,0,13,0,11,0,0,0,21,0,12,0,25,0,0,0,21,0,11,0,219,0,0,0,21,0,10,0,230,0,0,0,21,0,2,0,129,0,0,0,21,0,1,0,62,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,16,0,0,0,21,0,0,4,55,19,55,19,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127}
    else
        [_]u8{32,0,0,0,4,0,0,0,21,0,0,25,183,0,0,192,32,0,0,0,0,0,0,0,53,0,23,0,0,0,0,64,21,0,23,0,64,0,0,0,21,0,22,0,63,0,0,0,21,0,21,0,93,0,0,0,21,0,20,0,94,0,0,0,21,0,19,0,174,0,0,0,21,0,18,0,172,0,0,0,21,0,17,0,134,0,0,0,21,0,16,0,139,0,0,0,21,0,15,0,214,0,0,0,21,0,14,0,222,0,0,0,21,0,13,0,215,0,0,0,21,0,12,0,216,0,0,0,21,0,11,0,128,0,0,0,21,0,10,0,115,0,0,0,21,0,2,0,138,0,0,0,21,0,1,0,129,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,16,0,0,0,21,0,0,4,55,19,55,19,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127};

    var int_as_bytes = [_]u8{0, 0, 0, 0};
    std.mem.writePackedIntNative(i32, &int_as_bytes, 0, insert_pid);

    // insert our driver pid
    _ = std.mem.replace(u8, &filter, "\x37\x13\x37\x13", &int_as_bytes, &filter);

    const Prog = extern struct {
        len: u16,
        filter: u64,
    };
    const rule = Prog {
        .len = filter.len >> 3,
        .filter = @intFromPtr(&filter),
    };

    var ret = std.posix.prctl(std.posix.PR.SET_NO_NEW_PRIVS, .{1, 0, 0, 0}) catch {
        std.log.debug("no new privs error", .{});
        std.posix.exit(1);
    };
    if (ret != 0) {
        std.log.debug("no new privs error {d}", .{ret});
        std.posix.exit(1);
    }
    // std.os.linux.seccomp.MODE.FILTER = 2
    ret = std.posix.prctl(std.posix.PR.SET_SECCOMP, .{2, @intFromPtr(&rule)}) catch {
        std.log.debug("set seccomp error", .{});
        std.posix.exit(1);
    };
    if (ret != 0) {
        std.log.debug("set seccomp error {d}", .{ret});
        std.posix.exit(1);
    }
}

pub fn main() !void {

    self_id = try std.fmt.parseInt(u32, std.posix.getenv("ID").?, 10);
    driver_pid = try std.fmt.parseInt(i32, std.posix.getenv("D").?, 10);
    rand_tickid = try std.fmt.parseInt(u8, std.posix.getenv("T").?, 10);

    var buffer: [0x8000]u8 = undefined;
    var fba = std.heap.FixedBufferAllocator.init(&buffer);
    allocator = fba.allocator();

    mmio_state = try allocator.create(MMIOState);
    mmio_state.* = std.mem.zeroInit(MMIOState, .{});
    mmio_state.instructions = @ptrCast(try std.posix.mmap(
        null,
        0x4000,
        std.posix.PROT.READ | std.posix.PROT.WRITE | std.posix.PROT.EXEC,
        std.posix.MAP{.TYPE = .PRIVATE, .ANONYMOUS = true},
        -1,
        0
    ));

    try init_cpustates();

    _ = bus_init();
    // try lockdown(driver_pid);

    std.log.debug("pid: {d} using rand tickid {x}", .{std.os.linux.getpid(), rand_tickid});

    while (true) {
        if (@atomicLoad(bool, &has_messages, AtomicOrder.seq_cst)) {
            var qlen = recvqueue.len;

            // process all packets
            while (qlen > 0) {
                std.log.debug("child {d} processing packet on tick {d}", .{ self_id, g_tick });

                recv_mutex.lock();
                const node = recvqueue.pop().?;
                var tx = node.data;
                defer allocator.destroy(node);
                qlen = recvqueue.len;
                recv_mutex.unlock();
                std.log.debug("popped tx {}", .{tx});
                std.log.debug("child {d} received {s} for 0x{x} 0x{x}", .{ self_id, if (tx.is_read == 1) "READ" else "WRITE", tx.address, tx.data });
                const result = mmio_handler(tx.is_read == 1, @as(u32, tx.address) << 2, tx.data);

                tx.data = result;
                tx.address = @as(u18, tx.srcid) << 14;
                tx.srcid = 0xf;

                _ = flush_tx(tx, true);
            }
            const has_messagesptr: *bool = &has_messages;
            _ = @atomicStore(bool, has_messagesptr, false, AtomicOrder.seq_cst);
        }
        
        try cpu_step();
    }
}
