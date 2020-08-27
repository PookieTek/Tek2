##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC		=	main.hs	\
			error.hs	\
			rule30.hs	\
			rule90.hs 	 \
			rule110.hs

NAME	=	wolfram

OBJ		=	$(SRC:.hs=.o)

all: 	$(NAME)

$(NAME):
			ghc -o $(NAME) $(SRC)
			rm -f $(OBJ)
			rm -f *.hi
clean:
		rm -f $(OBJ)
		rm -f *.hi

fclean:	clean
		rm -f $(NAME)
		rm -f *#		\
		rm -f *~

re:	fclean all

.PHONY: 	all clean re fclean
