/*
** EPITECH PROJECT, 2020
** Unix
** File description:
** mylloc
*/

#ifndef MYLLOC_H_
#define MYLLOC_H_

#include <unistd.h>

typedef struct mylloc_s {
    struct mylloc_s *next;
    struct mylloc_s *previous;
    size_t size;
    int is_fill;
    void *ptr;
} mylloc_t;

void *malloc(size_t);
void free(void *);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void *reallocarray(void *, size_t, size_t);

void *add_block(size_t size, mylloc_t *block);
mylloc_t *new_block(size_t size, mylloc_t *block);
mylloc_t *mylloc_init(int size);
int allignsize(size_t size);
mylloc_t *remove_block(mylloc_t *block);
#endif /* !MYLLOC_H_ */
