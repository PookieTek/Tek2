##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

NAME	=	GRAPHICAL

all: $(NAME)

$(NAME):
	@make graphical

graphical:
	@make -C SFML
	@mv SFML/lib_arcade_sfml.so .
	@make -C NCurse
	@mv NCurse/lib_arcade_ncurses.so .

re:
	@make -C SFML re
	@mv SFML/lib_arcade_sfml.so .
	@make -C NCurse re
	@mv NCurse/lib_arcade_ncurses.so .

fclean:
	@make -C SFML fclean
	@make -C NCurse fclean
	@rm -rf *.so

clean:
	@make -C SFML clean
	@make -C NCurse clean

.PHONY: all graphical re fclean clean