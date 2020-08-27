##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC	=	malloc.c			\
		tools.c				\
		block.c
		
SRCDIR = ./srcs/

CFLAGS = -Wall -Wextra

CPPFLAGS = -I include

NAME	=	libmy_malloc.so

OBJ		=	$(addprefix $(SRCDIR), $(SRC:.c=.o))

all:	$(NAME)

$(NAME): 	$(OBJ)
	gcc -o $(NAME) -shared -fPIC $(addprefix $(SRCDIR), $(SRC))
	make clean

clean:
	rm -rf $(OBJ)
fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:	fclean all
