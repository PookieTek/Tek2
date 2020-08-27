##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	main.c	\
		init_trace.c	\
		trace.c

NAME	=	ftrace

CFLAGS	=	-Wall -Wextra -I include -I lib/include

SRCDIR	+=	./src/

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJ)
		make -C lib
		gcc $(OBJ) -o $(NAME) -L lib -lmy -g3


clean:
	rm -rf $(OBJ)
	make -C lib clean


fclean:
	rm -rf $(OBJ)
	make -C lib fclean
	rm -f $(NAME)
	rm -f *#	\
	rm -f *~


re: fclean all


.PHONY: all clean re fclean