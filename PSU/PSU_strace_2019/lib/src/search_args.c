/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** search_args.c
*/

#include "lib.h"

int search_args(char **av, char *str)
{
    for (int a = 1; av[a]; a++) {
        if (mystrcmp(av[a], str) == SUCCESS)
            return (SUCCESS);
    }
    return (FAILURE);
}