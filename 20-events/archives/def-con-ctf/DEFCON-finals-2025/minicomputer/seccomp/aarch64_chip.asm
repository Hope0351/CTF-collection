# check if arch is good
A = arch
A == ARCH_AARCH64 ? next : dead
A = sys_number
A >= 0x40000000 ? dead : next
A == write ? ok : next
A == read ? ok : next
A == exit ? ok : next
A == exit_group ? ok : next
A == getuid ? ok : next
A == getpid ? ok : next
A == rt_sigaction ? ok : next
A == rt_sigreturn ? ok : next
A == brk ? ok : next
A == mmap ? ok : next
A == munmap ? ok : next
A == mremap ? ok : next
A == restart_syscall ? ok : next
A == clock_nanosleep ? ok : next
A == rt_sigqueueinfo ? checksig : next
A == kill ? checksig : next
return KILL
checksig:
A = args[0]
A == 0x13371337 ? next : dead
A = args[1]
A == 34 ? ok : next
A == 35 ? ok : next
return KILL
dead:
return KILL
ok:
return ALLOW