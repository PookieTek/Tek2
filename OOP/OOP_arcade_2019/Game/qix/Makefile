##
## EPITECH PROJECT, 2020
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	qix.cpp

NAME	=	lib_arcade_qix.so

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I include

SRCDIR	+=	./srcs/

OBJ = $(addprefix $(SRCDIR), $(SRC))

all:	$(NAME)


$(NAME):
		@echo Compiling Qix
		@g++ $(CPPFLAGS) $(OBJ) $(CFLAGS) -fPIC -shared -ldl -o $(NAME)
		@echo Qix Compiled
		@make clean

clean:
	@rm -f srcs/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f *#
	@rm -f *~

re:	fclean all

.PHONY:	all clean re fclean