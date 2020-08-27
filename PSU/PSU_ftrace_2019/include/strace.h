/*
** EPITECH PROJECT, 2019
** PSU_strace_2019
** File description:
** strace.h
*/

#ifndef _STRACE_
#define _STRACE_

#include "lib.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>

typedef enum {
    OPTION_S = 2,
    NO_OPTION = 1,
} strace_enum_t;

int init_trace(char **av, int ac, int opt);
int trace(pid_t pid);

#endif