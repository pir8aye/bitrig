/*	$OpenBSD: linux_sysent.c,v 1.43 2003/08/14 18:35:57 fgsch Exp $	*/

/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	OpenBSD: syscalls.master,v 1.41 2003/08/14 18:34:15 fgsch Exp 
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>
#include <compat/linux/linux_types.h>
#include <compat/linux/linux_signal.h>
#include <compat/linux/linux_misc.h>
#include <compat/linux/linux_syscallargs.h>
#include <machine/linux_machdep.h>

#define	s(type)	sizeof(type)

struct sysent linux_sysent[] = {
	{ 0, 0,
	    sys_nosys },			/* 0 = syscall */
	{ 1, s(struct sys_exit_args),
	    sys_exit },				/* 1 = exit */
	{ 0, 0,
	    sys_fork },				/* 2 = fork */
	{ 3, s(struct sys_read_args),
	    sys_read },				/* 3 = read */
	{ 3, s(struct sys_write_args),
	    sys_write },			/* 4 = write */
	{ 3, s(struct linux_sys_open_args),
	    linux_sys_open },			/* 5 = open */
	{ 1, s(struct sys_close_args),
	    sys_close },			/* 6 = close */
	{ 3, s(struct linux_sys_waitpid_args),
	    linux_sys_waitpid },		/* 7 = waitpid */
	{ 2, s(struct linux_sys_creat_args),
	    linux_sys_creat },			/* 8 = creat */
	{ 2, s(struct sys_link_args),
	    sys_link },				/* 9 = link */
	{ 1, s(struct linux_sys_unlink_args),
	    linux_sys_unlink },			/* 10 = unlink */
	{ 3, s(struct linux_sys_execve_args),
	    linux_sys_execve },			/* 11 = execve */
	{ 1, s(struct linux_sys_chdir_args),
	    linux_sys_chdir },			/* 12 = chdir */
	{ 1, s(struct linux_sys_time_args),
	    linux_sys_time },			/* 13 = time */
	{ 3, s(struct linux_sys_mknod_args),
	    linux_sys_mknod },			/* 14 = mknod */
	{ 2, s(struct linux_sys_chmod_args),
	    linux_sys_chmod },			/* 15 = chmod */
	{ 3, s(struct linux_sys_lchown16_args),
	    linux_sys_lchown16 },		/* 16 = lchown16 */
	{ 1, s(struct linux_sys_break_args),
	    linux_sys_break },			/* 17 = break */
	{ 0, 0,
	    linux_sys_ostat },			/* 18 = ostat */
	{ 3, s(struct compat_43_sys_lseek_args),
	    compat_43_sys_lseek },		/* 19 = lseek */
	{ 0, 0,
	    linux_sys_getpid },			/* 20 = getpid */
	{ 5, s(struct linux_sys_mount_args),
	    linux_sys_mount },			/* 21 = mount */
	{ 1, s(struct linux_sys_umount_args),
	    linux_sys_umount },			/* 22 = umount */
	{ 1, s(struct sys_setuid_args),
	    sys_setuid },			/* 23 = linux_setuid16 */
	{ 0, 0,
	    linux_sys_getuid },			/* 24 = linux_getuid16 */
	{ 1, s(struct linux_sys_stime_args),
	    linux_sys_stime },			/* 25 = stime */
#ifdef PTRACE
	{ 0, 0,
	    linux_sys_ptrace },			/* 26 = ptrace */
#else
	{ 0, 0,
	    sys_nosys },			/* 26 = unimplemented ptrace */
#endif
	{ 1, s(struct linux_sys_alarm_args),
	    linux_sys_alarm },			/* 27 = alarm */
	{ 0, 0,
	    linux_sys_ofstat },			/* 28 = ofstat */
	{ 0, 0,
	    linux_sys_pause },			/* 29 = pause */
	{ 2, s(struct linux_sys_utime_args),
	    linux_sys_utime },			/* 30 = utime */
	{ 0, 0,
	    linux_sys_stty },			/* 31 = stty */
	{ 0, 0,
	    linux_sys_gtty },			/* 32 = gtty */
	{ 2, s(struct linux_sys_access_args),
	    linux_sys_access },			/* 33 = access */
	{ 1, s(struct linux_sys_nice_args),
	    linux_sys_nice },			/* 34 = nice */
	{ 0, 0,
	    linux_sys_ftime },			/* 35 = ftime */
	{ 0, 0,
	    sys_sync },				/* 36 = sync */
	{ 2, s(struct linux_sys_kill_args),
	    linux_sys_kill },			/* 37 = kill */
	{ 2, s(struct linux_sys_rename_args),
	    linux_sys_rename },			/* 38 = rename */
	{ 2, s(struct linux_sys_mkdir_args),
	    linux_sys_mkdir },			/* 39 = mkdir */
	{ 1, s(struct linux_sys_rmdir_args),
	    linux_sys_rmdir },			/* 40 = rmdir */
	{ 1, s(struct sys_dup_args),
	    sys_dup },				/* 41 = dup */
	{ 1, s(struct linux_sys_pipe_args),
	    linux_sys_pipe },			/* 42 = pipe */
	{ 1, s(struct linux_sys_times_args),
	    linux_sys_times },			/* 43 = times */
	{ 0, 0,
	    linux_sys_prof },			/* 44 = prof */
	{ 1, s(struct linux_sys_brk_args),
	    linux_sys_brk },			/* 45 = brk */
	{ 1, s(struct sys_setgid_args),
	    sys_setgid },			/* 46 = linux_setgid16 */
	{ 0, 0,
	    linux_sys_getgid },			/* 47 = linux_getgid16 */
	{ 2, s(struct linux_sys_signal_args),
	    linux_sys_signal },			/* 48 = signal */
	{ 0, 0,
	    sys_geteuid },			/* 49 = linux_geteuid16 */
	{ 0, 0,
	    sys_getegid },			/* 50 = linux_getegid16 */
	{ 1, s(struct sys_acct_args),
	    sys_acct },				/* 51 = acct */
	{ 0, 0,
	    linux_sys_phys },			/* 52 = phys */
	{ 0, 0,
	    linux_sys_lock },			/* 53 = lock */
	{ 3, s(struct linux_sys_ioctl_args),
	    linux_sys_ioctl },			/* 54 = ioctl */
	{ 3, s(struct linux_sys_fcntl_args),
	    linux_sys_fcntl },			/* 55 = fcntl */
	{ 0, 0,
	    linux_sys_mpx },			/* 56 = mpx */
	{ 2, s(struct sys_setpgid_args),
	    sys_setpgid },			/* 57 = setpgid */
	{ 0, 0,
	    linux_sys_ulimit },			/* 58 = ulimit */
	{ 1, s(struct linux_sys_oldolduname_args),
	    linux_sys_oldolduname },		/* 59 = oldolduname */
	{ 1, s(struct sys_umask_args),
	    sys_umask },			/* 60 = umask */
	{ 1, s(struct sys_chroot_args),
	    sys_chroot },			/* 61 = chroot */
	{ 0, 0,
	    linux_sys_ustat },			/* 62 = ustat */
	{ 2, s(struct sys_dup2_args),
	    sys_dup2 },				/* 63 = dup2 */
	{ 0, 0,
	    sys_getppid },			/* 64 = getppid */
	{ 0, 0,
	    sys_getpgrp },			/* 65 = getpgrp */
	{ 0, 0,
	    sys_setsid },			/* 66 = setsid */
	{ 3, s(struct linux_sys_sigaction_args),
	    linux_sys_sigaction },		/* 67 = sigaction */
	{ 0, 0,
	    linux_sys_siggetmask },		/* 68 = siggetmask */
	{ 1, s(struct linux_sys_sigsetmask_args),
	    linux_sys_sigsetmask },		/* 69 = sigsetmask */
	{ 2, s(struct linux_sys_setreuid16_args),
	    linux_sys_setreuid16 },		/* 70 = setreuid16 */
	{ 2, s(struct linux_sys_setregid16_args),
	    linux_sys_setregid16 },		/* 71 = setregid16 */
	{ 3, s(struct linux_sys_sigsuspend_args),
	    linux_sys_sigsuspend },		/* 72 = sigsuspend */
	{ 1, s(struct linux_sys_sigpending_args),
	    linux_sys_sigpending },		/* 73 = sigpending */
	{ 2, s(struct compat_43_sys_sethostname_args),
	    compat_43_sys_sethostname },	/* 74 = sethostname */
	{ 2, s(struct linux_sys_setrlimit_args),
	    linux_sys_setrlimit },		/* 75 = setrlimit */
	{ 2, s(struct linux_sys_getrlimit_args),
	    linux_sys_getrlimit },		/* 76 = getrlimit */
	{ 2, s(struct sys_getrusage_args),
	    sys_getrusage },			/* 77 = getrusage */
	{ 2, s(struct sys_gettimeofday_args),
	    sys_gettimeofday },			/* 78 = gettimeofday */
	{ 2, s(struct sys_settimeofday_args),
	    sys_settimeofday },			/* 79 = settimeofday */
	{ 2, s(struct sys_getgroups_args),
	    sys_getgroups },			/* 80 = linux_getgroups */
	{ 2, s(struct sys_setgroups_args),
	    sys_setgroups },			/* 81 = linux_setgroups */
	{ 1, s(struct linux_sys_oldselect_args),
	    linux_sys_oldselect },		/* 82 = oldselect */
	{ 2, s(struct linux_sys_symlink_args),
	    linux_sys_symlink },		/* 83 = symlink */
	{ 2, s(struct compat_43_sys_lstat_args),
	    compat_43_sys_lstat },		/* 84 = olstat */
	{ 3, s(struct linux_sys_readlink_args),
	    linux_sys_readlink },		/* 85 = readlink */
	{ 1, s(struct linux_sys_uselib_args),
	    linux_sys_uselib },			/* 86 = uselib */
	{ 1, s(struct compat_25_sys_swapon_args),
	    compat_25_sys_swapon },		/* 87 = swapon */
	{ 1, s(struct sys_reboot_args),
	    sys_reboot },			/* 88 = reboot */
	{ 3, s(struct linux_sys_readdir_args),
	    linux_sys_readdir },		/* 89 = readdir */
	{ 1, s(struct linux_sys_mmap_args),
	    linux_sys_mmap },			/* 90 = mmap */
	{ 2, s(struct sys_munmap_args),
	    sys_munmap },			/* 91 = munmap */
	{ 2, s(struct linux_sys_truncate_args),
	    linux_sys_truncate },		/* 92 = truncate */
	{ 2, s(struct compat_43_sys_ftruncate_args),
	    compat_43_sys_ftruncate },		/* 93 = ftruncate */
	{ 2, s(struct sys_fchmod_args),
	    sys_fchmod },			/* 94 = fchmod */
	{ 3, s(struct linux_sys_fchown16_args),
	    linux_sys_fchown16 },		/* 95 = fchown16 */
	{ 2, s(struct sys_getpriority_args),
	    sys_getpriority },			/* 96 = getpriority */
	{ 3, s(struct sys_setpriority_args),
	    sys_setpriority },			/* 97 = setpriority */
	{ 4, s(struct sys_profil_args),
	    sys_profil },			/* 98 = profil */
	{ 2, s(struct linux_sys_statfs_args),
	    linux_sys_statfs },			/* 99 = statfs */
	{ 2, s(struct linux_sys_fstatfs_args),
	    linux_sys_fstatfs },		/* 100 = fstatfs */
#ifdef __i386__
	{ 3, s(struct linux_sys_ioperm_args),
	    linux_sys_ioperm },			/* 101 = ioperm */
#else
	{ 0, 0,
	    linux_sys_ioperm },			/* 101 = ioperm */
#endif
	{ 2, s(struct linux_sys_socketcall_args),
	    linux_sys_socketcall },		/* 102 = socketcall */
	{ 0, 0,
	    linux_sys_klog },			/* 103 = klog */
	{ 3, s(struct sys_setitimer_args),
	    sys_setitimer },			/* 104 = setitimer */
	{ 2, s(struct sys_getitimer_args),
	    sys_getitimer },			/* 105 = getitimer */
	{ 2, s(struct linux_sys_stat_args),
	    linux_sys_stat },			/* 106 = stat */
	{ 2, s(struct linux_sys_lstat_args),
	    linux_sys_lstat },			/* 107 = lstat */
	{ 2, s(struct linux_sys_fstat_args),
	    linux_sys_fstat },			/* 108 = fstat */
	{ 1, s(struct linux_sys_olduname_args),
	    linux_sys_olduname },		/* 109 = olduname */
#ifdef __i386__
	{ 1, s(struct linux_sys_iopl_args),
	    linux_sys_iopl },			/* 110 = iopl */
#else
	{ 0, 0,
	    linux_sys_iopl },			/* 110 = iopl */
#endif
	{ 0, 0,
	    linux_sys_vhangup },		/* 111 = vhangup */
	{ 0, 0,
	    linux_sys_idle },			/* 112 = idle */
	{ 0, 0,
	    linux_sys_vm86old },		/* 113 = vm86old */
	{ 4, s(struct linux_sys_wait4_args),
	    linux_sys_wait4 },			/* 114 = wait4 */
	{ 0, 0,
	    linux_sys_swapoff },		/* 115 = swapoff */
	{ 1, s(struct linux_sys_sysinfo_args),
	    linux_sys_sysinfo },		/* 116 = sysinfo */
	{ 5, s(struct linux_sys_ipc_args),
	    linux_sys_ipc },			/* 117 = ipc */
	{ 1, s(struct sys_fsync_args),
	    sys_fsync },			/* 118 = fsync */
	{ 1, s(struct linux_sys_sigreturn_args),
	    linux_sys_sigreturn },		/* 119 = sigreturn */
	{ 2, s(struct linux_sys_clone_args),
	    linux_sys_clone },			/* 120 = clone */
	{ 2, s(struct compat_09_sys_setdomainname_args),
	    compat_09_sys_setdomainname },	/* 121 = setdomainname */
	{ 1, s(struct linux_sys_uname_args),
	    linux_sys_uname },			/* 122 = uname */
#ifdef __i386__
	{ 3, s(struct linux_sys_modify_ldt_args),
	    linux_sys_modify_ldt },		/* 123 = modify_ldt */
#else
	{ 0, 0,
	    linux_sys_modify_ldt },		/* 123 = modify_ldt */
#endif
	{ 0, 0,
	    linux_sys_adjtimex },		/* 124 = adjtimex */
	{ 3, s(struct sys_mprotect_args),
	    sys_mprotect },			/* 125 = mprotect */
	{ 3, s(struct linux_sys_sigprocmask_args),
	    linux_sys_sigprocmask },		/* 126 = sigprocmask */
	{ 0, 0,
	    linux_sys_create_module },		/* 127 = create_module */
	{ 0, 0,
	    linux_sys_init_module },		/* 128 = init_module */
	{ 0, 0,
	    linux_sys_delete_module },		/* 129 = delete_module */
	{ 0, 0,
	    linux_sys_get_kernel_syms },	/* 130 = get_kernel_syms */
	{ 0, 0,
	    linux_sys_quotactl },		/* 131 = quotactl */
	{ 1, s(struct linux_sys_getpgid_args),
	    linux_sys_getpgid },		/* 132 = getpgid */
	{ 1, s(struct sys_fchdir_args),
	    sys_fchdir },			/* 133 = fchdir */
	{ 0, 0,
	    linux_sys_bdflush },		/* 134 = bdflush */
	{ 0, 0,
	    linux_sys_sysfs },			/* 135 = sysfs */
	{ 1, s(struct linux_sys_personality_args),
	    linux_sys_personality },		/* 136 = personality */
	{ 0, 0,
	    linux_sys_afs_syscall },		/* 137 = afs_syscall */
	{ 1, s(struct linux_sys_setfsuid_args),
	    linux_sys_setfsuid },		/* 138 = linux_setfsuid16 */
	{ 0, 0,
	    linux_sys_getfsuid },		/* 139 = linux_getfsuid16 */
	{ 5, s(struct linux_sys_llseek_args),
	    linux_sys_llseek },			/* 140 = llseek */
	{ 3, s(struct linux_sys_getdents_args),
	    linux_sys_getdents },		/* 141 = getdents */
	{ 5, s(struct linux_sys_select_args),
	    linux_sys_select },			/* 142 = select */
	{ 2, s(struct sys_flock_args),
	    sys_flock },			/* 143 = flock */
	{ 3, s(struct sys_msync_args),
	    sys_msync },			/* 144 = msync */
	{ 3, s(struct sys_readv_args),
	    sys_readv },			/* 145 = readv */
	{ 3, s(struct sys_writev_args),
	    sys_writev },			/* 146 = writev */
	{ 1, s(struct linux_sys_getsid_args),
	    linux_sys_getsid },			/* 147 = getsid */
	{ 1, s(struct linux_sys_fdatasync_args),
	    linux_sys_fdatasync },		/* 148 = fdatasync */
	{ 1, s(struct linux_sys___sysctl_args),
	    linux_sys___sysctl },		/* 149 = __sysctl */
	{ 2, s(struct sys_mlock_args),
	    sys_mlock },			/* 150 = mlock */
	{ 2, s(struct sys_munlock_args),
	    sys_munlock },			/* 151 = munlock */
	{ 0, 0,
	    linux_sys_mlockall },		/* 152 = mlockall */
	{ 0, 0,
	    linux_sys_munlockall },		/* 153 = munlockall */
	{ 2, s(struct linux_sys_sched_setparam_args),
	    linux_sys_sched_setparam },		/* 154 = sched_setparam */
	{ 2, s(struct linux_sys_sched_getparam_args),
	    linux_sys_sched_getparam },		/* 155 = sched_getparam */
	{ 3, s(struct linux_sys_sched_setscheduler_args),
	    linux_sys_sched_setscheduler },	/* 156 = sched_setscheduler */
	{ 1, s(struct linux_sys_sched_getscheduler_args),
	    linux_sys_sched_getscheduler },	/* 157 = sched_getscheduler */
	{ 0, 0,
	    linux_sys_sched_yield },		/* 158 = sched_yield */
	{ 1, s(struct linux_sys_sched_get_priority_max_args),
	    linux_sys_sched_get_priority_max },	/* 159 = sched_get_priority_max */
	{ 1, s(struct linux_sys_sched_get_priority_min_args),
	    linux_sys_sched_get_priority_min },	/* 160 = sched_get_priority_min */
	{ 0, 0,
	    linux_sys_sched_rr_get_interval },	/* 161 = sched_rr_get_interval */
	{ 2, s(struct sys_nanosleep_args),
	    sys_nanosleep },			/* 162 = nanosleep */
	{ 4, s(struct linux_sys_mremap_args),
	    linux_sys_mremap },			/* 163 = mremap */
	{ 3, s(struct linux_sys_setresuid16_args),
	    linux_sys_setresuid16 },		/* 164 = setresuid16 */
	{ 3, s(struct linux_sys_getresuid16_args),
	    linux_sys_getresuid16 },		/* 165 = getresuid16 */
	{ 0, 0,
	    linux_sys_vm86 },			/* 166 = vm86 */
	{ 0, 0,
	    linux_sys_query_module },		/* 167 = query_module */
	{ 3, s(struct sys_poll_args),
	    sys_poll },				/* 168 = poll */
	{ 0, 0,
	    linux_sys_nfsservctl },		/* 169 = nfsservctl */
	{ 3, s(struct linux_sys_setresgid16_args),
	    linux_sys_setresgid16 },		/* 170 = setresgid16 */
	{ 3, s(struct linux_sys_getresgid16_args),
	    linux_sys_getresgid16 },		/* 171 = getresgid16 */
	{ 0, 0,
	    linux_sys_prctl },			/* 172 = prctl */
	{ 1, s(struct linux_sys_rt_sigreturn_args),
	    linux_sys_rt_sigreturn },		/* 173 = rt_sigreturn */
	{ 4, s(struct linux_sys_rt_sigaction_args),
	    linux_sys_rt_sigaction },		/* 174 = rt_sigaction */
	{ 4, s(struct linux_sys_rt_sigprocmask_args),
	    linux_sys_rt_sigprocmask },		/* 175 = rt_sigprocmask */
	{ 2, s(struct linux_sys_rt_sigpending_args),
	    linux_sys_rt_sigpending },		/* 176 = rt_sigpending */
	{ 0, 0,
	    linux_sys_rt_sigtimedwait },	/* 177 = rt_sigtimedwait */
	{ 0, 0,
	    linux_sys_rt_queueinfo },		/* 178 = rt_queueinfo */
	{ 2, s(struct linux_sys_rt_sigsuspend_args),
	    linux_sys_rt_sigsuspend },		/* 179 = rt_sigsuspend */
	{ 4, s(struct linux_sys_pread_args),
	    linux_sys_pread },			/* 180 = pread */
	{ 4, s(struct linux_sys_pwrite_args),
	    linux_sys_pwrite },			/* 181 = pwrite */
	{ 3, s(struct linux_sys_chown16_args),
	    linux_sys_chown16 },		/* 182 = chown16 */
	{ 2, s(struct linux_sys_getcwd_args),
	    linux_sys_getcwd },			/* 183 = getcwd */
	{ 0, 0,
	    linux_sys_capget },			/* 184 = capget */
	{ 0, 0,
	    linux_sys_capset },			/* 185 = capset */
	{ 2, s(struct linux_sys_sigaltstack_args),
	    linux_sys_sigaltstack },		/* 186 = sigaltstack */
	{ 0, 0,
	    linux_sys_sendfile },		/* 187 = sendfile */
	{ 0, 0,
	    linux_sys_getpmsg },		/* 188 = getpmsg */
	{ 0, 0,
	    linux_sys_putpmsg },		/* 189 = putpmsg */
	{ 0, 0,
	    sys_vfork },			/* 190 = vfork */
	{ 2, s(struct linux_sys_ugetrlimit_args),
	    linux_sys_ugetrlimit },		/* 191 = ugetrlimit */
	{ 6, s(struct linux_sys_mmap2_args),
	    linux_sys_mmap2 },			/* 192 = mmap2 */
	{ 2, s(struct linux_sys_truncate64_args),
	    linux_sys_truncate64 },		/* 193 = truncate64 */
	{ 2, s(struct linux_sys_ftruncate64_args),
	    linux_sys_ftruncate64 },		/* 194 = ftruncate64 */
	{ 2, s(struct linux_sys_stat64_args),
	    linux_sys_stat64 },			/* 195 = stat64 */
	{ 2, s(struct linux_sys_lstat64_args),
	    linux_sys_lstat64 },		/* 196 = lstat64 */
	{ 2, s(struct linux_sys_fstat64_args),
	    linux_sys_fstat64 },		/* 197 = fstat64 */
	{ 0, 0,
	    linux_sys_lchown },			/* 198 = lchown */
	{ 0, 0,
	    linux_sys_getuid },			/* 199 = getuid */
	{ 0, 0,
	    linux_sys_getgid },			/* 200 = getgid */
	{ 0, 0,
	    sys_geteuid },			/* 201 = geteuid */
	{ 0, 0,
	    sys_getegid },			/* 202 = getegid */
	{ 0, 0,
	    linux_sys_setreuid },		/* 203 = setreuid */
	{ 0, 0,
	    linux_sys_setregid },		/* 204 = setregid */
	{ 2, s(struct sys_getgroups_args),
	    sys_getgroups },			/* 205 = getgroups */
	{ 2, s(struct sys_setgroups_args),
	    sys_setgroups },			/* 206 = setgroups */
	{ 0, 0,
	    linux_sys_fchown },			/* 207 = fchown */
	{ 3, s(struct sys_setresuid_args),
	    sys_setresuid },			/* 208 = setresuid */
	{ 3, s(struct sys_getresuid_args),
	    sys_getresuid },			/* 209 = getresuid */
	{ 3, s(struct sys_setresgid_args),
	    sys_setresgid },			/* 210 = setresgid */
	{ 3, s(struct sys_getresgid_args),
	    sys_getresgid },			/* 211 = getresgid */
	{ 0, 0,
	    linux_sys_chown },			/* 212 = chown */
	{ 1, s(struct sys_setuid_args),
	    sys_setuid },			/* 213 = setuid */
	{ 1, s(struct sys_setgid_args),
	    sys_setgid },			/* 214 = setgid */
	{ 1, s(struct linux_sys_setfsuid_args),
	    linux_sys_setfsuid },		/* 215 = setfsuid */
	{ 0, 0,
	    linux_sys_setfsgid },		/* 216 = setfsgid */
	{ 0, 0,
	    linux_sys_pivot_root },		/* 217 = pivot_root */
	{ 0, 0,
	    linux_sys_mincore },		/* 218 = mincore */
	{ 0, 0,
	    linux_sys_madvise },		/* 219 = madvise */
	{ 3, s(struct linux_sys_getdents64_args),
	    linux_sys_getdents64 },		/* 220 = getdents64 */
	{ 3, s(struct linux_sys_fcntl64_args),
	    linux_sys_fcntl64 },		/* 221 = fcntl64 */
	{ 0, 0,
	    sys_nosys },			/* 222 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 223 = unimplemented */
	{ 0, 0,
	    sys_nosys },			/* 224 = unimplemented linux_sys_gettid */
	{ 0, 0,
	    sys_nosys },			/* 225 = unimplemented linux_sys_readahead */
	{ 0, 0,
	    sys_nosys },			/* 226 = unimplemented linux_sys_setxattr */
	{ 0, 0,
	    sys_nosys },			/* 227 = unimplemented linux_sys_lsetxattr */
	{ 0, 0,
	    sys_nosys },			/* 228 = unimplemented linux_sys_fsetxattr */
	{ 0, 0,
	    sys_nosys },			/* 229 = unimplemented linux_sys_getxattr */
	{ 0, 0,
	    sys_nosys },			/* 230 = unimplemented linux_sys_lgetxattr */
	{ 0, 0,
	    sys_nosys },			/* 231 = unimplemented linux_sys_fgetxattr */
	{ 0, 0,
	    sys_nosys },			/* 232 = unimplemented linux_sys_listxattr */
	{ 0, 0,
	    sys_nosys },			/* 233 = unimplemented linux_sys_llistxattr */
	{ 0, 0,
	    sys_nosys },			/* 234 = unimplemented linux_sys_flistxattr */
	{ 0, 0,
	    sys_nosys },			/* 235 = unimplemented linux_sys_removexattr */
	{ 0, 0,
	    sys_nosys },			/* 236 = unimplemented linux_sys_lremovexattr */
	{ 0, 0,
	    sys_nosys },			/* 237 = unimplemented linux_sys_fremovexattr */
	{ 0, 0,
	    sys_nosys },			/* 238 = unimplemented linux_sys_tkill */
	{ 0, 0,
	    sys_nosys },			/* 239 = unimplemented linux_sys_sendfile64 */
	{ 0, 0,
	    sys_nosys },			/* 240 = unimplemented linux_sys_futex */
	{ 0, 0,
	    sys_nosys },			/* 241 = unimplemented linux_sys_sched_setaffinity */
	{ 0, 0,
	    sys_nosys },			/* 242 = unimplemented linux_sys_sched_getaffinity */
	{ 0, 0,
	    sys_nosys },			/* 243 = unimplemented linux_sys_set_thread_area */
	{ 0, 0,
	    sys_nosys },			/* 244 = unimplemented linux_sys_get_thread_area */
	{ 0, 0,
	    sys_nosys },			/* 245 = unimplemented linux_sys_io_setup */
	{ 0, 0,
	    sys_nosys },			/* 246 = unimplemented linux_sys_io_destroy */
	{ 0, 0,
	    sys_nosys },			/* 247 = unimplemented linux_sys_io_getevents */
	{ 0, 0,
	    sys_nosys },			/* 248 = unimplemented linux_sys_io_submit */
	{ 0, 0,
	    sys_nosys },			/* 249 = unimplemented linux_sys_io_cancel */
	{ 0, 0,
	    sys_nosys },			/* 250 = unimplemented linux_sys_fadvise64 */
	{ 0, 0,
	    sys_nosys },			/* 251 = unimplemented */
	{ 1, s(struct sys_exit_args),
	    sys_exit },				/* 252 = exit */
	{ 0, 0,
	    sys_nosys },			/* 253 = unimplemented linux_sys_lookup_dcookie */
	{ 0, 0,
	    sys_nosys },			/* 254 = unimplemented linux_sys_epoll_create */
	{ 0, 0,
	    sys_nosys },			/* 255 = unimplemented linux_sys_epoll_ctl */
	{ 0, 0,
	    sys_nosys },			/* 256 = unimplemented linux_sys_epoll_wait */
	{ 0, 0,
	    sys_nosys },			/* 257 = unimplemented linux_sys_remap_file_pages */
	{ 0, 0,
	    sys_nosys },			/* 258 = unimplemented linux_sys_set_tid_address */
	{ 0, 0,
	    sys_nosys },			/* 259 = unimplemented linux_sys_timer_create */
	{ 0, 0,
	    sys_nosys },			/* 260 = unimplemented linux_sys_timer_settime */
	{ 0, 0,
	    sys_nosys },			/* 261 = unimplemented linux_sys_timer_gettime */
	{ 0, 0,
	    sys_nosys },			/* 262 = unimplemented linux_sys_timer_getoverrun */
	{ 0, 0,
	    sys_nosys },			/* 263 = unimplemented linux_sys_timer_delete */
	{ 0, 0,
	    sys_nosys },			/* 264 = unimplemented linux_sys_clock_settime */
	{ 0, 0,
	    sys_nosys },			/* 265 = unimplemented linux_sys_clock_gettime */
	{ 0, 0,
	    sys_nosys },			/* 266 = unimplemented linux_sys_clock_getres */
	{ 0, 0,
	    sys_nosys },			/* 267 = unimplemented linux_sys_clock_nanosleep */
};

