/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** core
*/
#ifndef CORE_HPP_
#define CORE_HPP_


#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <vector>
#include <algorithm>
#include "Errors.hpp"
#include <chrono>
#include <thread>
#include <dirent.h>


class Core {
    public:
        Core(const std::string &startLib);
        ~Core();


        //Event
        IDisplayModule *getLibInstance() const;
        void LoadLibs();
        void manageMenu();
        void manageGame();
        void managePause();
        void foundHighScore();
        void storeHighScore();
        void manageGameOver();
        void startGame();
        void playGame();

        //Event
        void nextLib();
        void prevLib();
        void nextGame();
        void prevGame();
        void prepareGame();
        void restartGame();

    protected:
    private:
        std::vector<std::string> _graphicPaths;
        std::vector<IDisplayModule *> _displayLibs;
        std::vector<std::string> _gamePaths;
        std::vector<IGameModule *> _displayGames;

        bool _isPlaying;
        bool _isGameOver;
        KEY _eventGame;
        KEY _eventGameOver;
        int _actualLib;
        int _gameSelected;
        std::string _playerName;
        std::ofstream _highScoreFile;
        std::pair<std::string, int> _scoreTab;
        clock_t _t1, _t2, _t3;
        double _elapsed, _elapsed2;
};

#endif /* !CORE_HPP_ */
