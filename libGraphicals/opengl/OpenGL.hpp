/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** opengl
*/

#ifndef NCURSES_LIB_HPP_
#define NCURSES_LIB_HPP_

#include "IDisplayModule.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Errors.hpp"
#include <GL/glu.h>
#include <iostream>
#include <cmath>

#define UNUSED(expr) do { (void)(expr); } while (0)

class opengl: public IDisplayModule {
    public:
        opengl();
        ~opengl();

        //Lib
        void initColor();
        void initLib();
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

        //Display
        void drawText(sf::Text text, std::string str, int size, int x, int y, sf::Color color, sf::Font font);
        void drawMenu();
        void drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity);
        void drawHighScore(int highScore);
        void drawSphere(double r, int lats, int longs);
        void drawScores(std::string player1, int score, std::string player2, int highScore);
        void drawCube(std::vector<float> x, std::vector<float> y, std::vector<float> z, std::vector<GLubyte> color);
        void gluPerspective(double fovy, double aspect, double zNear, double zFar);
        void drawGameOver(int score);

        //Utils
        const std::string &getPlayerName() const;

    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Text _menuTitle;
        sf::Text _snakeText;
        sf::Text _secondGame;
        sf::Font _classicFont;
        sf::Font _spaceRanger;
        sf::Font _jerseyLetters;
        sf::Font _conthrax;
        int _menuIndex;
        sf::Text _highScoreTitle;
        sf::Text _highScoreName;
        sf::Text _highScore;
        sf::Text _ScoreTitle;
        sf::Text _ScoreName;
        sf::Text _Score;
        std::string _playerName;
        sf::Text _qToQuit;
};

extern "C" IDisplayModule *loadLib()
{
    return new opengl();
}

#endif /* !NCURSES_LIB_HPP_ */
