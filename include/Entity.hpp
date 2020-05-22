/*
** EPITECH PROJECT, 2020
** Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

enum Shape {
    CIRCLE,
    RECT
};

class Entity {
    public:
        Entity(const Shape &shape, const std::vector<float> &size, const std::vector<int> &color, int ncursesColor);
        ~Entity();

        const Shape &getShape() const;
        const std::vector<float> &getSize() const;
        const std::vector<int> &getColor() const;
        int getncursesColor() const;

    protected:
    private:
        Shape _shape;
        std::vector<float> _size;
        std::vector<int> _color;
        int _ncursesColor;
};

#endif /* !ENTITY_HPP */
