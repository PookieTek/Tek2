/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** init_trace.c
*/

#include "strace.h"

static int launch_child(char **av, int ac, int opt, int *pid)
{
    char *args[ac];
    int a = 0;

    for ( ; av[a + opt]; a++) {
        args[a] = av[a + opt];
    }
    args[a] = NULL;
    *pid = fork();
    if (*pid == FAILURE)
        return (ERROR);
    else if (*pid == 0) {
        ptrace(PT_TRACE_ME, *pid, NULL, NULL);
        execvp(args[0], args);
        return (ERROR);
    }
    return (SUCCESS);
}

int init_trace(char **av, int ac, int opt)
{
    pid_t pid;

    if (!av[opt])
            return (exit_error("Error\nThere Is No Command To Be Executed"));
    else if (mystrcmp(av[opt], "-p") == SUCCESS) {
        if (!av[opt + 1])
            return (exit_error("Error\nThere Is No Pid"));
        pid = atoi(av[opt + 1]);
    } else {
        if (launch_child(av, ac, opt, &pid) == ERROR)
            return (ERROR);
    }
    return (trace(pid));
}