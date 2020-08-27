##
## EPITECH PROJECT, 2019
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

NAME	=	IMAGECOMPRESSOR

all:	$(NAME)

$(NAME):
	@cd ./compressor && \
	stack build
	@make -C compressor

clean:
	@cd ./compressor && stack clean
fclean:
	@cd ./compressor && stack purge
	@rm -f imageCompressor
re: 
	@make fclean 
	@make all


.PHONY:	all fclean clean re