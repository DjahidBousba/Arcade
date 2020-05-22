/*
** EPITECH PROJECT, 2020
** Entity
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity(const Shape &shape, const std::vector<float> &size, const std::vector<int> &color, int ncursesColor)
{
    _shape = shape;
    _size = size;
    _color = color;
    _ncursesColor = ncursesColor;
}

Entity::~Entity()
{
}

const Shape &Entity::getShape() const
{
    return (_shape);
}

const std::vector<float> &Entity::getSize() const
{
    return (_size);
}

const std::vector<int> &Entity::getColor() const
{
    return (_color);
}

int Entity::getncursesColor() const
{
    return (_ncursesColor);
}