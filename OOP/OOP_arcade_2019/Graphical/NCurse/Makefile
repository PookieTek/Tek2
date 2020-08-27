##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	ncurse.cpp	\
		tools.cpp	\
		display.cpp	\
		game.cpp

NAME	=	lib_arcade_ncurses.so


CPPFLAGS	=	-I include

SRCDIR += ./srcs/

OBJ =	$(addprefix $(SRCDIR), $(SRC))

all:	$(NAME)

$(NAME):
	@echo Compiling NCurses
	@g++ $(CPPFLAGS) -lncurses $(OBJ) -fPIC -shared -ldl -o $(NAME)
	@echo NCurses Compiled

clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f *#
	@rm -f *~

re: fclean all

.PHONY:	all clean re fclean