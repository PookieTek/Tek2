##
## EPITECH PROJECT, 2020
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	snake.cpp	\
		map.cpp 	\
		move.cpp

NAME	=	lib_arcade_nibbler.so


CPPFLAGS	=	-I include

SRCDIR	+=	./srcs/

OBJ	=	$(addprefix $(SRCDIR), $(SRC))

all:	$(NAME)


$(NAME):
		@echo Compiling Nibbler
		@g++ $(CPPFLAGS) $(OBJ) -fPIC -shared -ldl -o $(NAME)
		@echo Nibbler Compiled

clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f *#
	@rm -f *~

re:	fclean all

.PHONY:	all clean re fclean