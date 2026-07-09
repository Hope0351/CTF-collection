const std = @import("std");
const cards = @import("cards.zig");
const util = @import("util.zig");
const game = @import("game.zig");
const server = @import("server.zig");

//

pub const GE = struct {
    game_state: *game.GameState,
    unresolved: [0x100]u64, // The stack for the vm (just a funky name)

    resources: *game.SetResources,

    active_card: ?*cards.Card,
    num_activations: u64,

    // Registers
    cursor: usize,
    unresolved_count: usize,

    //noinline
    pub fn get_unresolved(self: *GE, offset: u64) u64 {
        const v = self.unresolved[self.unresolved_count - offset];
        //std.log.info("get_unresolved: {d}: {d}", .{ self.unresolved_count, v });
        return v;
    }

    //noinline
    pub fn add_unresolved(self: *GE, value: u64) void {
        self.unresolved[self.unresolved_count] = value;
        self.unresolved_count += 1;
        //std.log.info("add_unresolved: {d}: {d}", .{ self.unresolved_count, value });
    }

    //noinline
    pub fn run_impl(self: *GE, bc: []u8) !bool {
        while (self.cursor < bc.len) {
            const op = bc[self.cursor];
            //std.log.info("op: {d}/{d} {c}", .{ self.cursor, bc.len, op });

            self.cursor += 1;
            if (op == 'M') {
                // Unconditional jump
                const next_pos = try util.bin_read_u64(bc, &self.cursor);
                self.cursor = next_pos;
                continue;
            }
            if (op == 'd') {
                // Conditional jump
                const next_pos = try util.bin_read_u64(bc, &self.cursor);
                const condition = self.get_unresolved(1);
                if (condition == 0) {
                    self.cursor = next_pos;
                    continue;
                }
            }

            if (op == 'P') {
                // Become persistent
                continue;
            }

            if (op == 'R') {
                // Reject
                return false;
            }

            if (op == 'r') {
                // Get resource value
                const resource_type_int = try util.bin_read_u64(bc, &self.cursor);
                const resource_type: cards.ResourceType = cards.ResourceType.from_int(resource_type_int);
                const value = self.resources.get_resource(resource_type).value;
                self.add_unresolved(value);
                continue;
            }

            if (op == 'C') {
                // Consume resource
                const resource_type_int = self.get_unresolved(1);
                const resource_type: cards.ResourceType = cards.ResourceType.from_int(resource_type_int);
                const resource_value = self.get_unresolved(2);

                const is_ok = self.resources.consume_resource_value(resource_type, @intCast(resource_value));
                if (!is_ok) {
                    return false;
                }

                continue;
            }

            if (op == 'p') {
                // Produce resource
                const resource_type_int = self.get_unresolved(1);
                const resource_type: cards.ResourceType = cards.ResourceType.from_int(resource_type_int);
                const resource_value = self.get_unresolved(2);

                self.resources.add_resource_value(resource_type, @intCast(resource_value));

                continue;
            }

            if (op == 's') {
                // Success
                return true;
            }

            if (op == 'a') {
                // Add
                const a = self.get_unresolved(1);
                const b = self.get_unresolved(2);

                const r = a + b;
                self.add_unresolved(r);
                continue;
            }

            if (op == 'N') {
                // Get number of activations
                self.add_unresolved(self.num_activations);
                continue;
            }

            if (op == 'm') {
                const m = self.get_unresolved(1);
                const v = self.get_unresolved(2);

                const r = m * v;
                self.add_unresolved(r);
                continue;
            }

            if (op == 'i') {
                const v = try util.bin_read_u64(bc, &self.cursor);
                self.add_unresolved(v);
                continue;
            }

            if (op == 'e') {
                // Equal
                const a = self.get_unresolved(1);
                const b = self.get_unresolved(2);

                if (a == b) {
                    self.add_unresolved(1);
                } else {
                    self.add_unresolved(0);
                }
                continue;
            }

            if (op == 'c') {
                // Compare
                const a = self.get_unresolved(1);
                const b = self.get_unresolved(2);

                if (a < b) {
                    self.add_unresolved(1);
                } else {
                    self.add_unresolved(0);
                }
                continue;
            }
            if (op == 'u') {
                // pop
                const v = try util.bin_read_u64(bc, &self.cursor);
                const v_16: u16 = @truncate(v);
                const v_i16: i16 = @intCast(v_16);
                var uc_i16: i16 = @intCast(self.unresolved_count);
                uc_i16 -= v_i16;
                const uc_i64: i64 = @intCast(uc_i16);

                self.unresolved_count = @intCast(uc_i64);
                continue;
            }
            if (op == 'z') {
                // Get amount of resource changed
                const v = try util.bin_read_u64(bc, &self.cursor);
                const resource_type: cards.ResourceType = cards.ResourceType.from_int(v);

                const start_v = self.game_state.get_resource_value(resource_type);
                const end_v = self.resources.get_resource(resource_type).value;

                const diff = end_v - start_v;
                self.add_unresolved(diff);
                continue;
            }
        }
        return true;
    }
};

//
//

pub export fn run(game_state: *game.GameState, resources: *game.SetResources, active_card: *cards.Card, num_activations: u64, error_: *error{ EOF, InvalidTag }!u64) bool {
    //std.log.info("INSIDE ENGINE BASE RUN", .{});

    var ge = GE{
        .game_state = game_state,
        .resources = resources,
        .active_card = active_card,
        .num_activations = num_activations,
        .cursor = 0,
        .unresolved = [_]u64{0} ** 0x100,
        .unresolved_count = 0,
    };

    var res = true;
    if (active_card.code != null) {
        res = ge.run_impl(active_card.code.?) catch |err| {
            error_.* = err;
            return false;
        };
    }

    return res;
}

pub export fn handle_request(serv: *server.GameServerRequestHandler, path: *const []const u8, card_manager: *cards.CardManager) callconv(.c) bool {
    _ = serv;
    _ = path;
    _ = card_manager;
    return false;
}
