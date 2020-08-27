/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** malloc
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/mylloc.h"
#include <string.h>

mylloc_t *map = NULL;

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    void *tmp = ptr;

    for (int i = 0; i < nmemb; i++, ptr++) {
        ptr = sbrk(size);
    }
    return tmp;
}

void *realloc(void *ptr, size_t size)
{
    void *tmp = malloc(size);
    mylloc_t *block = map;

    while (block != NULL && block->next != NULL) {
        if (block->ptr == ptr) {
            block->size = size;
            break;
        }
    }
    tmp = memcpy(tmp, ptr, block->size);
    block->ptr = tmp;
    return tmp;
}

void free(void *ptr)
{
    mylloc_t *block = map;
    mylloc_t *tmp;

    if (ptr == NULL)
        return;
    while (block != NULL) {
        if (block->ptr == ptr) {
            tmp = remove_block(block);
            if (tmp == NULL)
                map = NULL;
            break;
        } else
            block = block->next;
    }
}

void *calloc(size_t nmemb, size_t size)
{
    char *ptr = malloc(nmemb * size);

    if (ptr == NULL)
        return NULL;
    for (int i = 0; i < size; i++)
        ptr[i] = 0;
    return ptr;
}

void *malloc(size_t size)
{
    mylloc_t *tmp;

    if (map == NULL) {
        map = mylloc_init(size);
        return (map->ptr);
    } if (!map || size == 0)
        return NULL;
    tmp = new_block(size, map);
    if (tmp)
        return (tmp->ptr);
    else {
        tmp = add_block(size, map);
        if (tmp != NULL)
            return (tmp->ptr);
    }
    return NULL;
}