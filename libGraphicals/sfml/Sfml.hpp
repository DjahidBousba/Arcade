/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** sfmlLib
*/

#ifndef SFML_LIB_HPP_
#define SFML_LIB_HPP_

#include "IDisplayModule.hpp"
#include "Errors.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <chrono>
#include <thread>

class sfmlLib: public IDisplayModule {
    public:
        sfmlLib();
        ~sfmlLib();

        //Lib
        void initLib();
        void exit();
        void entry();

        //Window
        void openWindow();
        bool isOpen() const;
        void closeWindow();
        void clearWindow();

        //Events
        KEY manageEventsMenu();
        KEY manageEventsGame();
        KEY manageGameOver();

        //Display
        void drawGameOver(int score);
        void drawMenu();
        void drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity);
        void drawRect(Entity mapEntity, int x, int y);
        void drawCircle(Entity mapEntity, int x, int y);
        void drawScores(std::string player1, int score, std::string player2, int highScore);

        //UTILS
        void drawText(sf::Text text, std::string str, int size, int x, int y, sf::Color color, sf::Font font);
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
        sf::Text _gameOver;
        sf::Text _qToQuit;
        std::string _playerName;
};

extern "C" IDisplayModule *loadLib()
{
    return new sfmlLib();
}

#endif /* !SFML_LIB_HPP_ */
