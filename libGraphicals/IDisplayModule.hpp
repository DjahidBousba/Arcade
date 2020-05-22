/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "Entity.hpp"
#include <string.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

enum KEY {
    NONE,
    END,
    SNAKE,
    PACMAN,
    PREV_LIB,
    NEXT_LIB,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    PAUSE,
    RESTART,
    NEXT_GAME,
    PREV_GAME,
    MENU
};

class IDisplayModule {
    public:
        virtual ~IDisplayModule() {};

        //DISPLAY
        virtual void openWindow() = 0;
        virtual void closeWindow() = 0;
        virtual bool isOpen() const = 0;
        virtual void clearWindow() = 0;

        //EVENT
        virtual KEY manageEventsMenu() = 0;
        virtual KEY manageEventsGame() = 0;
        virtual KEY manageGameOver() = 0;

        //MENU
        virtual void drawMenu() = 0;

        //GAME
        virtual void drawMap(std::vector<std::string> map, std::map<char, Entity> _mapEntity) = 0;

        //HIGHSCORE
        virtual void drawScores(std::string player1, int score, std::string player2, int highScore) = 0;
        virtual void drawGameOver(int score) = 0;

        virtual const std::string &getPlayerName() const = 0;

    protected:
    private:
};

#endif /* !IDISPLAYMODULE_HPP_ */
