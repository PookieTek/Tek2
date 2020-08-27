##
## EPITECH PROJECT, 2020
## undefined
## File description:
## Makefile
##

CFLAGS	=	-shared -nostdlib

SRC		=	strlen.asm	\
			strchr.asm	\
			memcpy.asm	\
			memmove.asm	\
			memset.asm	\
			rindex.asm	\
			strcasecmp.asm	\
			strcmp.asm	\
			strcspn.asm	\
			strncmp.asm	\
			strpbrk.asm	\
			strstr.asm	\



NAME	=	libasm.so

OBJ		=	$(SRC:.asm=.o)

%.o: %.asm
	nasm -o $@ $< -f elf64

all:	$(NAME)

$(NAME):	$(OBJ)
		ld $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean
