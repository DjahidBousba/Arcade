##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

CC		=	g++

SRC		=	./Pacman.cpp

CFLAGS	=	-Wall -Werror -Wextra -g -I ../ -I ../../include

NAME	=	lib_arcade_pacman.so

all:
	$(CC) $(CFLAGS) -fPIC -shared -ldl -o $(NAME) $(SRC)
	mv $(NAME) ../../games

clean:
	rm -rf ../../games/$(NAME)

fclean: clean

re:
	fclean all