/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** lib.h
*/

#ifndef _LIB_
#define _LIB_

typedef enum {
    ERROR = 84,
    SUCCESS = 0,
    FAILURE = -1,
} lib_enum_t;


int mystrlen(char *str);
int mystrcmp(char *s1, char *s2);
int exit_error(char *str);
int search_args(char **tab, char *str);

#endif