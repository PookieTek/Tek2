##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

NAME	=	GAME


all: $(NAME)

$(NAME):
	@make game

game: 
	@make -C snake
	@mv snake/*.so .
	@make -C qix
	@mv qix/*.so .

re:
	@make -C snake re
	@mv snake/*.so .
	@make -C qix re
	@mv qix/*.so .

fclean:
	@make -C snake fclean
	@make -C qix fclean
	@rm -rf *.so

clean:
	@make -C snake clean
	@make -C qix clean

.PHONY:	all game re fclean clean
