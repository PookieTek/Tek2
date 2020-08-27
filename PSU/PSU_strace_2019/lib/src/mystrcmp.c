/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** mystrcmp.c
*/

#include "lib.h"

int mystrcmp(char *s1, char *s2)
{
    if (mystrlen(s1) != mystrlen(s2))
        return (FAILURE);
    for (int a = 0; s1[a] && s2[a]; a++) {
        if (s1[a] != s2[a])
            return (FAILURE);
    }
    return (SUCCESS);
}