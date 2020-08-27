##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	mystrlen.c	\
		mystrcmp.c	\
		exit_error.c	\
		search_args.c

NAME	=	libmy.a

CFLAGS	=	-Wall -Wextra -I include

SRCDIR	+=	./src/

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)


clean:
	rm -rf $(OBJ)


fclean: clean
	rm -f $(NAME)
	rm -f *#	\
	rm -f *~


re: fclean all


.PHONY: all clean re fclean