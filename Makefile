##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

CC		=	g++

SRC		=	./src/Main.cpp \
			./src/Core.cpp \
			./src/Errors.cpp \
			./src/Entity.cpp

CFLAGS	=	-Wall -Werror -Wextra -g -I ./include -I ./libGraphicals -I ./libGames

NAME	=	arcade

all: core graphicals games

core:
	$(CC) $(CFLAGS) -ldl -rdynamic -o $(NAME) $(SRC)

graphicals:
	make ncursesLib -C ./libGraphicals
	make sfmlLib -C ./libGraphicals
	make openglLib -C ./libGraphicals

games:
	make nibblerLib -C ./libGames
	make pacmanLib -C ./libGames

clean:
	make clean -C ./libGraphicals
	make clean -C ./libGames
	rm -rf $(NAME)

fclean: clean
	make fclean -C ./libGraphicals
	make fclean -C ./libGames
	rm -rf $(NAME)

re: fclean all

.PHONY:			games	core	opengl