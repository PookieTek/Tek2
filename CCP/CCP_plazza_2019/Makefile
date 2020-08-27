##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

SRC		=		main.cpp		\
				reception.cpp	\
				cook.cpp		\
				kitchen.cpp		\
				pizza.cpp		\
				timer.cpp		\
				npipe.cpp		\
				tools.cpp		\
				process.cpp

NAME	=		plazza

CFLAGS	=		-Wall -Wextra

CPPFLAGS	=	-I include -lpthread

SRCDIR	+=	./srcs/

OBJ	=	$(addprefix $(SRCDIR), $(SRC:.cpp=.o))

all:	$(NAME)

$(NAME): $(OBJ)
		@rm -f $(NAME)
		@echo Compiling plazza
		@g++ $(CPPFLAGS) $(OBJ) $(CFLAGS) -o $(NAME)
		@echo plazza compiled
		@make clean


clean:
	@rm -rf $(OBJ)

fclean: clean
		@rm -f $(NAME)
		@rm -f *#
		@rm -f *~

re:		fclean all

.PHONY: all clean fclean re