/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** pacman
*/
#include "Pacman.hpp"
#include <iostream>

Pacman::Pacman()
{
    _mapEntity = {
        {'X', Entity(RECT, {1.f, 1.f}, {0, 0, 255}, 6)},
        {'_', Entity(RECT, {1.f, 0.5}, {255, 255, 255}, 13)},
        {'O', Entity(CIRCLE, {0.5, 0.5}, {255, 255, 255}, 13)},
        {'P', Entity(CIRCLE, {1.f, 1.f}, {255, 255, 0}, 15)},
        {'W', Entity(RECT, {1.f, 1.f}, {0, 0, 0}, 10)},
        {'F', Entity(CIRCLE, {0.5, 0.5}, {0, 255, 0}, 7)},
        {'*', Entity(CIRCLE, {0.2, 0.2}, {255, 255, 255}, 13)},
        {'1', Entity(CIRCLE, {1.f, 1.f}, {0, 255, 255}, 9)},
        {'2', Entity(CIRCLE, {1.f, 1.f}, {255, 0, 0}, 5)},
        {'3', Entity(CIRCLE, {1.f, 1.f}, {255, 0, 144}, 14)},
        {'4', Entity(CIRCLE, {1.f, 1.f}, {255, 127, 0}, 4)},
        {'5', Entity(CIRCLE, {1.f, 1.f}, {0, 0, 255}, 9)}
    };
}

Pacman::~Pacman()
{
}

void Pacman::initGame()
{
    this->_dir = RIGHT_DIR;
    this->_score = 0;
    this->_name = "Pacman";
    this->generateMap();
    srand (time(NULL));

    this->_pacmanPos = std::make_pair(14, 13);
    this->_tpPos = new std::pair<int, int>;
    this->_tpPos[0] = std::make_pair(12, 1);
    this->_tpPos[1] = std::make_pair(12, 25);

    this->_ghostPos['1'] = std::make_pair(11, 12);
    this->_ghostPos['2'] = std::make_pair(12, 12);
    this->_ghostPos['3'] = std::make_pair(11, 14);
    this->_ghostPos['4'] = std::make_pair(12, 14);

    this->_ghostIntel['1'] = 1;
    this->_ghostIntel['2'] = 2;
    this->_ghostIntel['3'] = 4;
    this->_ghostIntel['4'] = 6;

    for (int i = '1'; i != '5'; i++) {
        this->_ghostDir[i] = RIGHT_DIR;
        this->_ghostExit[i] = false;
        this->_ghostState[i] = Pacman::CHASE;
        time(&_t2[i]);
    }
    _fleeModeTime = 10;
    _timeToWait = 10;

    time(&_t1);
    time(&_tFruit);
    time(&_tFruit2);
    _combo = 1;
}

void Pacman::resetGame()
{
    this->_map.clear();
    this->_map2.clear();
}

void Pacman::generateMap()
{
    _map.push_back("WXXXXXXXXXXXXXXXXXXXXXXXXXW");
    _map.push_back("WXO**********X**********OXW");
    _map.push_back("WX*XXXX*XXXX*X*XXXX*XXXX*XW");
    _map.push_back("WX*XXXX*XXXX*X*XXXX*XXXX*XW");
    _map.push_back("WX***********************XW");
    _map.push_back("WX*XXXX*XX*XXXXX*XX*XXXX*XW");
    _map.push_back("WX*XXXX*XX*XXXXX*XX*XXXX*XW");
    _map.push_back("WX******XX***X***XX******XW");
    _map.push_back("WXXXXXX*XXXX*X*XXXX*XXXXXXW");
    _map.push_back("W     X*XX*******XX*X     W");
    _map.push_back("W     X*XX*XX_XX*XX*X     W");
    _map.push_back("WXXXXXX*XX*X1 3X*XX*XXXXXXW");
    _map.push_back("W      ****X2 4X****      W");
    _map.push_back("WXXXXXX*XX*XXXXX*XX*XXXXXXW");
    _map.push_back("W     X*XX***P***XX*X     W");
    _map.push_back("W     X*XX*XXXXX*XX*X     W");
    _map.push_back("WXXXXXX*XX*XXXXX*XX*XXXXXXW");
    _map.push_back("WX***********X***********XW");
    _map.push_back("WX*XXXX*XXXX*X*XXXX*XXXX*XW");
    _map.push_back("WXO**XX*************XX**OXW");
    _map.push_back("WXXX*XX*XX*XXXXX*XX*XX*XXXW");
    _map.push_back("WX******XX***X***XX******XW");
    _map.push_back("WX*XXXXXXXXX*X*XXXXXXXXX*XW");
    _map.push_back("WX***********************XW");
    _map.push_back("WXXXXXXXXXXXXXXXXXXXXXXXXXW");
    _map2 = _map;
    _map2[14][13] = ' ';
}

int Pacman::refreshGame()
{
    if (this->_map[this->_pacmanPos.first][this->_pacmanPos.second] != 'P' && this->_map[this->_pacmanPos.first][this->_pacmanPos.second] != '5')
        return (1);
    switch (_dir) {
        case UP_DIR:
            if (this->_map[this->_pacmanPos.first - 1][this->_pacmanPos.second] == 'X')
                break;
            eatPacgums(-1, 0);
            movePacman(-1, 0);
            break;
        case DOWN_DIR:
            if (this->_map[this->_pacmanPos.first + 1][this->_pacmanPos.second] == 'X')
                break;
            eatPacgums(1, 0);
            movePacman(1, 0);
            break;
        case LEFT_DIR:
            if (this->_pacmanPos.first == this->_tpPos[0].first && this->_pacmanPos.second == this->_tpPos[0].second) {
                movePacman(0, 24);
                break;
            }
            if (this->_map[this->_pacmanPos.first][this->_pacmanPos.second - 1] == 'X')
                break;
            eatPacgums(0, -1);
            movePacman(0, -1);
            break;
        case RIGHT_DIR:
            if (this->_pacmanPos.first == this->_tpPos[1].first && this->_pacmanPos.second == this->_tpPos[1].second) {
                movePacman(0, -24);
                break;
            }
            if (this->_map[this->_pacmanPos.first][this->_pacmanPos.second + 1] == 'X')
                break;
            eatPacgums(0, 1);
            movePacman(0, 1);
            break;
    }
    ghostMoves();
    generateFruit();
    return (0);
}

void Pacman::generateFruit()
{
    double diffFruit = 0;

    time(&_tFruit);
    if (_tFruit2 != 0)
        diffFruit = difftime(_tFruit, _tFruit2);
    if (diffFruit > 30) {
        _map[14][13] = 'F';
        _map2[14][13] = 'F';
        _tFruit = 0;
        _tFruit2 = 0;
    }


}

void Pacman::exitGhost(char ghost)
{
    _map[9][13] = _map[_ghostPos[ghost].first][_ghostPos[ghost].second];
    _map[_ghostPos[ghost].first][_ghostPos[ghost].second] = ' ';
    _ghostPos[ghost] = std::make_pair(9, 13);
}

int Pacman::checkWall(int x, int y) const
{
    int nbWall = 1;

    if (_map[x + 1][y] == 'X')
        nbWall++;
    if (_map[x - 1][y] == 'X')
        nbWall++;
    if (_map[x][y + 1] == 'X')
        nbWall++;
    if (_map[x][y - 1] == 'X')
        nbWall++;
    return (nbWall);
}

void Pacman::checkNotWall(int x, int y)
{
    if (_map[x + 1][y] != 'X')
        _choice.push_back(DOWN_DIR);
    if (_map[x - 1][y] != 'X')
        _choice.push_back(UP_DIR);
    if (_map[x][y + 1] != 'X')
        _choice.push_back(RIGHT_DIR);
    if (_map[x][y - 1] != 'X')
        _choice.push_back(LEFT_DIR);
}


int Pacman::setBrainyDirection(int x, int y, int dir)
{
    int xPacman = _pacmanPos.first;
    int yPacman = _pacmanPos.second;

    if (xPacman - x > 0) {
        if (_map[x + 1][y] != 'X' && _map[x + 1][y] != '_' && dir != UP_DIR)
            return (DOWN_DIR);
    }
    if (yPacman - y < 0) {
        if (_map[x][y - 1] != 'X' && _map[x][y - 1] != '_' && dir != RIGHT_DIR)
            return (LEFT_DIR);
    }
    if (xPacman - x < 0) {
        if (_map[x - 1][y] != 'X' && _map[x - 1][y] != '_' && dir != DOWN_DIR)
            return (UP_DIR);
    }
    if (yPacman - y > 0) {
        if (_map[x][y + 1] != 'X' && _map[x][y + 1] != '_' && dir != LEFT_DIR)
            return (RIGHT_DIR);
    }
    return(setRandomDirection(x, y));
}

int Pacman::fleePacman(int x, int y, int dir)
{
    int xPacman = _pacmanPos.first;
    int yPacman = _pacmanPos.second;

    if (xPacman - x > 0) {
        if (_map[x - 1][y] != 'X' && _map[x - 1][y] != '_' && dir != DOWN_DIR)
            return (UP_DIR);
    }
    if (yPacman - y < 0) {
        if (_map[x][y + 1] != 'X' && _map[x][y + 1] != '_' && dir != LEFT_DIR)
            return (RIGHT_DIR);
    }
    if (xPacman - x < 0) {
        if (_map[x + 1][y] != 'X' && _map[x + 1][y] != '_' && dir != UP_DIR)
            return (DOWN_DIR);
    }
    if (yPacman - y > 0) {
        if (_map[x][y - 1] != 'X' && _map[x][y - 1] != '_' && dir != RIGHT_DIR)
            return (LEFT_DIR);
    }
    return(setRandomDirection(x, y));
}

int Pacman::setRandomDirection(int x, int y)
{
    int i = 0;

    _choice.clear();
    checkNotWall(x, y);

    i = rand() % _choice.size();
    return (_choice[i]);
}


int Pacman::setDirectionGhost(int x, int y, int dir, int ghost)
{
    int i = rand() % 10;

    if (this->_ghostState[ghost] == Pacman::CHASE && (i <= _ghostIntel[ghost]))
        return (setBrainyDirection(x, y, dir));
    else if (this->_ghostState[ghost] == Pacman::FLEE)
        return (fleePacman(x, y, dir));
    return (setRandomDirection(x, y));
}

int Pacman::checkFrontGhost(int ghost)
{
    if (_ghostDir[ghost] == UP_DIR && _map[_ghostPos[ghost].first - 1][_ghostPos[ghost].second] != 'X')
        return (1);
    if (_ghostDir[ghost] == DOWN_DIR && _map[_ghostPos[ghost].first + 1][_ghostPos[ghost].second] != 'X')
        return (1);
    if (_ghostDir[ghost] == RIGHT_DIR && _map[_ghostPos[ghost].first][_ghostPos[ghost].second + 1] != 'X')
        return (1);
    if (_ghostDir[ghost] == LEFT_DIR && _map[_ghostPos[ghost].first][_ghostPos[ghost].second - 1] != 'X')
        return (1);
    return (0);
}

void Pacman::ghostMoves()
{
    double diffExit = 0;
    double diffFlee = 0;
    double diffSlow = 0;

    time(&_t4);
    diffFlee = difftime(_t4, _t3);
    for (int i = '1'; i != '5'; i++) {
        if (_ghostState[i] == Pacman::FLEE) {
            if (diffFlee > _fleeModeTime) {
                _ghostState[i] = Pacman::CHASE;
                this->_map[this->_ghostPos[i].first][this->_ghostPos[i].second] = i;
                time(&_t3);
                _combo = 1;
                continue;
            }
            eatGhosts(i);
            _t6[i] = clock();
            diffSlow = (_t6[i] - _t5[i]) / 1000;
            if (diffSlow < 50)
                continue;
            else
                _t5[i] = clock();
        }
        if (_ghostExit[i] == false) {
            time(&_t2[i]);
            diffExit = difftime(_t2[i], _t1);
            if (diffExit > _timeToWait) {
                exitGhost(i);
                time(&_t1);
                _timeToWait = 4;
                _ghostExit[i] = true;
                break;
            }
            continue;
        }
        if (checkWall(_ghostPos[i].first, _ghostPos[i].second) <= 2 || checkFrontGhost(i) == 0)
            _ghostDir[i] = setDirectionGhost(_ghostPos[i].first, _ghostPos[i].second, _ghostDir[i], i);
        switch (_ghostDir[i]) {
            case UP_DIR:
                if (_map[_ghostPos[i].first - 1][_ghostPos[i].second] == 'X' || _map[_ghostPos[i].first - 1][_ghostPos[i].second] == '_') {
                    _ghostDir[i] = setDirectionGhost(_ghostPos[i].first, _ghostPos[i].second, _ghostDir[i], i);
                    continue;
                }
                moveGhost(-1, 0, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                break;
            case DOWN_DIR:
                if (_map[_ghostPos[i].first + 1][_ghostPos[i].second] == 'X' || _map[_ghostPos[i].first + 1][_ghostPos[i].second] == '_') {
                    _ghostDir[i] = setDirectionGhost(_ghostPos[i].first, _ghostPos[i].second, _ghostDir[i], i);
                    continue;
                }
                moveGhost(1, 0, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                break;
            case RIGHT_DIR:
                if (this->_ghostPos[i].first == this->_tpPos[1].first && this->_ghostPos[i].second == this->_tpPos[1].second) {
                    moveGhost(0, -24, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                    continue;
                }
                if (_map[_ghostPos[i].first][_ghostPos[i].second + 1] == 'X' || _map[_ghostPos[i].first][_ghostPos[i].second + 1] == '_') {
                    _ghostDir[i] = setDirectionGhost(_ghostPos[i].first, _ghostPos[i].second, _ghostDir[i], i);
                    continue;
                }
                moveGhost(0, 1, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                break;
            case LEFT_DIR:
                if (this->_ghostPos[i].first == this->_tpPos[0].first && this->_ghostPos[i].second == this->_tpPos[0].second) {
                    moveGhost(0, 24, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                    continue;
                }
                if (_map[_ghostPos[i].first][_ghostPos[i].second - 1] == 'X' || _map[_ghostPos[i].first][_ghostPos[i].second - 1] == '_') {
                    _ghostDir[i] = setDirectionGhost(_ghostPos[i].first, _ghostPos[i].second, _ghostDir[i], i);
                    continue;
                }
                moveGhost(0, -1, i, _map[_ghostPos[i].first][_ghostPos[i].second]);
                break;
        }
    }
}

void Pacman::movePacman(int x, int y)
{
    this->_map[this->_pacmanPos.first + x][this->_pacmanPos.second + y] = 'P';
    this->_map[this->_pacmanPos.first][this->_pacmanPos.second] = ' ';
    this->_pacmanPos = std::make_pair(this->_pacmanPos.first + x, this->_pacmanPos.second + y);
}

void Pacman::moveGhost(int x, int y, char ghost, char color)
{
    this->_map[this->_ghostPos[ghost].first + x][this->_ghostPos[ghost].second + y] = color;
    this->_map[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second] = this->_map2[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second];
    this->_ghostPos[ghost] = std::make_pair(this->_ghostPos[ghost].first + x, this->_ghostPos[ghost].second + y);
    if (this->_ghostState[ghost] == Pacman::FLEE && this->_map[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second] != '5')
        this->_map[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second] = '5';
    if (this->_map[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second] != ghost && this->_ghostState[ghost] == Pacman::CHASE && ghost != 'P')
        this->_map[this->_ghostPos[ghost].first][this->_ghostPos[ghost].second] = ghost;
}

void Pacman::eatBigPacgum()
{
    this->_ghostState['1'] = Pacman::FLEE;
    this->_ghostState['2'] = Pacman::FLEE;
    this->_ghostState['3'] = Pacman::FLEE;
    this->_ghostState['4'] = Pacman::FLEE;
    this->_map[_ghostPos['1'].first][_ghostPos['1'].second] = '5';
    this->_map[_ghostPos['2'].first][_ghostPos['2'].second] = '5';
    this->_map[_ghostPos['3'].first][_ghostPos['3'].second] = '5';
    this->_map[_ghostPos['4'].first][_ghostPos['4'].second] = '5';
    time(&_t3);
    time(&_t4);
    for (int i = '1'; i != '5'; i++) {
        _t5[i] = clock();
        _t6[i] = clock();
    }
}

void Pacman::eatPacgums(int x, int y)
{
    if (this->_map[this->_pacmanPos.first + x][this->_pacmanPos.second + y] == 'O') {
        _score += 50;
        eatBigPacgum();
    }
    else if (this->_map[this->_pacmanPos.first + x][this->_pacmanPos.second + y] == '*')
        _score += 10;
    else if (this->_map[this->_pacmanPos.first + x][this->_pacmanPos.second + y] == 'F')
        _score += 100;
    this->_map2[this->_pacmanPos.first + x][this->_pacmanPos.second + y] = ' ';
}

void Pacman::eatGhosts(char ghost)
{
    if (this->_map[_ghostPos[ghost].first][_ghostPos[ghost].second] == 'P' || (_ghostPos[ghost].first == _pacmanPos.first && _ghostPos[ghost].second == _pacmanPos.second)) {
        this->_map[_pacmanPos.first][_pacmanPos.second] = 'P';
        switch (ghost) {
            case '1':
                this->_ghostPos['1'] = std::make_pair(11, 12);
                this->_map[_ghostPos['1'].first][_ghostPos['1'].second] = ghost;
                this->_ghostState['1'] = Pacman::CHASE;
                this->_ghostExit['1'] = false;
                break;
            case '2':
                this->_ghostPos['2'] = std::make_pair(12, 12);
                this->_map[_ghostPos['2'].first][_ghostPos['2'].second] = ghost;
                this->_ghostState['2'] = Pacman::CHASE;
                this->_ghostExit['2'] = false;
                break;
            case '3':
                this->_ghostPos['3'] = std::make_pair(11, 14);
                this->_map[_ghostPos['3'].first][_ghostPos['3'].second] = ghost;
                this->_ghostState['3'] = Pacman::CHASE;
                this->_ghostExit['3'] = false;
                break;
            case '4':
                this->_ghostPos['4'] = std::make_pair(12, 14);
                this->_map[_ghostPos['4'].first][_ghostPos['4'].second] = ghost;
                this->_ghostState['4'] = Pacman::CHASE;
                this->_ghostExit['4'] = false;
                break;
        }
        time(&_t1);
        time(&_t2[ghost]);
        _score += (200 * _combo);
        _combo *= 2;
    }
}

void Pacman::makeAction(DIRECTION direction)
{
    if (direction == UP_DIR && this->_map[this->_pacmanPos.first - 1][this->_pacmanPos.second] == 'X')
        return;
    else if (direction == DOWN_DIR && this->_map[this->_pacmanPos.first + 1][this->_pacmanPos.second] == 'X')
        return;
    else if (direction == RIGHT_DIR && this->_pacmanPos.second + 1 <= 24 && this->_map[this->_pacmanPos.first][this->_pacmanPos.second + 1] == 'X')
        return;
    else if (direction == LEFT_DIR && this->_pacmanPos.second - 1 >= 0 && this->_map[this->_pacmanPos.first][this->_pacmanPos.second - 1] == 'X')
        return;
    this->_dir = direction;
}

int Pacman::getScore() const
{
    return (this->_score);
}

const std::vector<std::string> &Pacman::getMap() const
{
    return (this->_map);
}

const std::string& Pacman::getName() const
{
    return (this->_name);
}

const std::map<char, Entity> &Pacman::getMapEntity() const
{
    return (this->_mapEntity);
}