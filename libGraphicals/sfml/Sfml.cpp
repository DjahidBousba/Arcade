/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** sfmlLib.cpp
*/

#include "Sfml.hpp"

sfmlLib::sfmlLib()
{
    this->initLib();
    this->_window.create(sf::VideoMode(1920, 1080), "Arcade SFML");
    _window.setActive(false);
    _window.setVisible(false);
}

sfmlLib::~sfmlLib()
{
}

void sfmlLib::initLib()
{
    if (!(this->_classicFont.loadFromFile("./libGraphicals/utils/arial.ttf")))
        throw ParsingError("Error while loading font from file.");
    if (!(this->_spaceRanger.loadFromFile("./libGraphicals/utils/spaceranger.ttf")))
        throw ParsingError("Error while loading font from file.");
    if (!(this->_jerseyLetters.loadFromFile("./libGraphicals/utils/JerseyLetters.ttf")))
        throw ParsingError("Error while loading font from file.");
    if (!(this->_conthrax.loadFromFile("./libGraphicals/utils/conthrax-sb.ttf")))
        throw ParsingError("Error while loading font from file.");
    _menuIndex = 0;
}

void sfmlLib::openWindow()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Arcade SFML");
}

bool sfmlLib::isOpen() const
{
    return (this->_window.isOpen());
}

void sfmlLib::closeWindow()
{
    if (this->_window.isOpen())
        _window.close();
}

void sfmlLib::clearWindow()
{
    if (this->isOpen())
        this->_window.clear(sf::Color::Black);
}

KEY sfmlLib::manageEventsMenu()
{
    while (this->_window.pollEvent(_event))
    {
        if (this->_event.type == sf::Event::Closed) {
            this->closeWindow();
            return (END);
        } else if (_menuIndex == 2 && ((this->_event.type == sf::Event::TextEntered && (this->_event.text.unicode == 127 || (this->_event.text.unicode >= 48 && this->_event.text.unicode <= 57) || (this->_event.text.unicode >= 65 && this->_event.text.unicode <= 90) || (this->_event.text.unicode >= 97 && this->_event.text.unicode <= 122))) || (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Backspace))) {
            if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Backspace && !(this->_playerName.empty())) {
                this->_playerName.pop_back();
            } else if (this->_playerName.size() < 10) {
                this->_playerName += (char)_event.text.unicode;
            }
        } else if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape) {
                this->closeWindow();
                return (END);
            } else if (this->_event.key.code == sf::Keyboard::Left) {
                return (PREV_LIB);
            }
            else if (this->_event.key.code == sf::Keyboard::Right) {
                return (NEXT_LIB);
            } else if (this->_event.key.code == sf::Keyboard::Up) {
                _menuIndex--;
                if (_menuIndex == -1)
                    _menuIndex = 2;
                return (NONE);
            } else if (this->_event.key.code == sf::Keyboard::Down) {
                _menuIndex++;
                if (_menuIndex == 3)
                    _menuIndex = 0;
                return (NONE);
            } else if (this->_event.key.code == sf::Keyboard::Enter) {
                if (_menuIndex == 0)
                    return (SNAKE);
                else if (_menuIndex == 1)
                    return (PACMAN);
            }
        }
    }
    return (NONE);
}

KEY sfmlLib::manageEventsGame()
{
    while (this->_window.pollEvent(_event))
    {
        if (this->_event.type == sf::Event::Closed) {
            this->closeWindow();
            return (END);
        } else if (this->_event.type == sf::Event::KeyPressed) {
            switch (this->_event.key.code) {
                case sf::Keyboard::Escape:
                    this->closeWindow();
                    return (END);
                case sf::Keyboard::Left:
                    return (PREV_LIB);
                case sf::Keyboard::Right:
                    return (NEXT_LIB);
                case sf::Keyboard::Up:
                    return (NEXT_GAME);
                case sf::Keyboard::Down:
                    return (PREV_GAME);
                case sf::Keyboard::R:
                    return (RESTART);
                case sf::Keyboard::O:
                    return (MENU);
                case sf::Keyboard::P:
                    return (PAUSE);
                case sf::Keyboard::Z:
                    return (UP);
                case sf::Keyboard::S:
                    return (DOWN);
                case sf::Keyboard::D:
                    return (RIGHT);
                case sf::Keyboard::Q:
                    return (LEFT);
                default:
                    break;
            }
        }
    }
    return (NONE);
}

KEY sfmlLib::manageGameOver()
{
    while (this->_window.pollEvent(_event)) {
        if (this->_event.type == sf::Event::Closed) {
            this->closeWindow();
            return (END);
        }
        if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::R) {
                return (RESTART);
            } else if (this->_event.key.code == sf::Keyboard::Escape) {
                this->closeWindow();
                return (END);
            } else if (this->_event.key.code == sf::Keyboard::Left) {
                return (PREV_LIB);
            }
            else if (this->_event.key.code == sf::Keyboard::Right) {
                return (NEXT_LIB);
            }
        }
    }
    return (NONE);
}

void sfmlLib::drawText(sf::Text text, std::string str, int size, int x, int y, sf::Color color, sf::Font font)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    text.setFillColor(color);
    this->_window.draw(text);
}

void sfmlLib::drawMenu()
{
    std::string playerName = "PlayerName";

    if (!(_playerName.empty()))
        playerName = _playerName;
    this->clearWindow();
    this->drawText(this->_menuTitle, "Arcade", 150, (1920 / 2) - ((6 / 2) * 110), (1080 / 2) - 500, sf::Color::White, this->_spaceRanger);
    if (_menuIndex == 0) {
        this->drawText(this->_snakeText, "Snake", 30, (1920 / 2) - ((5 / 2) * 20), ((1080 / 2) - 50), sf::Color::Red, this->_conthrax);
        this->drawText(this->_secondGame, "Pacman", 30, (1920 / 2) - ((6 / 2) * 17), (1080 / 2) + 50, sf::Color::White, this->_conthrax);
        this->drawText(this->_secondGame, playerName, 30, (1920 / 2) - ((playerName.size() / 2) * 15), (1080 / 2) + 150, sf::Color::White, this->_conthrax);
    } else if (_menuIndex == 1) {
        this->drawText(this->_snakeText, "Snake", 30, (1920 / 2) - ((5 / 2) * 20), ((1080 / 2) - 50), sf::Color::White, this->_conthrax);
        this->drawText(this->_secondGame, "Pacman", 30, (1920 / 2) - ((6 / 2) * 17), (1080 / 2) + 50, sf::Color::Red, this->_conthrax);
        this->drawText(this->_secondGame, playerName, 30, (1920 / 2) - ((playerName.size() / 2) * 15), (1080 / 2) + 150, sf::Color::White, this->_conthrax);
    } else {
        this->drawText(this->_snakeText, "Snake", 30, (1920 / 2) - ((5 / 2) * 20), ((1080 / 2) - 50), sf::Color::White, this->_conthrax);
        this->drawText(this->_secondGame, "Pacman", 30, (1920 / 2) - ((6 / 2) * 17), (1080 / 2) + 50, sf::Color::White, this->_conthrax);
        this->drawText(this->_secondGame, playerName, 30, (1920 / 2) - ((playerName.size() / 2) * 15), (1080 / 2) + 150, sf::Color::Red, this->_conthrax);
    }
    _window.display();
}

void sfmlLib::drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map.at(i).size(); j++) {
            if (map[i][j] != ' ') {
                if (mapEntity.at(map[i][j]).getShape() == RECT)
                    drawRect(mapEntity.at(map[i][j]), i, j);
                else if (mapEntity.at(map[i][j]).getShape() == CIRCLE)
                    drawCircle(mapEntity.at(map[i][j]), i, j);
            }
        }
    }
    _window.display();
}

void sfmlLib::drawRect(Entity mapEntity, int x, int y)
{
    int center = (mapEntity.getSize()[1]) == 0.5 ? 10 : 0;

    sf::RectangleShape rectangle(sf::Vector2f(mapEntity.getSize()[0] * 35, mapEntity.getSize()[1] * 35));
    rectangle.setPosition((float)(y * 35), (float)(x * 35) + center);
    rectangle.setFillColor(sf::Color(mapEntity.getColor()[0], mapEntity.getColor()[1], mapEntity.getColor()[2], 255));
    rectangle.setOutlineThickness(0.f);
    rectangle.setOutlineColor(sf::Color(mapEntity.getColor()[0], mapEntity.getColor()[1], mapEntity.getColor()[2]));
    this->_window.draw(rectangle);
}

void sfmlLib::drawCircle(Entity mapEntity, int x, int y)
{
    int center = ((35 / 2) - mapEntity.getSize()[0] * 15);

    sf::CircleShape circle(mapEntity.getSize()[0] * 15, 50);
    circle.setPosition((float)(y * 35) + center, (float)(x * 35) + center);
    circle.setFillColor(sf::Color(mapEntity.getColor()[0], mapEntity.getColor()[1], mapEntity.getColor()[2], 255));
    circle.setOutlineThickness(0.f);
    circle.setOutlineColor(sf::Color(mapEntity.getColor()[0], mapEntity.getColor()[1], mapEntity.getColor()[2]));
    this->_window.draw(circle);
}

void sfmlLib::drawScores(std::string player1, int score, std::string player2, int highScore)
{
    std::string str = std::to_string(score);
    std::string str2 = std::to_string(highScore);

    this->clearWindow();
    this->drawText(this->_highScoreTitle, "HighScore", 50, 1230, 100, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_highScoreName, player2, 30, 1140, 250, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_highScoreName, "-->", 30, 1455, 250, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_highScore, str2, 30, 1500, 250, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_ScoreTitle, "Score", 50, 1280, 400, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_ScoreName, player1, 30, 1140, 550, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_ScoreName, "-->", 30, 1455, 550, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_Score, str, 30, 1500, 550, sf::Color::White, this->_spaceRanger);
}

const std::string &sfmlLib::getPlayerName() const
{
    return (_playerName);
}

void sfmlLib::drawGameOver(int score)
{
    std::string str = std::to_string(score);

    this->clearWindow();
    this->drawText(this->_menuTitle, "Game Over", 150, (1920 / 2) - ((9 / 2) * 110), (1080 / 2) - 500, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_ScoreTitle, "Score", 50, (1920 / 2) - ((5 / 2) * 35), (1080 / 2) - 200, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_Score, str, 50, (1920 / 2) - ((str.size() / 2) * 17), (1080 / 2) - 100 , sf::Color::White, this->_spaceRanger);
    this->drawText(this->_qToQuit, "Press R to restart", 50, (1920 / 2) - ((18 / 2) * 30), (1080 / 2) + 50, sf::Color::White, this->_spaceRanger);
    this->drawText(this->_qToQuit, "Press Esc to quit", 50, (1920 / 2) - ((17 / 2) * 30), (1080 / 2) + 200, sf::Color::White, this->_spaceRanger);
    _window.display();
}