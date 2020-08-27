##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

NAME	=	CORE


all: $(NAME)

$(NAME):
	@make core
	@make games
	@make graphicals

core: 
	@make -C Core
	@cp Core/arcade .

games:
	@make -C Game
	@cp -rf Game/*.so games/.

graphicals:
	@make -C Graphical
	@cp -rf Graphical/*.so lib/.

re:
	@make -C Core re
	@cp Core/arcade arcade
	@make -C Game re
	@cp -rf Game/*.so games/.
	@make -C Graphical re
	@cp -rf Graphical/*.so lib/.

fclean:
	@make -C Core fclean
	@make -C Game fclean
	@make -C Graphical fclean
	@rm -rf lib/*.so
	@rm -rf games/*.so
	@rm -f arcade


clean:
	@make -C Core clean
	@make -C Game clean
	@make -C Graphical clean

.PHONY:	all core games graphicals re fclean clean
