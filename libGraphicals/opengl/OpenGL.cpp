/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** opengl.cpp
*/

#include "OpenGL.hpp"

opengl::opengl()
{
    this->initLib();
}

opengl::~opengl()
{
}

void opengl::initLib()
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

void opengl::openWindow()
{
    this->_window.create(sf::VideoMode(1920, 1080), "ArcadeOpenGL");
}

void opengl::closeWindow()
{
    if (this->isOpen())
        this->_window.close();
}

bool opengl::isOpen() const
{
    return (this->_window.isOpen());
}

void opengl::clearWindow()
{
    if (this->isOpen())
        this->_window.clear(sf::Color::Black);
}

KEY opengl::manageEventsMenu()
{
    while (this->_window.pollEvent(_event))
    {
        if (this->_event.type == sf::Event::Closed) {
            this->closeWindow();
            return (END);
        } else if (_menuIndex == 2 && ((this->_event.type == sf::Event::TextEntered && (this->_event.text.unicode == 127 || (this->_event.text.unicode >= 48 && this->_event.text.unicode <= 57) || (this->_event.text.unicode >= 65 && this->_event.text.unicode <= 90) || (this->_event.text.unicode >= 97 && this->_event.text.unicode <= 122))) || (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Backspace))) {
            if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Backspace && !(this->_playerName.empty())) {
                this->_playerName.pop_back();
            } else {
                this->_playerName += (char)_event.text.unicode;
            }
        } else if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape) {
                this->closeWindow();
                return (END);
            }
            else if (this->_event.key.code == sf::Keyboard::Left) {
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
                else
                    return (PACMAN);
            }
        }
    }
    return (NONE);
}

KEY opengl::manageEventsGame()
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

KEY opengl::manageGameOver()
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

void opengl::drawText(sf::Text text, std::string str, int size, int x, int y, sf::Color color, sf::Font font)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    text.setFillColor(color);
    this->_window.draw(text);
}


void opengl::drawMenu()
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

void opengl::drawCube(std::vector<float> x, std::vector<float> y, std::vector<float> z, std::vector<GLubyte> color) {
    glBegin(GL_QUADS);

    glColor4ub(color[0],color[1],color[2], 150);
    glVertex3f(x[0], y[0], z[0]);
    glVertex3f(x[0], y[1], z[0]);
    glVertex3f(x[1], y[1], z[0]);
    glVertex3f(x[1], y[0], z[0]);

    glColor4ub(color[0] / 1.18,color[1] / 1.18,color[2] / 1.18, 150);
    glVertex3f(x[0], y[0], z[1]);
    glVertex3f(x[0], y[1], z[1]);
    glVertex3f(x[1], y[1], z[1]);
    glVertex3f(x[1], y[0], z[1]);

    glColor4ub(color[0] / 1.54,color[1] / 1.54,color[2] / 1.54, 150);
    glVertex3f(x[0], y[0], z[0]);
    glVertex3f(x[0], y[1], z[0]);
    glVertex3f(x[0], y[1], z[1]);
    glVertex3f(x[0], y[0], z[1]);

    glColor4ub(color[0] / 2.04,color[1] / 2.04,color[2] / 2.04, 150);
    glVertex3f(x[1], y[0], z[0]);
    glVertex3f(x[1], y[1], z[0]);
    glVertex3f(x[1], y[1], z[1]);
    glVertex3f(x[1], y[0], z[1]);

    glColor4ub(color[0] / 3,color[1] / 3,color[2] / 3, 150);
    glVertex3f(x[0], y[0], z[1]);
    glVertex3f(x[0], y[0], z[0]);
    glVertex3f(x[1], y[0], z[0]);
    glVertex3f(x[1], y[0], z[1]);

    glColor4ub(color[0] / 7.28,color[1] / 7.28,color[2] / 7.28, 150);
    glVertex3f(x[0], y[1], z[1]);
    glVertex3f(x[0], y[1], z[0]);
    glVertex3f(x[1], y[1], z[0]);
    glVertex3f(x[1], y[1], z[1]);

    glEnd();
}

void opengl::gluPerspective(double fovy, double aspect, double zNear, double zFar) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double xmin, xmax, ymin, ymax;
    ymax = zNear * tan(fovy * 3.14 / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void opengl::drawSphere(double r, int lats, int longs) {
    int i, j = 0;

    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            //glColor4ub(color[0] / 7.28,color[1] / 7.28,color[2] / 7.28, 150);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}

void opengl::drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    this->gluPerspective(100.f, 1.f, 1.f, 400.0f);

    gluLookAt(160.5, 59.f, -575.f, 144.5, 481.f, 600.5, 0, 10, 0);

    float size = 5.f;
    std::vector<GLubyte> color;
    std::vector<float> x = {size, -size};
    std::vector<float> pos = {size, -size};
    std::vector<float> y = {2, -2};

    int sizey = map.size();
    int sizex;
    for (size_t i = 0; i < map.size(); i++) {
        sizex = map[0].size();
        for (size_t j = 0; j < map.at(i).size(); j++) {
            color.clear();
            if (map[i][j] != ' ') {
                size = 5.f * mapEntity.at(map[i][j]).getSize()[0];
                x = {size, -size};
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                glTranslatef(sizex * pos[0] * 2, (sizey * pos[0] * 2), -400.f);
                color.push_back((float)mapEntity.at(map[i][j]).getColor()[0]);
                color.push_back((float)mapEntity.at(map[i][j]).getColor()[1]);
                color.push_back((float)mapEntity.at(map[i][j]).getColor()[2]);
                this->drawCube(x, x, x, color);
            }
            --sizex;
        }
        --sizey;
    }
    _window.display();
}

void opengl::drawScores(std::string player1, int score, std::string player2, int highScore)
{
    UNUSED(player1);
    UNUSED(score);
    UNUSED(player2);
    UNUSED(highScore);
}

const std::string &opengl::getPlayerName() const
{
        return (_playerName);
}

void opengl::drawGameOver(int score)
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