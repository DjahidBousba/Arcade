/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGameModule.hpp"

class Nibbler: public IGameModule {
    public:
        Nibbler();
        ~Nibbler();

        //Map
        void initGame();
        void resetGame();
        void generateMap();
        void createRandomWalls();
        void generateFruit();
        const std::vector<std::string> &getMap() const;
        int refreshGame();
        int checkFreeCell() const;

        //Snake
        void generateSnake();
        void moveSnake(DIRECTION dir, int x, int y, std::pair<int, int> newTail);
        std::pair<int, int> findNewTail() const;
        void makeAction(DIRECTION direction);
        int getScore() const;
        const std::string &getName() const;
        int eatFruit(DIRECTION dir, int x, int y);
        const std::map<char, Entity> &getMapEntity() const;

    protected:
    private:
        std::vector<std::string> _map;
        std::string _name = "nibbler";
        int _snakeSize;
        int _dir;
        int _score;
        std::pair<int, int> _head;
        std::pair<int, int> _tail;
        std::list<int> _allDir;
        std::map<char, Entity> _mapEntity;

};

extern "C" IGameModule *loadGames()
{
    return new Nibbler();
}

#endif /* !NIBBLER_HPP_ */
