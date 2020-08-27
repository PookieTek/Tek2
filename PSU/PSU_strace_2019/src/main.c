/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** main.c
*/

#include "strace.h"

static int display_usage(int ac)
{
    fprintf(stderr, "USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    if (ac < 2)
        return (ERROR);
    return (SUCCESS);
}

int main (int ac, char ** av)
{
    if (ac < 2 || search_args(av, "--help") == SUCCESS)
        return(display_usage(ac));
    return (init_trace(av, ac, (2 + mystrcmp(av[1], "-s"))));
}