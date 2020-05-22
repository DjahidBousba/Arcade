/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** nibbler
*/

#include "Nibbler.hpp"
#include <iostream>

Nibbler::Nibbler()
{
    _mapEntity = {
        {'X', Entity(RECT, {1.f, 1.f}, {255, 255, 255}, 8)},
        {'H', Entity(RECT, {1.f, 1.f}, {255, 0, 0}, 5)},
        {'P', Entity(RECT, {1.f, 1.f}, {0, 255, 0}, 7)},
        {'O', Entity(CIRCLE, {1.f, 1.f}, {0, 0, 255}, 6)}
    };
}

Nibbler::~Nibbler()
{
}

void Nibbler::initGame()
{
    this->_dir = LEFT_DIR;
    this->_snakeSize = 4;
    this->_score = 0;
    this->_name = "Nibbler";
    this->generateMap();
}

void Nibbler::resetGame()
{
    _map.clear();
    _allDir.clear();
}

const std::string& Nibbler::getName() const
{
    return (_name);
}

void Nibbler::generateMap()
{
    srand (time(NULL));
    std::string line;
    for (int j = 0; j < 22; j++) {
        _map.push_back("                                ");
        for (int i = 0; i < 32; i++) {
            if (j == 0 || j == 21 || i == 0 || i == 31)
                this->_map[j][i] = 'X';
            else
                this->_map[j][i] = ' ';
        }
    }
    this->generateSnake();
    this->createRandomWalls();
    this->generateFruit();
}

void Nibbler::createRandomWalls()
{
    int nbWalls = 20;
    int i = 0;
    int j = 0;

    while (nbWalls > 0) {
        i = rand() % (30 - 2) + 2;
        j = rand() % (20 - 2) + 2;
        if (j == 10)
            j += 1;
        if (_map[j][i] == ' ') {
            _map[j][i] = 'X';
            nbWalls -= 1;
        }
    }
}

void Nibbler::generateSnake()
{
    _map[10][13] = 'H';
    this->_head = std::make_pair(10, 13);
    for (int i = 0; i != 3; i++) {
        _map[10][i + 14] = 'P';
        if (i + 1 == 3)
            this->_tail = std::make_pair(10, i + 14);
        _allDir.push_back(LEFT_DIR);
    }
}

const std::vector<std::string> &Nibbler::getMap() const
{
    return (this->_map);
}

std::pair<int, int> Nibbler::findNewTail() const
{
    int x = this->_tail.first;
    int y = this->_tail.second;
    std::pair<int, int> tmp;

    if (_allDir.back() == UP_DIR && _map[x - 1][y] == 'P') {
        return (std::make_pair(x - 1, y));
    }
    if (_allDir.back() == DOWN_DIR && _map[x + 1][y] == 'P') {
        return (std::make_pair(x + 1, y));
    }
    if (_allDir.back() == LEFT_DIR && _map[x][y - 1] == 'P') {
        return (std::make_pair(x, y - 1));
    }
    if (_allDir.back() == RIGHT_DIR && _map[x][y + 1] == 'P') {
        return (std::make_pair(x, y + 1));
    }
    return (tmp);
}

int Nibbler::checkFreeCell() const
{
    int freeCell = 0;

     for (int j = 0; j < 22; j++) {
        for (int i = 0; i < 32; i++) {
            if (_map[j][i] == ' ')
                freeCell++;
        }
    }
    return (freeCell);
}

int Nibbler::refreshGame()
{
    std::pair<int, int> newTail = this->findNewTail();

    this->_map[this->_tail.first][this->_tail.second] = ' ';
    this->_map[this->_head.first][this->_head.second] = 'P';
    if (checkFreeCell() == 0)
        return (1);
    switch (_dir) {
        case UP_DIR:
            if (this->_map[this->_head.first - 1][this->_head.second] == 'X' || this->_map[this->_head.first - 1][this->_head.second] == 'P')
                return (1);
            if (eatFruit(UP_DIR, -1, 0) == 0)
                return (0);
            moveSnake(UP_DIR, -1, 0, newTail);
            break;
        case DOWN_DIR:
            if (this->_map[this->_head.first + 1][this->_head.second] == 'X' || this->_map[this->_head.first + 1][this->_head.second] == 'P')
                return (1);
            if (eatFruit(DOWN_DIR, 1, 0) == 0)
                return (0);
            moveSnake(DOWN_DIR, 1, 0, newTail);
            break;
        case LEFT_DIR:
            if (this->_map[this->_head.first][this->_head.second - 1] == 'X' || this->_map[this->_head.first][this->_head.second - 1] == 'P')
                return (1);
            if (eatFruit(LEFT_DIR, 0, -1) == 0)
                return (0);
            moveSnake(LEFT_DIR, 0, -1, newTail);
            break;
        case RIGHT_DIR:
            if (this->_map[this->_head.first][this->_head.second + 1] == 'X' || this->_map[this->_head.first][this->_head.second + 1] == 'P')
                return (1);
            if (eatFruit(RIGHT_DIR, 0, 1) == 0)
                return (0);
            moveSnake(RIGHT_DIR, 0, 1, newTail);
            break;
    }
    return (0);
}

void Nibbler::moveSnake(DIRECTION dir, int x, int y, std::pair<int, int> newTail)
{
    this->_map[this->_head.first + x][this->_head.second + y] = 'H';
    this->_head = std::make_pair(this->_head.first + x, this->_head.second + y);
    this->_tail = newTail;
    _allDir.pop_back();
    _allDir.push_front(dir);
}

int Nibbler::eatFruit(DIRECTION dir, int x, int y)
{
    if (this->_map[this->_head.first + x][this->_head.second + y] == 'O') {
        this->_map[this->_head.first + x][this->_head.second + y] = 'H';
        this->_map[this->_head.first][this->_head.second] = 'P';
        this->_head = std::make_pair(this->_head.first + x, this->_head.second + y);
        _allDir.push_front(dir);
        generateFruit();
        _score += 10;
        return (0);
    }
    return (1);
}

void Nibbler::generateFruit()
{
    int i = 0;
    int j = 0;

    while (_map[j][i] != ' ') {
        i = rand() % (30 - 2) + 2;
        j = rand() % (20 - 2) + 2;
        if (_map[j][i] == ' ') {
            _map[j][i] = 'O';
            return;
        }
    }
}

void Nibbler::makeAction(DIRECTION direction)
{
    if (this->_dir == DOWN_DIR && direction == UP_DIR)
        return;
    else if (this->_dir == UP_DIR && direction == DOWN_DIR)
        return;
    else if (this->_dir == LEFT_DIR && direction == RIGHT_DIR)
        return;
    else if (this->_dir == RIGHT_DIR && direction == LEFT_DIR)
        return;
    this->_dir = direction;
}

int Nibbler::getScore() const
{
    return (_score);
}

const std::map<char, Entity> &Nibbler::getMapEntity() const
{
    return (_mapEntity);
}