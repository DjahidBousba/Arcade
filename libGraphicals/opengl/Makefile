##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Arcade
##

CC		=	g++

SRC		=	./OpenGL.cpp

CFLAGS	=	-Wall -Werror -Wextra -g -I ../ -I ../../include

NAME	=	lib_arcade_opengl.so

all:
	$(CC) $(CFLAGS) -fPIC -shared -ldl -o $(NAME) $(SRC) -lsfml-graphics -lsfml-window -lsfml-system -lm -lGLU -lGL
	mv $(NAME) ../../lib

clean:
	rm -rf ../../lib/$(NAME)

fclean: clean

re:
	fclean all