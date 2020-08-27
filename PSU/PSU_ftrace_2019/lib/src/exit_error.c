/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** failure.c
*/

#include "lib.h"
#include <unistd.h>

int exit_error(char *str)
{
    write(2, str, mystrlen(str));
    write(2, "\n", 1);
    return (ERROR);
}