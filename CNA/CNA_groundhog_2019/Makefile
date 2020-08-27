##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

SRC		=		main.cpp		\
				groundhog.cpp	\
				run.cpp

NAME	=		groundhog

CFLAGS	=		-Wall -Wextra

CPPFLAGS	=	-I include

SRCDIR	+=	./srcs/

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.cpp=.o))

all:	$(NAME)

$(NAME): $(OBJ)
		@rm -f $(NAME)
		@echo Compiling Groundhog
		@g++ $(CPPFLAGS) $(OBJ) $(CFLAGS) -o $(NAME)
		@echo Groundhog compiled
		@make clean


clean:
	@rm -rf $(OBJ)

fclean: clean
		@rm -f $(NAME)
		@rm -f *#
		@rm -f *~

re:		fclean all

.PHONY: all clean fclean re