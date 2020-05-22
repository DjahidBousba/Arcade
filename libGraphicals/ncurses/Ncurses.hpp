/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** ncursesLib
*/

#ifndef NCURSES_LIB_HPP_
#define NCURSES_LIB_HPP_

#include "IDisplayModule.hpp"
#include <ncurses.h>
#include <curses.h>
#include <vector>
#include <string>

class ncursesLib: public IDisplayModule {
    public:
        ncursesLib();
        ~ncursesLib();

        //Lib
        void initColor();
        void exitLib();
        void loadingLib();

        //Window
        void openWindow();
        void closeWindow();
        bool isOpen() const;
        void clearWindow();

        //Event
        int manageKey();
        KEY manageEventsMenu();
        KEY manageEventsGame();
        KEY manageGameOver();
        int menu();

        //Display
        void drawMenu();
        void highlight() const;
        void dispTitle();
        void drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity);
        void drawScores(std::string player1, int score, std::string player2, int highScore);
        void drawGameOver(int score);

        //Utils
        const std::string &getPlayerName() const;

    protected:
    private:
        std::vector<std::string> _games;
        int _menuIndex;
        bool _isOpen;
        std::string _playerName;
        int _ymax;
        int _xmax;
};

extern "C" IDisplayModule *loadLib()
{
    return new ncursesLib();
}

#endif /* !NCURSES_LIB_HPP_ */
