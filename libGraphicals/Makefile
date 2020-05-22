##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

all: ncursesLib sfmlLib openglLib

ncursesLib:
	make -C ./ncurses

sfmlLib:
	make -C ./sfml

openglLib:
	make -C ./opengl

clean:
	make clean -C ./ncurses
	make clean -C ./sfml
	make clean -C ./opengl

fclean: clean
	make fclean -C ./ncurses
	make fclean -C ./sfml
	make fclean -C ./opengl

re:
	fclean all

.PHONY:			opengl