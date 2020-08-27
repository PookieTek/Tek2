##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	sfml.cpp	\
		menu.cpp	\
		tools.cpp

NAME	=	lib_arcade_sfml.so

CPPFLAGS	=	-I include

SRCDIR += ./srcs/

OBJ =	$(addprefix $(SRCDIR), $(SRC))

SFML = -lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME):
	@echo Compiling SFML
	@g++ $(CPPFLAGS) $(SFML) $(OBJ) -fPIC -shared -ldl -o $(NAME)
	@echo SFML Compiled

clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f *#
	@rm -f *~

re: fclean all

.PHONY:	all clean re fclean