/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from;	FreeBSD: src/sys/alpha/osf1/syscalls.master,v 1.8 2004/02/04 21:57:00 jhb Exp 
 */

#include "opt_compat.h"
#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <alpha/osf1/osf1.h>
#include <alpha/osf1/osf1_signal.h>
#include <alpha/osf1/osf1_proto.h>

#define AS(name) (sizeof(struct name) / sizeof(register_t))

/* The casts are bogus but will do for now. */
struct sysent osf1_sysent[] = {
	{ 0, (sy_call_t *)nosys },			/* 0 = nosys */
	{ SYF_MPSAFE | AS(sys_exit_args), (sy_call_t *)sys_exit },	/* 1 = exit */
	{ SYF_MPSAFE | 0, (sy_call_t *)fork },		/* 2 = fork */
	{ SYF_MPSAFE | AS(read_args), (sy_call_t *)read },	/* 3 = read */
	{ SYF_MPSAFE | AS(write_args), (sy_call_t *)write },	/* 4 = write */
	{ 0, (sy_call_t *)nosys },			/* 5 = old open */
	{ SYF_MPSAFE | AS(close_args), (sy_call_t *)close },	/* 6 = close */
	{ AS(osf1_wait4_args), (sy_call_t *)osf1_wait4 },	/* 7 = osf1_wait4 */
	{ 0, (sy_call_t *)nosys },			/* 8 = old creat */
	{ AS(link_args), (sy_call_t *)link },		/* 9 = link */
	{ AS(unlink_args), (sy_call_t *)unlink },	/* 10 = unlink */
	{ 0, (sy_call_t *)nosys },			/* 11 = execv */
	{ AS(chdir_args), (sy_call_t *)chdir },		/* 12 = chdir */
	{ AS(fchdir_args), (sy_call_t *)fchdir },	/* 13 = fchdir */
	{ AS(osf1_mknod_args), (sy_call_t *)osf1_mknod },	/* 14 = osf1_mknod */
	{ AS(chmod_args), (sy_call_t *)chmod },		/* 15 = chmod */
	{ AS(chown_args), (sy_call_t *)chown },		/* 16 = chown */
	{ AS(obreak_args), (sy_call_t *)obreak },	/* 17 = obreak */
	{ AS(osf1_getfsstat_args), (sy_call_t *)osf1_getfsstat },	/* 18 = osf1_getfsstat */
	{ AS(osf1_lseek_args), (sy_call_t *)osf1_lseek },	/* 19 = osf1_lseek */
	{ SYF_MPSAFE | 0, (sy_call_t *)getpid },	/* 20 = getpid */
	{ AS(osf1_mount_args), (sy_call_t *)osf1_mount },	/* 21 = osf1_mount */
	{ AS(osf1_unmount_args), (sy_call_t *)osf1_unmount },	/* 22 = osf1_unmount */
	{ SYF_MPSAFE | AS(osf1_setuid_args), (sy_call_t *)osf1_setuid },	/* 23 = osf1_setuid */
	{ SYF_MPSAFE | 0, (sy_call_t *)getuid },	/* 24 = getuid */
	{ 0, (sy_call_t *)nosys },			/* 25 = exec_with_loader */
	{ 0, (sy_call_t *)nosys },			/* 26 = ptrace */
	{ 0, (sy_call_t *)nosys },			/* 27 = recvmsg */
	{ 0, (sy_call_t *)nosys },			/* 28 = sendmsg */
	{ AS(recvfrom_args), (sy_call_t *)recvfrom },	/* 29 = recvfrom */
	{ AS(accept_args), (sy_call_t *)accept },	/* 30 = accept */
	{ AS(getpeername_args), (sy_call_t *)getpeername },	/* 31 = getpeername */
	{ AS(getsockname_args), (sy_call_t *)getsockname },	/* 32 = getsockname */
	{ AS(osf1_access_args), (sy_call_t *)osf1_access },	/* 33 = osf1_access */
	{ 0, (sy_call_t *)nosys },			/* 34 = chflags */
	{ 0, (sy_call_t *)nosys },			/* 35 = fchflags */
	{ 0, (sy_call_t *)sync },			/* 36 = sync */
	{ SYF_MPSAFE | AS(osf1_kill_args), (sy_call_t *)osf1_kill },	/* 37 = osf1_kill */
	{ 0, (sy_call_t *)nosys },			/* 38 = old stat */
	{ SYF_MPSAFE | AS(setpgid_args), (sy_call_t *)setpgid },	/* 39 = setpgid */
	{ 0, (sy_call_t *)nosys },			/* 40 = old lstat */
	{ SYF_MPSAFE | AS(dup_args), (sy_call_t *)dup },	/* 41 = dup */
	{ SYF_MPSAFE | 0, (sy_call_t *)pipe },		/* 42 = pipe */
	{ AS(osf1_set_program_attributes_args), (sy_call_t *)osf1_set_program_attributes },	/* 43 = osf1_set_program_attributes */
	{ 0, (sy_call_t *)nosys },			/* 44 = profil */
	{ AS(osf1_open_args), (sy_call_t *)osf1_open },	/* 45 = osf1_open */
	{ 0, (sy_call_t *)nosys },			/* 46 = obsolete sigaction */
	{ SYF_MPSAFE | 0, (sy_call_t *)getgid },	/* 47 = getgid */
	{ SYF_MPSAFE | AS(osf1_sigprocmask_args), (sy_call_t *)osf1_sigprocmask },	/* 48 = osf1_sigprocmask */
	{ SYF_MPSAFE | AS(getlogin_args), (sy_call_t *)getlogin },	/* 49 = getlogin */
	{ SYF_MPSAFE | AS(setlogin_args), (sy_call_t *)setlogin },	/* 50 = setlogin */
	{ AS(acct_args), (sy_call_t *)acct },		/* 51 = acct */
	{ SYF_MPSAFE | AS(osf1_sigpending_args), (sy_call_t *)osf1_sigpending },	/* 52 = osf1_sigpending */
	{ AS(osf1_classcntl_args), (sy_call_t *)osf1_classcntl },	/* 53 = osf1_classcntl */
	{ AS(osf1_ioctl_args), (sy_call_t *)osf1_ioctl },	/* 54 = osf1_ioctl */
	{ AS(osf1_reboot_args), (sy_call_t *)osf1_reboot },	/* 55 = osf1_reboot */
	{ AS(revoke_args), (sy_call_t *)revoke },	/* 56 = revoke */
	{ AS(symlink_args), (sy_call_t *)symlink },	/* 57 = symlink */
	{ AS(readlink_args), (sy_call_t *)readlink },	/* 58 = readlink */
	{ AS(osf1_execve_args), (sy_call_t *)osf1_execve },	/* 59 = osf1_execve */
	{ SYF_MPSAFE | AS(umask_args), (sy_call_t *)umask },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)chroot },	/* 61 = chroot */
	{ 0, (sy_call_t *)nosys },			/* 62 = old fstat */
	{ SYF_MPSAFE | 0, (sy_call_t *)getpgrp },	/* 63 = getpgrp */
	{ 0, (sy_call_t *)ogetpagesize },		/* 64 = ogetpagesize */
	{ 0, (sy_call_t *)nosys },			/* 65 = mremap */
	{ SYF_MPSAFE | 0, (sy_call_t *)vfork },		/* 66 = vfork */
	{ AS(osf1_stat_args), (sy_call_t *)osf1_stat },	/* 67 = osf1_stat */
	{ AS(osf1_lstat_args), (sy_call_t *)osf1_lstat },	/* 68 = osf1_lstat */
	{ 0, (sy_call_t *)nosys },			/* 69 = sbrk */
	{ 0, (sy_call_t *)nosys },			/* 70 = sstk */
	{ AS(osf1_mmap_args), (sy_call_t *)osf1_mmap },	/* 71 = osf1_mmap */
	{ 0, (sy_call_t *)nosys },			/* 72 = ovadvise */
	{ AS(munmap_args), (sy_call_t *)munmap },	/* 73 = munmap */
	{ AS(mprotect_args), (sy_call_t *)mprotect },	/* 74 = mprotect */
	{ 0, (sy_call_t *)osf1_madvise },		/* 75 = osf1_madvise */
	{ 0, (sy_call_t *)nosys },			/* 76 = old vhangup */
	{ 0, (sy_call_t *)nosys },			/* 77 = kmodcall */
	{ 0, (sy_call_t *)nosys },			/* 78 = mincore */
	{ SYF_MPSAFE | AS(getgroups_args), (sy_call_t *)getgroups },	/* 79 = getgroups */
	{ SYF_MPSAFE | AS(setgroups_args), (sy_call_t *)setgroups },	/* 80 = setgroups */
	{ 0, (sy_call_t *)nosys },			/* 81 = old getpgrp */
	{ SYF_MPSAFE | AS(osf1_setpgrp_args), (sy_call_t *)osf1_setpgrp },	/* 82 = osf1_setpgrp */
	{ AS(osf1_setitimer_args), (sy_call_t *)osf1_setitimer },	/* 83 = osf1_setitimer */
	{ 0, (sy_call_t *)nosys },			/* 84 = old wait */
	{ AS(osf1_table_args), (sy_call_t *)osf1_table },	/* 85 = osf1_table */
	{ AS(osf1_getitimer_args), (sy_call_t *)osf1_getitimer },	/* 86 = osf1_getitimer */
	{ SYF_MPSAFE | AS(gethostname_args), (sy_call_t *)ogethostname },	/* 87 = ogethostname */
	{ SYF_MPSAFE | AS(sethostname_args), (sy_call_t *)osethostname },	/* 88 = osethostname */
	{ SYF_MPSAFE | 0, (sy_call_t *)getdtablesize },	/* 89 = getdtablesize */
	{ SYF_MPSAFE | AS(dup2_args), (sy_call_t *)dup2 },	/* 90 = dup2 */
	{ AS(osf1_fstat_args), (sy_call_t *)osf1_fstat },	/* 91 = osf1_fstat */
	{ AS(osf1_fcntl_args), (sy_call_t *)osf1_fcntl },	/* 92 = osf1_fcntl */
	{ AS(osf1_select_args), (sy_call_t *)osf1_select },	/* 93 = osf1_select */
	{ AS(poll_args), (sy_call_t *)poll },		/* 94 = poll */
	{ AS(fsync_args), (sy_call_t *)fsync },		/* 95 = fsync */
	{ SYF_MPSAFE | AS(setpriority_args), (sy_call_t *)setpriority },	/* 96 = setpriority */
	{ AS(osf1_socket_args), (sy_call_t *)osf1_socket },	/* 97 = osf1_socket */
	{ AS(connect_args), (sy_call_t *)connect },	/* 98 = connect */
	{ AS(accept_args), (sy_call_t *)oaccept },	/* 99 = oaccept */
	{ SYF_MPSAFE | AS(getpriority_args), (sy_call_t *)getpriority },	/* 100 = getpriority */
	{ AS(osend_args), (sy_call_t *)osend },		/* 101 = osend */
	{ AS(orecv_args), (sy_call_t *)orecv },		/* 102 = orecv */
	{ SYF_MPSAFE | AS(osf1_sigreturn_args), (sy_call_t *)osf1_sigreturn },	/* 103 = osf1_sigreturn */
	{ AS(bind_args), (sy_call_t *)bind },		/* 104 = bind */
	{ AS(setsockopt_args), (sy_call_t *)setsockopt },	/* 105 = setsockopt */
	{ AS(listen_args), (sy_call_t *)listen },	/* 106 = listen */
	{ 0, (sy_call_t *)nosys },			/* 107 = plock */
	{ 0, (sy_call_t *)nosys },			/* 108 = old sigvec */
	{ 0, (sy_call_t *)nosys },			/* 109 = old sigblock */
	{ 0, (sy_call_t *)nosys },			/* 110 = old sigsetmask */
	{ SYF_MPSAFE | AS(osf1_sigsuspend_args), (sy_call_t *)osf1_sigsuspend },	/* 111 = osf1_sigsuspend */
	{ SYF_MPSAFE | AS(osf1_osigstack_args), (sy_call_t *)osf1_osigstack },	/* 112 = osf1_osigstack */
	{ 0, (sy_call_t *)nosys },			/* 113 = old recvmsg */
	{ 0, (sy_call_t *)nosys },			/* 114 = old sendmsg */
	{ 0, (sy_call_t *)nosys },			/* 115 = vtrace */
	{ AS(osf1_gettimeofday_args), (sy_call_t *)osf1_gettimeofday },	/* 116 = osf1_gettimeofday */
	{ AS(osf1_getrusage_args), (sy_call_t *)osf1_getrusage },	/* 117 = osf1_getrusage */
	{ AS(getsockopt_args), (sy_call_t *)getsockopt },	/* 118 = getsockopt */
	{ 0, (sy_call_t *)nosys },			/* 119 =  */
	{ AS(osf1_readv_args), (sy_call_t *)osf1_readv },	/* 120 = osf1_readv */
	{ AS(osf1_writev_args), (sy_call_t *)osf1_writev },	/* 121 = osf1_writev */
	{ SYF_MPSAFE | AS(settimeofday_args), (sy_call_t *)settimeofday },	/* 122 = settimeofday */
	{ AS(fchown_args), (sy_call_t *)fchown },	/* 123 = fchown */
	{ AS(fchmod_args), (sy_call_t *)fchmod },	/* 124 = fchmod */
	{ AS(recvfrom_args), (sy_call_t *)orecvfrom },	/* 125 = orecvfrom */
	{ SYF_MPSAFE | AS(setreuid_args), (sy_call_t *)setreuid },	/* 126 = setreuid */
	{ SYF_MPSAFE | AS(setregid_args), (sy_call_t *)setregid },	/* 127 = setregid */
	{ AS(rename_args), (sy_call_t *)rename },	/* 128 = rename */
	{ AS(osf1_truncate_args), (sy_call_t *)osf1_truncate },	/* 129 = osf1_truncate */
	{ AS(osf1_ftruncate_args), (sy_call_t *)osf1_ftruncate },	/* 130 = osf1_ftruncate */
	{ AS(flock_args), (sy_call_t *)flock },		/* 131 = flock */
	{ SYF_MPSAFE | AS(osf1_setgid_args), (sy_call_t *)osf1_setgid },	/* 132 = osf1_setgid */
	{ AS(osf1_sendto_args), (sy_call_t *)osf1_sendto },	/* 133 = osf1_sendto */
	{ AS(shutdown_args), (sy_call_t *)shutdown },	/* 134 = shutdown */
	{ 0, (sy_call_t *)nosys },			/* 135 = socketpair */
	{ AS(mkdir_args), (sy_call_t *)mkdir },		/* 136 = mkdir */
	{ AS(rmdir_args), (sy_call_t *)rmdir },		/* 137 = rmdir */
	{ AS(utimes_args), (sy_call_t *)utimes },	/* 138 = utimes */
	{ 0, (sy_call_t *)nosys },			/* 139 = obsolete 4.2 sigreturn */
	{ 0, (sy_call_t *)nosys },			/* 140 = adjtime */
	{ AS(ogetpeername_args), (sy_call_t *)ogetpeername },	/* 141 = ogetpeername */
	{ SYF_MPSAFE | 0, (sy_call_t *)ogethostid },	/* 142 = ogethostid */
	{ SYF_MPSAFE | AS(osethostid_args), (sy_call_t *)osethostid },	/* 143 = osethostid */
	{ SYF_MPSAFE | AS(osf1_getrlimit_args), (sy_call_t *)osf1_getrlimit },	/* 144 = osf1_getrlimit */
	{ SYF_MPSAFE | AS(osf1_setrlimit_args), (sy_call_t *)osf1_setrlimit },	/* 145 = osf1_setrlimit */
	{ 0, (sy_call_t *)nosys },			/* 146 = old killpg */
	{ SYF_MPSAFE | 0, (sy_call_t *)setsid },	/* 147 = setsid */
	{ 0, (sy_call_t *)nosys },			/* 148 = quotactl */
	{ SYF_MPSAFE | 0, (sy_call_t *)oquota },	/* 149 = oquota */
	{ AS(getsockname_args), (sy_call_t *)ogetsockname },	/* 150 = ogetsockname */
	{ 0, (sy_call_t *)nosys },			/* 151 =  */
	{ 0, (sy_call_t *)nosys },			/* 152 =  */
	{ 0, (sy_call_t *)nosys },			/* 153 =  */
	{ 0, (sy_call_t *)nosys },			/* 154 =  */
	{ 0, (sy_call_t *)nosys },			/* 155 =  */
	{ SYF_MPSAFE | AS(osf1_sigaction_args), (sy_call_t *)osf1_sigaction },	/* 156 = osf1_sigaction */
	{ 0, (sy_call_t *)nosys },			/* 157 =  */
	{ 0, (sy_call_t *)nosys },			/* 158 = nfssvc */
	{ AS(ogetdirentries_args), (sy_call_t *)ogetdirentries },	/* 159 = ogetdirentries */
	{ AS(osf1_statfs_args), (sy_call_t *)osf1_statfs },	/* 160 = osf1_statfs */
	{ AS(osf1_fstatfs_args), (sy_call_t *)osf1_fstatfs },	/* 161 = osf1_fstatfs */
	{ 0, (sy_call_t *)nosys },			/* 162 =  */
	{ 0, (sy_call_t *)nosys },			/* 163 = async_daemon */
	{ 0, (sy_call_t *)nosys },			/* 164 = getfh */
	{ SYF_MPSAFE | AS(getdomainname_args), (sy_call_t *)getdomainname },	/* 165 = getdomainname */
	{ SYF_MPSAFE | AS(setdomainname_args), (sy_call_t *)setdomainname },	/* 166 = setdomainname */
	{ 0, (sy_call_t *)nosys },			/* 167 =  */
	{ 0, (sy_call_t *)nosys },			/* 168 =  */
	{ 0, (sy_call_t *)nosys },			/* 169 = exportfs */
	{ 0, (sy_call_t *)nosys },			/* 170 =  */
	{ 0, (sy_call_t *)nosys },			/* 171 =  */
	{ 0, (sy_call_t *)nosys },			/* 172 = alt msgctl */
	{ 0, (sy_call_t *)nosys },			/* 173 = alt msgget */
	{ 0, (sy_call_t *)nosys },			/* 174 = alt msgrcv */
	{ 0, (sy_call_t *)nosys },			/* 175 = alt msgsnd */
	{ 0, (sy_call_t *)nosys },			/* 176 = alt semctl */
	{ 0, (sy_call_t *)nosys },			/* 177 = alt semget */
	{ 0, (sy_call_t *)nosys },			/* 178 = alt semop */
	{ 0, (sy_call_t *)nosys },			/* 179 = alt uname */
	{ 0, (sy_call_t *)nosys },			/* 180 =  */
	{ 0, (sy_call_t *)nosys },			/* 181 = alt plock */
	{ 0, (sy_call_t *)nosys },			/* 182 = lockf */
	{ 0, (sy_call_t *)nosys },			/* 183 =  */
	{ 0, (sy_call_t *)nosys },			/* 184 = getmnt */
	{ 0, (sy_call_t *)nosys },			/* 185 =  */
	{ 0, (sy_call_t *)nosys },			/* 186 = unmount */
	{ 0, (sy_call_t *)nosys },			/* 187 = alt sigpending */
	{ 0, (sy_call_t *)nosys },			/* 188 = alt setsid */
	{ 0, (sy_call_t *)nosys },			/* 189 =  */
	{ 0, (sy_call_t *)nosys },			/* 190 =  */
	{ 0, (sy_call_t *)nosys },			/* 191 =  */
	{ 0, (sy_call_t *)nosys },			/* 192 =  */
	{ 0, (sy_call_t *)nosys },			/* 193 =  */
	{ 0, (sy_call_t *)nosys },			/* 194 =  */
	{ 0, (sy_call_t *)nosys },			/* 195 =  */
	{ 0, (sy_call_t *)nosys },			/* 196 =  */
	{ 0, (sy_call_t *)nosys },			/* 197 =  */
	{ 0, (sy_call_t *)nosys },			/* 198 =  */
	{ 0, (sy_call_t *)nosys },			/* 199 = swapon */
	{ SYF_MPSAFE | AS(msgctl_args), (sy_call_t *)msgctl },	/* 200 = msgctl */
	{ SYF_MPSAFE | AS(msgget_args), (sy_call_t *)msgget },	/* 201 = msgget */
	{ SYF_MPSAFE | AS(msgrcv_args), (sy_call_t *)msgrcv },	/* 202 = msgrcv */
	{ SYF_MPSAFE | AS(msgsnd_args), (sy_call_t *)msgsnd },	/* 203 = msgsnd */
	{ SYF_MPSAFE | AS(__semctl_args), (sy_call_t *)__semctl },	/* 204 = __semctl */
	{ SYF_MPSAFE | AS(semget_args), (sy_call_t *)semget },	/* 205 = semget */
	{ SYF_MPSAFE | AS(semop_args), (sy_call_t *)semop },	/* 206 = semop */
	{ SYF_MPSAFE | AS(uname_args), (sy_call_t *)uname },	/* 207 = uname */
	{ AS(lchown_args), (sy_call_t *)lchown },	/* 208 = lchown */
	{ SYF_MPSAFE | AS(shmat_args), (sy_call_t *)shmat },	/* 209 = shmat */
	{ SYF_MPSAFE | AS(shmctl_args), (sy_call_t *)shmctl },	/* 210 = shmctl */
	{ SYF_MPSAFE | AS(shmdt_args), (sy_call_t *)shmdt },	/* 211 = shmdt */
	{ SYF_MPSAFE | AS(shmget_args), (sy_call_t *)shmget },	/* 212 = shmget */
	{ 0, (sy_call_t *)nosys },			/* 213 = mvalid */
	{ 0, (sy_call_t *)nosys },			/* 214 = getaddressconf */
	{ 0, (sy_call_t *)nosys },			/* 215 = msleep */
	{ 0, (sy_call_t *)nosys },			/* 216 = mwakeup */
	{ AS(osf1_msync_args), (sy_call_t *)osf1_msync },	/* 217 = osf1_msync */
	{ SYF_MPSAFE | AS(osf1_signal_args), (sy_call_t *)osf1_signal },	/* 218 = osf1_signal */
	{ 0, (sy_call_t *)nosys },			/* 219 = utc gettime */
	{ 0, (sy_call_t *)nosys },			/* 220 = utc adjtime */
	{ 0, (sy_call_t *)nosys },			/* 221 =  */
	{ 0, (sy_call_t *)nosys },			/* 222 = security */
	{ 0, (sy_call_t *)nosys },			/* 223 = kloadcall */
	{ 0, (sy_call_t *)nosys },			/* 224 =  */
	{ 0, (sy_call_t *)nosys },			/* 225 =  */
	{ 0, (sy_call_t *)nosys },			/* 226 =  */
	{ 0, (sy_call_t *)nosys },			/* 227 =  */
	{ 0, (sy_call_t *)nosys },			/* 228 =  */
	{ 0, (sy_call_t *)nosys },			/* 229 =  */
	{ 0, (sy_call_t *)nosys },			/* 230 =  */
	{ 0, (sy_call_t *)nosys },			/* 231 =  */
	{ 0, (sy_call_t *)nosys },			/* 232 =  */
	{ SYF_MPSAFE | AS(getpgid_args), (sy_call_t *)getpgid },	/* 233 = getpgid */
	{ SYF_MPSAFE | AS(getsid_args), (sy_call_t *)getsid },	/* 234 = getsid */
	{ SYF_MPSAFE | AS(osf1_sigaltstack_args), (sy_call_t *)osf1_sigaltstack },	/* 235 = osf1_sigaltstack */
	{ 0, (sy_call_t *)nosys },			/* 236 = waitid */
	{ 0, (sy_call_t *)nosys },			/* 237 = priocntlset */
	{ 0, (sy_call_t *)nosys },			/* 238 = sigsendset */
	{ 0, (sy_call_t *)nosys },			/* 239 =  */
	{ 0, (sy_call_t *)nosys },			/* 240 = msfs_syscall */
	{ SYF_MPSAFE | AS(osf1_sysinfo_args), (sy_call_t *)osf1_sysinfo },	/* 241 = osf1_sysinfo */
	{ 0, (sy_call_t *)nosys },			/* 242 = uadmin */
	{ 0, (sy_call_t *)nosys },			/* 243 = fuser */
	{ 0, (sy_call_t *)osf1_proplist_syscall },	/* 244 = osf1_proplist_syscall */
	{ AS(osf1_ntpadjtime_args), (sy_call_t *)osf1_ntpadjtime },	/* 245 = osf1_ntpadjtime */
	{ AS(osf1_ntpgettime_args), (sy_call_t *)osf1_ntpgettime },	/* 246 = osf1_ntpgettime */
	{ AS(osf1_pathconf_args), (sy_call_t *)osf1_pathconf },	/* 247 = osf1_pathconf */
	{ AS(osf1_fpathconf_args), (sy_call_t *)osf1_fpathconf },	/* 248 = osf1_fpathconf */
	{ 0, (sy_call_t *)nosys },			/* 249 =  */
	{ AS(osf1_uswitch_args), (sy_call_t *)osf1_uswitch },	/* 250 = osf1_uswitch */
	{ AS(osf1_usleep_thread_args), (sy_call_t *)osf1_usleep_thread },	/* 251 = osf1_usleep_thread */
	{ 0, (sy_call_t *)nosys },			/* 252 = audcntl */
	{ 0, (sy_call_t *)nosys },			/* 253 = audgen */
	{ 0, (sy_call_t *)nosys },			/* 254 = sysfs */
	{ 0, (sy_call_t *)nosys },			/* 255 =  */
	{ AS(osf1_getsysinfo_args), (sy_call_t *)osf1_getsysinfo },	/* 256 = osf1_getsysinfo */
	{ AS(osf1_setsysinfo_args), (sy_call_t *)osf1_setsysinfo },	/* 257 = osf1_setsysinfo */
	{ 0, (sy_call_t *)nosys },			/* 258 = afs_syscall */
	{ 0, (sy_call_t *)nosys },			/* 259 = swapctl */
	{ 0, (sy_call_t *)nosys },			/* 260 = memcntl */
	{ 0, (sy_call_t *)nosys },			/* 261 =  */
	{ 0, (sy_call_t *)nosys },			/* 262 =  */
	{ 0, (sy_call_t *)nosys },			/* 263 =  */
	{ 0, (sy_call_t *)nosys },			/* 264 =  */
	{ 0, (sy_call_t *)nosys },			/* 265 =  */
	{ 0, (sy_call_t *)nosys },			/* 266 =  */
	{ 0, (sy_call_t *)nosys },			/* 267 =  */
	{ 0, (sy_call_t *)nosys },			/* 268 =  */
	{ 0, (sy_call_t *)nosys },			/* 269 =  */
	{ 0, (sy_call_t *)nosys },			/* 270 =  */
	{ 0, (sy_call_t *)nosys },			/* 271 =  */
	{ 0, (sy_call_t *)nosys },			/* 272 =  */
	{ 0, (sy_call_t *)nosys },			/* 273 =  */
	{ 0, (sy_call_t *)nosys },			/* 274 =  */
	{ 0, (sy_call_t *)nosys },			/* 275 =  */
	{ 0, (sy_call_t *)nosys },			/* 276 =  */
	{ 0, (sy_call_t *)nosys },			/* 277 =  */
	{ 0, (sy_call_t *)nosys },			/* 278 =  */
	{ 0, (sy_call_t *)nosys },			/* 279 =  */
	{ 0, (sy_call_t *)nosys },			/* 280 =  */
	{ 0, (sy_call_t *)nosys },			/* 281 =  */
	{ 0, (sy_call_t *)nosys },			/* 282 =  */
	{ 0, (sy_call_t *)nosys },			/* 283 =  */
	{ 0, (sy_call_t *)nosys },			/* 284 =  */
	{ 0, (sy_call_t *)nosys },			/* 285 =  */
	{ 0, (sy_call_t *)nosys },			/* 286 =  */
	{ 0, (sy_call_t *)nosys },			/* 287 =  */
	{ 0, (sy_call_t *)nosys },			/* 288 =  */
	{ 0, (sy_call_t *)nosys },			/* 289 =  */
	{ 0, (sy_call_t *)nosys },			/* 290 =  */
	{ 0, (sy_call_t *)nosys },			/* 291 =  */
	{ 0, (sy_call_t *)nosys },			/* 292 =  */
	{ 0, (sy_call_t *)nosys },			/* 293 =  */
	{ 0, (sy_call_t *)nosys },			/* 294 =  */
	{ 0, (sy_call_t *)nosys },			/* 295 =  */
	{ 0, (sy_call_t *)nosys },			/* 296 =  */
	{ 0, (sy_call_t *)nosys },			/* 297 =  */
	{ 0, (sy_call_t *)nosys },			/* 298 =  */
	{ 0, (sy_call_t *)nosys },			/* 299 =  */
	{ 0, (sy_call_t *)nosys },			/* 300 =  */
};
