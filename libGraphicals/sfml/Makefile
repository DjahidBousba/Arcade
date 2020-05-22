##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

CC		=	g++

SRC		=	./Sfml.cpp

CFLAGS	=	-Wall -Werror -Wextra -g -lsfml-window -lsfml-graphics -lsfml-system -I ../ -I ../../include

NAME	=	lib_arcade_sfml.so

all:
	$(CC) $(CFLAGS) -fPIC -shared -o $(NAME) $(SRC)
	mv $(NAME) ../../lib

clean:
	rm -rf ../../lib/$(NAME)

fclean: clean

re:
	fclean all