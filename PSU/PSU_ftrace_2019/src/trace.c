/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** exec_s.c
*/

#include "strace.h"
#include "syscall.h"

int opcode_exist(int opcode, int *index)
{
    for (int a = 0; a <= MAX_OPCODE; a++) {
        if (opcode == my_syscall[a].opcode) {
            *index = a;
            return (SUCCESS);
        }
    }
    return (FAILURE);
}

static void display_args(struct user_regs_struct *regs, int nb)
{
    long long unsigned int args[6];

    args[0] = regs->rdi;
    args[1] = regs->rsi;
    args[2] = regs->rdx;
    args[3] = regs->rcx;
    args[4] = regs->r8;
    args[5] = regs->r9;
    for (int a = 0; a < nb; a++) {
        fprintf(stderr, "0x%llx", args[a]);
        if (a != (nb - 1))
            fprintf(stderr, ", ");
    }
}

static void display_info(struct user_regs_struct *regs, pid_t pid)
{
    int index = -1;

    if (regs->rax <= MAX_OPCODE && opcode_exist(regs->rax, &index) == SUCCESS) {
        fprintf(stderr, "%s(", my_syscall[index].name);
        display_args(regs, my_syscall[index].nb_args);
    } else {
        fprintf(stderr, "Ox%lld(Ox%llx, Ox%llx, ", regs->rax, regs->rdi, regs->rsi);
        fprintf(stderr, "0x%llx, 0x%llx, 0x%llx, ", regs->rdx, regs->rcx, regs->r8);
        fprintf(stderr, "0x%llx",regs->r9);
    }
    ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
    ptrace(PTRACE_GETREGS, pid, 0, &regs);
    if (index != -1 && my_syscall[index].ret == VOID)
        fprintf(stderr, ") = ?\n");
    else
        fprintf(stderr, ") = 0x%llx\n", regs->rax);
}

int trace(pid_t pid)
{
    int wstatus;
    int opcode;
    struct user_regs_struct regs;

    while (waitpid(pid, &wstatus, 0) && !WIFEXITED(wstatus)) {
        ptrace(PTRACE_GETREGS, pid, 0, &regs);
        opcode = ptrace(PTRACE_PEEKDATA, pid, regs.rip, 0);
        opcode &= 0xffff;
        if (opcode == 0xcd80 || opcode == 0x050f)
            display_info(&regs, pid);
        ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
    }
    return (SUCCESS);
}

