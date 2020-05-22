/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <vector>
#include <string>
#include <map>
#include <list>
#include "Entity.hpp"

enum DIRECTION {
    UP_DIR,
    DOWN_DIR,
    RIGHT_DIR,
    LEFT_DIR
};

class IGameModule {
    public:
        virtual ~IGameModule() {};

        virtual const std::vector<std::string> &getMap() const = 0;
        virtual int refreshGame() = 0;
        virtual void makeAction(DIRECTION direction) = 0;
        virtual int getScore() const = 0;
        virtual const std::string &getName() const = 0;
        virtual const std::map<char, Entity> &getMapEntity() const = 0;
        virtual void initGame() = 0;
        virtual void resetGame() = 0;

    protected:
    private:
};

#endif /* !IGAMEMODULE_HPP_ */
