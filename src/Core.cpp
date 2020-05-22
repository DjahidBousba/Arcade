/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** core
*/

#include "Core.hpp"

Core::Core(const std::string &startLib)
{
    DIR *dir = opendir("lib");
    struct dirent *entry = NULL;
    std::string folder = "lib/";
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0)
            continue;
        if (strcmp(entry->d_name, ".gitkeep") == 0)
            continue;
        if (strcmp(entry->d_name, "..") == 0)
            continue;
        std::string path = folder + entry->d_name;
        _graphicPaths.push_back(path);
    }
    dir = opendir("games");
    entry = NULL;
    folder = "games/";
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0)
            continue;
        if (strcmp(entry->d_name, ".gitkeep") == 0)
            continue;
        if (strcmp(entry->d_name, "..") == 0)
            continue;
        std::string path = folder + entry->d_name;
        _gamePaths.push_back(path);
    }
    _gameSelected = 0;
    std::vector<std::string>::iterator it = std::find(_graphicPaths.begin(), _graphicPaths.end(), startLib);
    if (it != _graphicPaths.end())
        _actualLib = std::distance(_graphicPaths.begin(), it);
    else
        throw LibraryError("Library doesn't exist.");
}

Core::~Core()
{
}

IDisplayModule *Core::getLibInstance() const
{
    return (_displayLibs.at(_actualLib));
}

void Core::LoadLibs()
{
    std::vector<DLLoader<IDisplayModule> *> graphicLoader;
    std::vector<DLLoader<IGameModule> *> gameLoader;

    for (size_t i = 0; i < _graphicPaths.size(); ++i)
        graphicLoader.push_back(new DLLoader<IDisplayModule>(_graphicPaths[i]));
    for (size_t i = 0; i < _gamePaths.size(); ++i)
        gameLoader.push_back(new DLLoader<IGameModule>(_gamePaths[i]));
    for (size_t i = 0; i < graphicLoader.size(); ++i) {
        _displayLibs.push_back(graphicLoader[i]->getInstance("loadLib"));
        if (!_displayLibs[i])
            throw LibraryError("Loading of lib failed : " + _graphicPaths.at(i));
    }
    for (size_t i = 0; i < gameLoader.size(); ++i) {
        _displayGames.push_back(gameLoader[i]->getInstance("loadGames"));
        if (!_displayGames[i])
            throw GameError("Loading of games failed : " + _gamePaths.at(i));
    }
    startGame();
    _displayLibs.at(_actualLib)->closeWindow();
    for (size_t i = 0; i < gameLoader.size(); ++i)
        gameLoader[i]->closeLib();
    for (size_t i = 0; i < graphicLoader.size(); ++i)
        graphicLoader[i]->closeLib();
}

void Core::startGame()
{
    this->manageMenu();
    this->_playerName = _displayLibs.at(_actualLib)->getPlayerName();
    if (_playerName.empty())
        _playerName = "Player";
    this->foundHighScore();
    if (_displayLibs.at(_actualLib)->isOpen())
        this->playGame();
}

void Core::manageMenu()
{
    KEY event = NONE;

    _displayLibs.at(_actualLib)->openWindow();
    while ((event = _displayLibs.at(_actualLib)->manageEventsMenu()) != END) {
        switch (event) {
            case SNAKE:
                _gameSelected = 1;
                return;
            case PACMAN:
                _gameSelected = 0;
                return;
            case NEXT_LIB:
                this->nextLib();
                break;
            case PREV_LIB:
                this->prevLib();
                break;
            default:
                break;
        }
        _displayLibs.at(_actualLib)->drawMenu();
    }
    _displayLibs.at(_actualLib)->closeWindow();
}

void Core::playGame()
{
    _t1 = clock();
    _t2 = clock();
    _t3 = clock();
    _elapsed = 0;
    _elapsed2 = 0;
    _isPlaying = true;

    this->restartGame();
    while (_isPlaying) {
        _t1 = clock();
        _elapsed = (_t1 - _t2) / 1000;
        _elapsed2 = (_t1 - _t3) / 1000;
        _eventGame = _displayLibs.at(_actualLib)->manageEventsGame();
        this->manageGame();
        this->foundHighScore();
        this->storeHighScore();
        _displayLibs.at(_actualLib)->drawScores(this->_playerName, _displayGames.at(_gameSelected)->getScore(), _scoreTab.first, _scoreTab.second);
        if (_elapsed > 24) {
            _t2 = clock();
            _displayLibs.at(_actualLib)->drawMap(_displayGames.at(_gameSelected)->getMap(), _displayGames.at(_gameSelected)->getMapEntity());
            if (_displayGames.at(_gameSelected)->refreshGame() == 1) {
                this->storeHighScore();
                this->foundHighScore();
                this->manageGameOver();
            }
        }
    }
    if (_isPlaying == false && _eventGame == MENU)
        this->startGame();
}

void Core::manageGame()
{
    switch (_eventGame) {
        case NEXT_LIB:
            this->nextLib();
            break;
        case PREV_LIB:
            this->prevLib();
            break;
        case PREV_GAME:
            this->prevGame();
            break;
        case NEXT_GAME:
            this->nextGame();
            break;
        case RESTART:
            this->restartGame();
            break;
        case MENU:
            _isPlaying = false;
            break;
        case END:
            _isPlaying = false;
            break;
        case NONE:
            break;
        case PAUSE:
            this->managePause();
            break;
        default:
            if (_elapsed2 > 15) {
                _t3 = clock();
                _displayGames.at(_gameSelected)->makeAction((DIRECTION)(_eventGame - 6));
            }
            break;
    }
}

void Core::manageGameOver()
{
    _isGameOver = true;
    _displayLibs.at(_actualLib)->clearWindow();
    _displayLibs.at(_actualLib)->drawGameOver(_displayGames.at(_gameSelected)->getScore());
    while (_isGameOver) {
        _eventGameOver = _displayLibs.at(_actualLib)->manageGameOver();
        switch (_eventGameOver) {
            case NEXT_LIB:
                this->nextLib();
                break;
            case PREV_LIB:
                this->prevLib();
                break;
            case RESTART:
                this->restartGame();
                _isGameOver = false;
                return;
            case END:
                _isGameOver = false;
                break;
            default:
                break;
        }
    _displayLibs.at(_actualLib)->drawGameOver(_displayGames.at(_gameSelected)->getScore());
    }
    _isPlaying = false;
}

void Core::foundHighScore()
{
    std::fstream myFile;
    std::string line;
    std::string playerName;
    int playerScore;
    size_t found;

    myFile.open(_displayGames.at(_gameSelected)->getName() + ".score");
    if (!myFile.is_open())
        throw ParsingError("The file can't be read");
    for (; getline(myFile, line); ) {
        if ((found = line.find(" == ")) != std::string::npos) {
            playerName = line.substr(0, line.find(" == "));
            playerScore = std::stoi(line.substr(found + 4, line.size()));
            _scoreTab = std::make_pair(playerName, playerScore);
        }
    }
    myFile.close();
}

void Core::storeHighScore()
{
    int score = _displayGames.at(_gameSelected)->getScore();

    if (score > _scoreTab.second) {
        _highScoreFile.open(_displayGames.at(_gameSelected)->getName() + ".score", std::ios::trunc);
        _highScoreFile << _playerName << " == " << score << std::endl;
        _highScoreFile.close();
    }
}

void Core::nextLib()
{
    _displayLibs.at(_actualLib)->closeWindow();
     _actualLib++;
     if (_actualLib > 2)
        _actualLib = 0;
    _displayLibs.at(_actualLib)->openWindow();
    _displayLibs.at(_actualLib)->clearWindow();
}

void Core::prevLib()
{
    _displayLibs.at(_actualLib)->closeWindow();
    _actualLib--;
    if (_actualLib < 0)
        _actualLib = 2;
    _displayLibs.at(_actualLib)->openWindow();
    _displayLibs.at(_actualLib)->clearWindow();
}

void Core::nextGame()
{
    _gameSelected++;
    if (_gameSelected >= (int) _displayGames.size())
        _gameSelected = 0;
    _displayGames.at(_gameSelected)->resetGame();
    this->prepareGame();
}

void Core::prevGame()
{
     _gameSelected--;
    if (_gameSelected < 0)
        _gameSelected = _displayGames.size() - 1;
    _displayGames.at(_gameSelected)->resetGame();
    this->prepareGame();
}

void Core::prepareGame()
{
    _displayGames.at(_gameSelected)->initGame();
    _displayLibs.at(_actualLib)->clearWindow();
    _displayLibs.at(_actualLib)->drawMap(_displayGames.at(_gameSelected)->getMap(), _displayGames.at(_gameSelected)->getMapEntity());
    _displayLibs.at(_actualLib)->drawScores(this->_playerName, _displayGames.at(_gameSelected)->getScore(), _scoreTab.first, _scoreTab.second);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Core::restartGame()
{
    _displayGames.at(_gameSelected)->resetGame();
    this->prepareGame();
}

void Core::managePause()
{
    _eventGame = _displayLibs.at(_actualLib)->manageEventsGame();
    while (_eventGame != PAUSE && _eventGame != END)
        _eventGame = _displayLibs.at(_actualLib)->manageEventsGame();
    if (_eventGame == END)
        _isPlaying = false;
}