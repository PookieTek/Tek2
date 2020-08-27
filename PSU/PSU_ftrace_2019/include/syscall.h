/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** syscall.h
*/

#ifndef _SYSCALL_
#define _SYSCALL_

#define MAX_OPCODE 435

typedef enum {
    VOID = 0,
    RET = 1,
} syscall_return_enum_t;

typedef struct syscall_s
{
    int opcode;
    short ret;
    char *name;
    short nb_args;
} syscall_t;

syscall_t my_syscall[] =
{
    {0, RET, "read", 3},
    {1, RET, "write", 3},
    {2, RET, "open", 2},
    {3, RET, "close", 1},
    {4, RET, "stat", 2},
    {5, RET, "fstat", 2},
    {6, RET, "lstat", 2},
    {7, RET, "poll", 3},
    {8, RET, "lseek", 3},
    {9, RET, "mmap", 6},
    {10, RET, "mprotect", 3},
    {11, RET, "munmap", 2},
    {12, RET, "brk", 1},
    {13, RET, "sigaction", 3},
    {14, RET, "sigprocmask", 3},
    {15, RET, "sigreturn", 1},
    {16, RET, "ioctl", 2},
    {17, RET, "pread64", 4},
    {18, RET, "pwrite64", 4},
    {19, RET, "readv", 3},
    {20, RET, "writev", 3},
    {21, RET, "access", 2},
    {22, RET, "pipe", 1},
    {23, RET, "select", 5},
    {24, RET, "sched_yield", 0},
    {25, RET, "mremap", 5},
    {26, RET, "msync", 3},
    {27, RET, "mincore", 3},
    {28, RET, "madvise", 3},
    {29, RET, "shmget", 3},
    {30, RET, "shmat", 3},
    {31, RET, "shmctl", 3},
    {32, RET, "dup", 1},
    {33, RET, "dup2", 2},
    {34, RET, "pause", 0},
    {35, RET, "nanosleep", 2},
    {36, RET, "getitimer", 2},
    {37, RET, "alarm", 1},
    {38, RET, "setitimer", 3},
    {39, RET, "getpid", 0},
    {40, RET, "sendfile", 4},
    {41, RET, "socket", 3},
    {42, RET, "connect", 3},
    {43, RET, "accept", 3},
    {44, RET, "sendto", 6},
    {45, RET, "recvfrom", 6},
    {46, RET, "sendmsg", 3},
    {47, RET, "recvmsg", 3},
    {48, RET, "shutdown", 2},
    {49, RET, "bind", 3},
    {50, RET, "listen", 2},
    {51, RET, "getsockname", 3},
    {52, RET, "getpeername", 3},
    {53, RET, "socketpair", 4},
    {54, RET, "setsockopt", 5},
    {55, RET, "getsockopt", 5},
    {56, RET, "clone", 5},
    {57, RET, "fork", 0},
    {58, RET, "vfork", 0},
    {59, RET, "execve", 3},
    {60, VOID, "exit", 1},
    {61, RET, "wait4", 4},
    {62, RET, "kill", 2},
    {63, RET, "uname", 1},
    {64, RET, "semget", 3},
    {65, RET, "semop", 3},
    {66, RET, "semctl", 4},
    {67, RET, "shmdt", 1},
    {68, RET, "msgget", 2},
    {69, RET, "msgsnd", 4},
    {70, RET, "msgrcv", 5},
    {71, RET, "msgctl", 3},
    {72, RET, "fcntl", 3},
    {73, RET, "flock", 2},
    {74, RET, "fsync", 1},
    {75, RET, "fdatasync", 1},
    {76, RET, "truncate", 2},
    {77, RET, "ftrucate", 2},
    {78, RET, "getdents", 3},
    {79, RET, "getcwd", 2},
    {80, RET, "chdir", 1},
    {81, RET, "fchdir", 1},
    {82, RET, "rename", 2},
    {83, RET, "mkdir", 2},
    {84, RET, "rmdir", 1},
    {85, RET, "creat", 2},
    {86, RET, "link", 2},
    {87, RET, "unlink", 1},
    {88, RET, "symlink", 2},
    {89, RET, "readlink", 3},
    {90, RET, "chmod", 2},
    {91, RET, "fchmod", 2},
    {92, RET, "chown", 3},
    {93, RET, "fchown", 3},
    {94, RET, "lchown", 3},
    {95, RET, "umask", 1},
    {96, RET, "gettimeofday", 2},
    {97, RET, "getrlimit", 2},
    {98, RET, "getrusage", 2},
    {99, RET, "sysinfo", 1},
    {100, RET, "times", 1},
    {101, RET, "ptrace", 4},
    {102, RET, "getuid", 0},
    {103, RET, "syslog", 2},
    {104, RET, "getgid", 0},
    {105, RET, "setuid", 1},
    {106, RET, "setgid", 1},
    {107, RET, "geteuid", 0},
    {108, RET, "getegid", 0},
    {109, RET, "setpgid", 2},
    {110, RET, "getppid", 0},
    {111, RET, "getpgrp", 0},
    {112, RET, "setsid", 0},
    {113, RET, "setreuid", 2},
    {114, RET, "setregid", 2},
    {115, RET, "getgroups", 2},
    {116, RET, "setgroups", 2},
    {117, RET, "setresuid", 3},
    {118, RET, "getresuid", 3},
    {119, RET, "setresgid", 3},
    {120, RET, "getresgid", 3},
    {121, RET, "getpgid", 1},
    {122, RET, "setfsuid", 1},
    {123, RET, "setfsgid", 1},
    {124, RET, "getsid", 1},
    {125, RET, "capget", 2},
    {126, RET, "capset", 2},
    {127, RET, "rt_sigpending", 1},
    {128, RET, "rt_sigtimedwait", 3},
    {129, RET, "rt_sigqueueinfo", 3},
    {130, RET, "rt_sigsuspend", 1},
    {131, RET, "sigaltstack", 2},
    {132, RET, "utime", 2},
    {133, RET, "mknod", 3},
    {134, RET, "uselib", 1},
    {135, RET, "personality", 1},
    {136, RET, "ustat", 2},
    {137, RET, "statfs", 2},
    {138, RET, "fstatfs", 2},
    {139, RET, "sysfs", 2},
    {140, RET, "getpriority", 2},
    {141, RET, "setpriority", 3},
    {142, RET, "sched_setparam", 2},
    {143, RET, "sched_getparam", 2},
    {144, RET, "sched_setscheduler", 3},
    {145, RET, "sched_getscheduler", 1},
    {146, RET, "sched_get_priority_max", 1},
    {147, RET, "sched_get_priority_min", 1},
    {148, RET, "sched_rr_get_interval", 2},
    {149, RET, "mlock", 2},
    {150, RET, "munlock", 2},
    {151, RET, "mlockall", 1},
    {152, RET, "munlockall", 0},
    {153, RET, "vhangup", 0},
    {154, RET, "modify_ldt", 3},
    {155, RET, "pivot_root", 2},
    {156, RET, "sysctl", 1},
    {157, RET, "prctl", 5},
    {158, RET, "arch_prctl", 2},
    {159, RET, "adjtimex", 1},
    {160, RET, "setrlimit", 2},
    {161, RET, "chroot", 1},
    {162, VOID, "sync", 0},
    {163, RET, "acct", 1},
    {164, RET, "settimeofday", 2},
    {165, RET, "mount", 5},
    {166, RET, "umount2", 2},
    {167, RET, "swapon", 2},
    {168, RET, "swapoff", 1},
    {169, RET, "reboot", 4},
    {170, RET, "sethostname", 2},
    {171, RET, "setdomainname", 2},
    {172, RET, "iopl", 1},
    {173, RET, "ioperm", 3},
    {174, RET, "create_module", 2},
    {175, RET, "init_module", 3},
    {176, RET, "delete_module", 2},
    {177, RET, "get_kernel_syms", 1},
    {178, RET, "query_module", 5},
    {179, RET, "quotactl", 4},
    {180, RET, "nfsservctl", 3},
    {181, RET, "getpmsg", 5},
    {182, RET, "putpmsg", 4},
    {183, VOID, "afs_syscall", 0},
    {184, VOID, "tuxcall", 0},
    {185, VOID, "security", 0},
    {186, RET, "gettid", 0},
    {187, RET, "readahead", 3},
    {188, RET, "setxattr", 5},
    {189, RET, "lsetxattr", 5},
    {190, RET, "fsetxattr", 5},
    {191, RET, "getxattr", 4},
    {192, RET, "lgetxattr", 4},
    {193, RET, "fgetxattr", 4},
    {194, RET, "listxattr", 3},
    {195, RET, "llistxattr", 3},
    {196, RET, "flistxattr", 3},
    {197, RET, "removexattr", 2},
    {198, RET, "lremovexattr", 2},
    {199, RET, "fremovexattr", 2},
    {200, RET, "tkill", 2},
    {201, RET, "time", 1},
    {202, RET, "futex", 6},
    {203, RET, "sched_setaffinity", 3},
    {204, RET, "sched_getaffinity", 3},
    {205, RET, "set_thread_area", 1},
    {206, RET, "io_setup", 2},
    {207, RET, "io_destroy", 1},
    {208, RET, "io_getevents", 5},
    {209, RET, "io_submit", 3},
    {210, RET, "io_cancel", 3},
    {211, RET, "get_thread_area", 1},
    {212, RET, "lookup_dcookie", 3},
    {213, RET, "epoll_create", 1},
    {214, RET, "epoll_ctl_old", 4},
    {215, RET, "epoll_wait_old", 4},
    {216, RET, "remap_file_pages", 5},
    {217, RET, "getdents64", 3},
    {218, RET, "set_tid_address", 1},
    {219, RET, "restart_syscall", 0},
    {220, RET, "semtimedop", 4},
    {221, RET, "fadvise64", 4},
    {222, RET, "timer_create", 3},
    {223, RET, "timer_settime", 4},
    {224, RET, "timer_gettime", 2},
    {225, RET, "timer_getoverrun", 1},
    {226, RET, "timer_delete", 1},
    {227, RET, "clock_settime", 2},
    {228, RET, "clock_gettime", 2},
    {229, RET, "clock_getres", 2},
    {230, RET, "clock_nanosleep", 4},
    {231, VOID, "exit_group", 1},
    {232, RET, "epoll_wait", 4},
    {233, RET, "epoll_ctl", 4},
    {234, RET, "tgkill", 3},
    {235, RET, "utimes", 2},
    {236, VOID, "vserver", 0},
    {237, RET, "mbind", 6},
    {238, RET, "set_mempolicy", 3},
    {239, RET, "get_mempolicy", 5},
    {240, RET, "mq_open", 4},
    {241, RET, "mq_unlink", 1},
    {242, RET, "mq_timedsend", 5},
    {243, RET, "mq_timedreceive", 5},
    {244, RET, "mq_notify", 2},
    {245, RET, "mq_getsetattr", 3},
    {246, RET, "kexec_load", 4},
    {247, RET, "waitid", 4},
    {248, RET, "add_key", 5},
    {249, RET, "request_key", 4},
    {250, RET, "keyctl", 1},
    {251, RET, "ioprio_set", 3},
    {252, RET, "ioprio_get", 2},
    {253, RET, "inotify_init", 0},
    {254, RET, "inotify_add_watch", 3},
    {255, RET, "inotify_rm_watch", 2},
    {256, RET, "migrate_pages", 4},
    {257, RET, "openat", 3},   
    {258, RET, "mkdirat", 3},
    {259, RET, "mknodat", 4},
    {260, RET, "fchownat", 5},
    {261, RET, "futimesat", 3},
    {262, RET, "newfstatat", 4},
    {263, RET, "unlinkat", 3},
    {264, RET, "renameat", 4},
    {265, RET, "linkat", 5},
    {266, RET, "symlinkat", 3},
    {267, RET, "readlinkat", 4},
    {268, RET, "fchmodat", 4},
    {269, RET, "faccessat", 4},
    {270, RET, "pselect6", 6},
    {271, RET, "ppoll", 4},
    {272, RET, "unshare", 1},
    {273, RET, "set_robust_list", 2},
    {274, RET, "get_robust_list", 3},
    {275, RET, "splice", 6},
    {276, RET, "tee", 4},
    {277, RET, "sync_file_range", 4},
    {278, RET, "vmsplice", 4},
    {279, RET, "move_pages", 5},
    {280, RET, "utimensat", 4},
    {281, RET, "epoll_pwait", 5},
    {282, RET, "signalfd", 3},
    {283, RET, "timerfd_create", 2},
    {284, RET, "eventfd", 2},
    {285, RET, "fallocate", 4},
    {286, RET, "timerfd_settime", 4},
    {287, RET, "timerfd_gettime", 2},
    {288, RET, "accept4", 4},
    {289, RET, "signalfd4", 3},
    {290, RET, "eventfd2", 2},
    {291, RET, "epoll_create1", 1},
    {292, RET, "dup3", 3},
    {293, RET, "pipe2", 2},
    {294, RET, "inotify_init1", 1},
    {295, RET, "preadv", 4},
    {296, RET, "pwritev", 4},
    {297, RET, "rt_tgsigqueueinfo", 4},
    {298, RET, "perf_event_open", 5},
    {299, RET, "recvmmsg", 5},
    {300, RET, "fanotify_init", 2},
    {301, RET, "fanotify_mark", 5},
    {302, RET, "prlimit64", 4},
    {303, RET, "name_to_handle_at", 5},
    {304, RET, "open_by_handle_at", 3},
    {305, RET, "clock_adjtime", 2},
    {306, RET, "syncfs", 1},
    {307, RET, "sendmmsg", 4},
    {308, RET, "setns", 2},
    {309, RET, "getcpu", 3},
    {310, RET, "process_vm_readv", 6},
    {311, RET, "process_vm_writev", 6},
    {312, RET, "kcmp", 5},
    {313, RET, "finit_module", 3},
    {314, RET, "sched_setattr", 3},
    {315, RET, "sched_getattr", 4},
    {316, RET, "renameat2", 5},
    {317, RET, "seccomp", 3},
    {318, RET, "getrandom", 3},
    {319, RET, "memfd_create", 2},
    {320, RET, "kexec_file_load", 5},
    {321, RET, "bpf", 3},
    {322, RET, "execveat", 5},
    {323, RET, "userfaultfd", 1},
    {324, RET, "membarrier", 2},
    {325, RET, "mlock2", 3},
    {326, RET, "copy_file_range", 6},
    {327, RET, "preadv2", 5},
    {328, RET, "pwritev2", 5},
    {329, RET, "pkey_mprotect", 4},
    {330, RET, "pkey_alloc", 2},
    {331, RET, "pkey_free", 1},
    {332, RET, "statx", 5},
    {333, RET, "io_pgetevents", 5},
    {334, RET, "rseq", 4},
    {424, RET, "pidfd_send_signal", 4},
    {425, RET, "io_uring_setup", 2},
    {426, RET, "io_uring_enter", 5},
    {427, RET, "io_uring_register", 4},
    {428, RET, "open_tree", 3},
    {429, RET, "move_mount", 5},
    {430, RET, "fsopen", 2},
    {431, RET, "fsconfig", 5},
    {432, RET, "fsmount", 3},
    {433, RET, "fspick", 3},
    {434, RET, "pidfd_open", 2},
    {435, RET, "clone3", 2},
};

#endif