##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

CC		=	g++

SRC		=	./Ncurses.cpp

CFLAGS	=	-Wall -Werror -Wextra -g -I ../ -I ../../include

NAME	=	lib_arcade_ncurses.so

all:
	$(CC) $(CFLAGS) -fPIC -shared -ldl -o $(NAME) $(SRC) -lncurses
	mv $(NAME) ../../lib

clean:
	rm -rf ../../lib/$(NAME)

fclean: clean

re:
	fclean all