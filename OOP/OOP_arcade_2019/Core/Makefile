##
## EPITECH PROJECT, 2020
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	main.cpp 	\
		core.cpp	\
		event.cpp	\
		lib.cpp		\
		tools.cpp	\
		handle.cpp

NAME	=	arcade

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I include

SRCDIR	+=	./srcs/

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.cpp=.o))

all:	$(NAME)

$(NAME):	$(OBJ)
		@echo Compiling Core
		@g++ $(CPPFLAGS) $(CFLAGS) -o $(NAME) $(OBJ) -ldl
		@echo Core Compiled
		@make clean


clean:
	@rm -f $(OBJ)
	@echo Core Cleaned

fclean: clean
	@rm -f $(NAME)
	@rm -f *#
	@rm -f *~

re:	fclean all

.PHONY:	all clean re fclean
