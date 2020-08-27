/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** block
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/mylloc.h"

mylloc_t *remove_block(mylloc_t *block)
{
    mylloc_t *tmp = block;
    block->is_fill = 1;
    if (block->next == NULL && block->previous != NULL) {
        block->previous->next = NULL;
    } else if (block->next == NULL) {
        if (block->previous == NULL)
            tmp = NULL;
        sbrk(-1 * (sizeof(mylloc_t) + block->size));
    }
    return tmp;
}