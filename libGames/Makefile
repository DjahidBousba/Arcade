##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

all: nibblerLib pacmanLib

nibblerLib:
	make -C ./nibbler

pacmanLib:
	make -C ./pacman

clean:
	make clean -C ./nibbler
	make clean -C ./pacman
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./nibbler
	make fclean -C ./pacman
	rm -rf $(NAME)

re:
	fclean all