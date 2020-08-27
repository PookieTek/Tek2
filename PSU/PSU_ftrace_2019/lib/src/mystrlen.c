/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** mystrlen.c
*/

int mystrlen(char *str)
{
    int a = 0;

    for ( ; str[a]; a++);
    return (a);
}