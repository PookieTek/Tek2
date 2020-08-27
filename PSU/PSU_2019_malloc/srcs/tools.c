/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/mylloc.h"

int allignsize(size_t size)
{
    int res = 0;

    res = size * 2;
    return res;
}

mylloc_t *mylloc_init(int size)
{
    mylloc_t *tmp;
    size_t new = allignsize(size + sizeof(mylloc_t));

    tmp = (mylloc_t *)sbrk(new);
    tmp->next = NULL;
    tmp->previous = NULL;
    tmp->is_fill = 0;
    tmp->size = new + sizeof(mylloc_t);
    tmp->ptr = sbrk(new);
    return tmp;
}

mylloc_t *new_block(size_t size, mylloc_t *block)
{
    while (block != NULL && block->next != NULL) {
        if (block->is_fill < 1 && size <= block->size)
            return block;
        block = block->next;
    }
    return NULL;
}

void *add_block(size_t size, mylloc_t *block)
{
    void *ptr = sbrk(size + sizeof(mylloc_t));

    if (ptr == (void *)-1)
        return NULL;
    while (block->next != NULL)
        block = block->next;
    block->next = ptr;
    block->next->next = NULL;
    block->next->previous = block;
    block->next->is_fill = 0;
    block->next->size = size;
    block->next->ptr = ptr + sizeof(mylloc_t);
    return (block->next);
}
