/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD: src/sys/compat/svr4/syscalls.master,v 1.15 2004/02/06 20:07:33 jhb Exp 
 */

const char *svr4_syscallnames[] = {
	"#0",			/* 0 = unused */
	"exit",			/* 1 = exit */
	"fork",			/* 2 = fork */
	"read",			/* 3 = read */
	"write",			/* 4 = write */
	"svr4_sys_open",			/* 5 = svr4_sys_open */
	"close",			/* 6 = close */
	"svr4_sys_wait",			/* 7 = svr4_sys_wait */
	"svr4_sys_creat",			/* 8 = svr4_sys_creat */
	"link",			/* 9 = link */
	"unlink",			/* 10 = unlink */
	"svr4_sys_execv",			/* 11 = svr4_sys_execv */
	"chdir",			/* 12 = chdir */
	"svr4_sys_time",			/* 13 = svr4_sys_time */
	"svr4_sys_mknod",			/* 14 = svr4_sys_mknod */
	"chmod",			/* 15 = chmod */
	"chown",			/* 16 = chown */
	"svr4_sys_break",			/* 17 = svr4_sys_break */
	"svr4_sys_stat",			/* 18 = svr4_sys_stat */
	"lseek",			/* 19 = lseek */
	"getpid",			/* 20 = getpid */
	"#21",			/* 21 = old_mount */
	"#22",			/* 22 = sysv_umount */
	"setuid",			/* 23 = setuid */
	"getuid",			/* 24 = getuid */
	"#25",			/* 25 = stime */
	"#26",			/* 26 = ptrace */
	"svr4_sys_alarm",			/* 27 = svr4_sys_alarm */
	"svr4_sys_fstat",			/* 28 = svr4_sys_fstat */
	"svr4_sys_pause",			/* 29 = svr4_sys_pause */
	"svr4_sys_utime",			/* 30 = svr4_sys_utime */
	"#31",			/* 31 = stty */
	"#32",			/* 32 = gtty */
	"svr4_sys_access",			/* 33 = svr4_sys_access */
	"svr4_sys_nice",			/* 34 = svr4_sys_nice */
	"#35",			/* 35 = statfs */
	"sync",			/* 36 = sync */
	"svr4_sys_kill",			/* 37 = svr4_sys_kill */
	"#38",			/* 38 = fstatfs */
	"svr4_sys_pgrpsys",			/* 39 = svr4_sys_pgrpsys */
	"#40",			/* 40 = xenix */
	"dup",			/* 41 = dup */
	"pipe",			/* 42 = pipe */
	"svr4_sys_times",			/* 43 = svr4_sys_times */
	"#44",			/* 44 = profil */
	"#45",			/* 45 = plock */
	"setgid",			/* 46 = setgid */
	"getgid",			/* 47 = getgid */
	"svr4_sys_signal",			/* 48 = svr4_sys_signal */
#if defined(NOTYET)
	"svr4_sys_msgsys",			/* 49 = svr4_sys_msgsys */
#else
	"#49",			/* 49 = msgsys */
#endif
	"svr4_sys_sysarch",			/* 50 = svr4_sys_sysarch */
	"#51",			/* 51 = acct */
	"#52",			/* 52 = shmsys */
	"#53",			/* 53 = semsys */
	"svr4_sys_ioctl",			/* 54 = svr4_sys_ioctl */
	"#55",			/* 55 = uadmin */
	"#56",			/* 56 = exch */
	"svr4_sys_utssys",			/* 57 = svr4_sys_utssys */
	"fsync",			/* 58 = fsync */
	"svr4_sys_execve",			/* 59 = svr4_sys_execve */
	"umask",			/* 60 = umask */
	"chroot",			/* 61 = chroot */
	"svr4_sys_fcntl",			/* 62 = svr4_sys_fcntl */
	"svr4_sys_ulimit",			/* 63 = svr4_sys_ulimit */
	"#64",			/* 64 = reserved */
	"#65",			/* 65 = reserved */
	"#66",			/* 66 = reserved */
	"#67",			/* 67 = reserved */
	"#68",			/* 68 = reserved */
	"#69",			/* 69 = reserved */
	"#70",			/* 70 = advfs */
	"#71",			/* 71 = unadvfs */
	"#72",			/* 72 = rmount */
	"#73",			/* 73 = rumount */
	"#74",			/* 74 = rfstart */
	"#75",			/* 75 = sigret */
	"#76",			/* 76 = rdebug */
	"#77",			/* 77 = rfstop */
	"#78",			/* 78 = rfsys */
	"rmdir",			/* 79 = rmdir */
	"mkdir",			/* 80 = mkdir */
	"svr4_sys_getdents",			/* 81 = svr4_sys_getdents */
	"#82",			/* 82 = libattach */
	"#83",			/* 83 = libdetach */
	"#84",			/* 84 = sysfs */
	"svr4_sys_getmsg",			/* 85 = svr4_sys_getmsg */
	"svr4_sys_putmsg",			/* 86 = svr4_sys_putmsg */
	"svr4_sys_poll",			/* 87 = svr4_sys_poll */
	"svr4_sys_lstat",			/* 88 = svr4_sys_lstat */
	"symlink",			/* 89 = symlink */
	"readlink",			/* 90 = readlink */
	"getgroups",			/* 91 = getgroups */
	"setgroups",			/* 92 = setgroups */
	"fchmod",			/* 93 = fchmod */
	"fchown",			/* 94 = fchown */
	"svr4_sys_sigprocmask",			/* 95 = svr4_sys_sigprocmask */
	"svr4_sys_sigsuspend",			/* 96 = svr4_sys_sigsuspend */
	"svr4_sys_sigaltstack",			/* 97 = svr4_sys_sigaltstack */
	"svr4_sys_sigaction",			/* 98 = svr4_sys_sigaction */
	"svr4_sys_sigpending",			/* 99 = svr4_sys_sigpending */
	"svr4_sys_context",			/* 100 = svr4_sys_context */
	"#101",			/* 101 = evsys */
	"#102",			/* 102 = evtrapret */
	"svr4_sys_statvfs",			/* 103 = svr4_sys_statvfs */
	"svr4_sys_fstatvfs",			/* 104 = svr4_sys_fstatvfs */
	"#105",			/* 105 = whoknows */
	"#106",			/* 106 = nfssvc */
	"svr4_sys_waitsys",			/* 107 = svr4_sys_waitsys */
	"#108",			/* 108 = sigsendsys */
	"svr4_sys_hrtsys",			/* 109 = svr4_sys_hrtsys */
	"#110",			/* 110 = acancel */
	"#111",			/* 111 = async */
	"#112",			/* 112 = priocntlsys */
	"svr4_sys_pathconf",			/* 113 = svr4_sys_pathconf */
	"#114",			/* 114 = mincore */
	"svr4_sys_mmap",			/* 115 = svr4_sys_mmap */
	"mprotect",			/* 116 = mprotect */
	"munmap",			/* 117 = munmap */
	"svr4_sys_fpathconf",			/* 118 = svr4_sys_fpathconf */
	"vfork",			/* 119 = vfork */
	"fchdir",			/* 120 = fchdir */
	"readv",			/* 121 = readv */
	"writev",			/* 122 = writev */
	"svr4_sys_xstat",			/* 123 = svr4_sys_xstat */
	"svr4_sys_lxstat",			/* 124 = svr4_sys_lxstat */
	"svr4_sys_fxstat",			/* 125 = svr4_sys_fxstat */
	"svr4_sys_xmknod",			/* 126 = svr4_sys_xmknod */
	"#127",			/* 127 = clocal */
	"svr4_sys_setrlimit",			/* 128 = svr4_sys_setrlimit */
	"svr4_sys_getrlimit",			/* 129 = svr4_sys_getrlimit */
	"lchown",			/* 130 = lchown */
	"svr4_sys_memcntl",			/* 131 = svr4_sys_memcntl */
	"#132",			/* 132 = getpmsg */
	"#133",			/* 133 = putpmsg */
	"rename",			/* 134 = rename */
	"svr4_sys_uname",			/* 135 = svr4_sys_uname */
	"setegid",			/* 136 = setegid */
	"svr4_sys_sysconfig",			/* 137 = svr4_sys_sysconfig */
	"adjtime",			/* 138 = adjtime */
	"svr4_sys_systeminfo",			/* 139 = svr4_sys_systeminfo */
	"#140",			/* 140 = notused */
	"seteuid",			/* 141 = seteuid */
	"#142",			/* 142 = vtrace */
	"#143",			/* 143 = { */
	"#144",			/* 144 = sigtimedwait */
	"#145",			/* 145 = lwp_info */
	"#146",			/* 146 = yield */
	"#147",			/* 147 = lwp_sema_wait */
	"#148",			/* 148 = lwp_sema_post */
	"#149",			/* 149 = lwp_sema_trywait */
	"#150",			/* 150 = notused */
	"#151",			/* 151 = notused */
	"#152",			/* 152 = modctl */
	"svr4_sys_fchroot",			/* 153 = svr4_sys_fchroot */
	"svr4_sys_utimes",			/* 154 = svr4_sys_utimes */
	"svr4_sys_vhangup",			/* 155 = svr4_sys_vhangup */
	"svr4_sys_gettimeofday",			/* 156 = svr4_sys_gettimeofday */
	"getitimer",			/* 157 = getitimer */
	"setitimer",			/* 158 = setitimer */
	"#159",			/* 159 = lwp_create */
	"#160",			/* 160 = lwp_exit */
	"#161",			/* 161 = lwp_suspend */
	"#162",			/* 162 = lwp_continue */
	"#163",			/* 163 = lwp_kill */
	"#164",			/* 164 = lwp_self */
	"#165",			/* 165 = lwp_getprivate */
	"#166",			/* 166 = lwp_setprivate */
	"#167",			/* 167 = lwp_wait */
	"#168",			/* 168 = lwp_mutex_unlock */
	"#169",			/* 169 = lwp_mutex_lock */
	"#170",			/* 170 = lwp_cond_wait */
	"#171",			/* 171 = lwp_cond_signal */
	"#172",			/* 172 = lwp_cond_broadcast */
	"#173",			/* 173 = { */
	"#174",			/* 174 = { */
	"svr4_sys_llseek",			/* 175 = svr4_sys_llseek */
	"#176",			/* 176 = inst_sync */
	"#177",			/* 177 = whoknows */
	"#178",			/* 178 = kaio */
	"#179",			/* 179 = whoknows */
	"#180",			/* 180 = whoknows */
	"#181",			/* 181 = whoknows */
	"#182",			/* 182 = whoknows */
	"#183",			/* 183 = whoknows */
	"#184",			/* 184 = tsolsys */
	"svr4_sys_acl",			/* 185 = svr4_sys_acl */
	"svr4_sys_auditsys",			/* 186 = svr4_sys_auditsys */
	"#187",			/* 187 = processor_bind */
	"#188",			/* 188 = processor_info */
	"#189",			/* 189 = p_online */
	"#190",			/* 190 = sigqueue */
	"#191",			/* 191 = clock_gettime */
	"#192",			/* 192 = clock_settime */
	"#193",			/* 193 = clock_getres */
	"#194",			/* 194 = timer_create */
	"#195",			/* 195 = timer_delete */
	"#196",			/* 196 = timer_settime */
	"#197",			/* 197 = timer_gettime */
	"#198",			/* 198 = timer_overrun */
	"nanosleep",			/* 199 = nanosleep */
	"svr4_sys_facl",			/* 200 = svr4_sys_facl */
	"#201",			/* 201 = door */
	"setreuid",			/* 202 = setreuid */
	"setregid",			/* 203 = setregid */
	"#204",			/* 204 = install_utrap */
	"#205",			/* 205 = signotify */
	"#206",			/* 206 = schedctl */
	"#207",			/* 207 = pset */
	"#208",			/* 208 = whoknows */
	"svr4_sys_resolvepath",			/* 209 = svr4_sys_resolvepath */
	"#210",			/* 210 = signotifywait */
	"#211",			/* 211 = lwp_sigredirect */
	"#212",			/* 212 = lwp_alarm */
	"svr4_sys_getdents64",			/* 213 = svr4_sys_getdents64 */
	"svr4_sys_mmap64",			/* 214 = svr4_sys_mmap64 */
	"svr4_sys_stat64",			/* 215 = svr4_sys_stat64 */
	"svr4_sys_lstat64",			/* 216 = svr4_sys_lstat64 */
	"svr4_sys_fstat64",			/* 217 = svr4_sys_fstat64 */
	"svr4_sys_statvfs64",			/* 218 = svr4_sys_statvfs64 */
	"svr4_sys_fstatvfs64",			/* 219 = svr4_sys_fstatvfs64 */
	"svr4_sys_setrlimit64",			/* 220 = svr4_sys_setrlimit64 */
	"svr4_sys_getrlimit64",			/* 221 = svr4_sys_getrlimit64 */
	"#222",			/* 222 = pread64 */
	"#223",			/* 223 = pwrite64 */
	"svr4_sys_creat64",			/* 224 = svr4_sys_creat64 */
	"svr4_sys_open64",			/* 225 = svr4_sys_open64 */
	"#226",			/* 226 = rpcsys */
	"#227",			/* 227 = whoknows */
	"#228",			/* 228 = whoknows */
	"#229",			/* 229 = whoknows */
	"svr4_sys_socket",			/* 230 = svr4_sys_socket */
	"socketpair",			/* 231 = socketpair */
	"bind",			/* 232 = bind */
	"listen",			/* 233 = listen */
	"accept",			/* 234 = accept */
	"connect",			/* 235 = connect */
	"shutdown",			/* 236 = shutdown */
	"svr4_sys_recv",			/* 237 = svr4_sys_recv */
	"recvfrom",			/* 238 = recvfrom */
	"recvmsg",			/* 239 = recvmsg */
	"svr4_sys_send",			/* 240 = svr4_sys_send */
	"sendmsg",			/* 241 = sendmsg */
	"svr4_sys_sendto",			/* 242 = svr4_sys_sendto */
	"getpeername",			/* 243 = getpeername */
	"getsockname",			/* 244 = getsockname */
	"getsockopt",			/* 245 = getsockopt */
	"setsockopt",			/* 246 = setsockopt */
	"#247",			/* 247 = sockconfig */
	"#248",			/* 248 = { */
	"#249",			/* 249 = { */
};
