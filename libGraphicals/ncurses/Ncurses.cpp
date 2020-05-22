/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** ncursesLib.cpp
*/

#include "Ncurses.hpp"

ncursesLib::ncursesLib()
{
    _menuIndex = 0;
    _games.push_back("Snake ");
    _games.push_back("Pacman");
    _playerName = "";
    _games.push_back("PlayerName");
}

ncursesLib::~ncursesLib()
{
}

void ncursesLib::initColor()
{
    start_color();
    init_pair(1, COLOR_RED, 0);
    init_pair(2, COLOR_CYAN, 0);
    init_pair(3, COLOR_GREEN, 0);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_BLUE, COLOR_BLUE);
    init_pair(7, COLOR_GREEN, COLOR_GREEN);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
    init_pair(9, COLOR_CYAN, COLOR_CYAN);
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);
    init_pair(12, 13, 0);
    init_pair(13, COLOR_WHITE, 0);
    init_pair(14, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(15, 11, 11);
}

void ncursesLib::openWindow()
{
    initscr();
    nodelay(stdscr, true);
    this->initColor();
    curs_set(FALSE);
    init_color(COLOR_BLACK, 0, 0, 0);
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    _isOpen = true;
}

void ncursesLib::closeWindow()
{
    endwin();
    _isOpen = false;
}

bool ncursesLib::isOpen() const
{
    return (_isOpen);
}

void ncursesLib::clearWindow()
{
    clear();
}

KEY ncursesLib::manageEventsMenu()
{
    int key = getch();
    if (key == 27) {
        endwin();
        return (END);
    } else if (_menuIndex == 2 && ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key== KEY_BACKSPACE))) {
        if (key == KEY_BACKSPACE && !(this->_playerName.empty())) {
            this->_playerName.pop_back();
            clear();
            refresh();
        } else {
            this->_playerName += key;
        }
    }
    if (key == KEY_RIGHT)
        return (NEXT_LIB);
    if (key == KEY_LEFT) {
        return (PREV_LIB);
    }
    if (key == KEY_UP) {
        _menuIndex--;
        if (_menuIndex == -1)
            _menuIndex = 2;
    } else if (key == KEY_DOWN) {
        _menuIndex++;
        if (_menuIndex == 3)
            _menuIndex = 0;
    }
    if (key == 10) {
        clear();
        if (_menuIndex == 0)
            return (SNAKE);
        else
            return (PACMAN);
    }
    highlight();
    refresh();
    return (NONE);
}

KEY ncursesLib::manageEventsGame()
{
    int key = getch();
    if (key == 27) {
        endwin();
        return (END);
    }
    if (key == KEY_RIGHT)
        return (NEXT_LIB);
    if (key == KEY_LEFT)
        return (PREV_LIB);
    if (key == KEY_UP)
        return (NEXT_GAME);
    if (key == KEY_LEFT)
        return (PREV_GAME);
    if (key == 'r')
        return (RESTART);
    if (key == 'o')
        return (MENU);
    if (key == 'p')
        return (PAUSE);
    if (key == 'w')
        return (UP);
    else if (key == 's')
        return (DOWN);
    else if (key == 'a')
        return (LEFT);
    else if (key == 'd')
        return (RIGHT);
    refresh();
    return (NONE);
}

KEY ncursesLib::manageGameOver()
{
    int key = getch();
    if (key == 27) {
        endwin();
        return (END);
    }
    if (key == KEY_RIGHT)
        return (NEXT_LIB);
    if (key == KEY_LEFT) {
        return (PREV_LIB);
    }
    if (key == 'r') {
        return (RESTART);
    }
    return (NONE);
}

void ncursesLib::highlight() const
{
    attron(A_BOLD);
    for (int i = 0; i < (int)_games.size(); i++) {
        if (i == _menuIndex)
            attron(A_REVERSE);
        if (i == 2)
            mvprintw((i * 2) + 25, (_xmax / 2) - (_games[i].length() / 2), "%s : %s" , _games[i].c_str(), _playerName.c_str());
        else
            mvprintw((i * 2)  + 25, (_xmax / 2) - (_games[i].length() / 2), _games[i].c_str());
        attroff(A_REVERSE);
    }
    attroff(A_BOLD);
    refresh();
}

int ncursesLib::menu()
{
    int hi = 0;

    highlight();
    return (hi);
}

void ncursesLib::dispTitle()
{

    getmaxyx(stdscr, _ymax, _xmax);
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(1, _xmax / 2 - 64, "                                                                                                                                 ");
    mvprintw(2, _xmax / 2 - 64, "                                                                                                     dddddddd                    ");
    mvprintw(3, _xmax / 2 - 64, "               AAA                                                                                   d::::::d                    ");
    mvprintw(4, _xmax / 2 - 64, "              A:::A                                                                                  d::::::d                    ");
    mvprintw(5, _xmax / 2 - 64, "             A:::::A                                                                                 d::::::d                    ");
    mvprintw(6, _xmax / 2 - 64, "            A:::::::A                                                                                d:::::d                     ");
    mvprintw(7, _xmax / 2 - 64, "           A:::::::::A          rrrrr   rrrrrrrrr       cccccccccccccccc  aaaaaaaaaaaaa      ddddddddd:::::d     eeeeeeeeeeee    ");
    mvprintw(8, _xmax / 2 - 64, "          A:::::A:::::A         r::::rrr:::::::::r    cc:::::::::::::::c  a::::::::::::a   dd::::::::::::::d   ee::::::::::::ee  ");
    mvprintw(9, _xmax / 2 - 64, "         A:::::A A:::::A        r:::::::::::::::::r  c:::::::::::::::::c  aaaaaaaaa:::::a d::::::::::::::::d  e::::::eeeee:::::ee");
    mvprintw(10, _xmax / 2 - 64 , "        A:::::A   A:::::A       rr::::::rrrrr::::::rc:::::::cccccc:::::c           a::::ad:::::::ddddd:::::d e::::::e     e:::::e");
    mvprintw(11, _xmax / 2 - 64 , "       A:::::A     A:::::A       r:::::r     r:::::rc::::::c     ccccccc    aaaaaaa:::::ad::::::d    d:::::d e:::::::eeeee::::::e");
    mvprintw(12, _xmax / 2 - 64 , "      A:::::AAAAAAAAA:::::A      r:::::r     rrrrrrrc:::::c               aa::::::::::::ad:::::d     d:::::d e:::::::::::::::::e ");
    mvprintw(13, _xmax / 2 - 64 , "     A:::::::::::::::::::::A     r:::::r            c:::::c              a::::aaaa::::::ad:::::d     d:::::d e::::::eeeeeeeeeee  ");
    mvprintw(14, _xmax / 2 - 64 , "    A:::::AAAAAAAAAAAAA:::::A    r:::::r            c::::::c     ccccccca::::a    a:::::ad:::::d     d:::::d e:::::::e           ");
    mvprintw(15, _xmax / 2 - 64 , "   A:::::A             A:::::A   r:::::r            c:::::::cccccc:::::ca::::a    a:::::ad::::::ddddd::::::dde::::::::e          ");
    mvprintw(16, _xmax / 2 - 64 , "  A:::::A               A:::::A  r:::::r             c:::::::::::::::::ca:::::aaaa::::::a d:::::::::::::::::d e::::::::eeeeeeee  ");
    mvprintw(17, _xmax / 2 - 64 , " A:::::A                 A:::::A r:::::r              cc:::::::::::::::c a::::::::::aa:::a d:::::::::ddd::::d  ee:::::::::::::e  ");
    mvprintw(18, _xmax / 2 - 64 , "AAAAAAA                   AAAAAAArrrrrrr                cccccccccccccccc  aaaaaaaaaa  aaaa  ddddddddd   ddddd    eeeeeeeeeeeeee  ");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);

}

void ncursesLib::drawMenu()
{
    dispTitle();
    refresh();
    menu();
    refresh();
}

void ncursesLib::drawMap(std::vector<std::string> map, std::map<char, Entity> mapEntity)
{
    clear();
    for (int j = 0; j < (int)map.size(); j++) {
        for (int i = 0; i < (int)(map.at(j).size() * 2); i += 2) {
            if (map[j][i / 2] != ' ') {
                attron(COLOR_PAIR(mapEntity.at(map[j][i / 2]).getncursesColor()));
                mvprintw(j, i, "%c", map[j][i / 2]);
                if (mapEntity.at(map[j][i / 2]).getSize()[0] >= 1)
                    mvprintw(j, i + 1, "%c", map[j][i / 2]);
                attroff(COLOR_PAIR(mapEntity.at(map[j][i / 2]).getncursesColor()));
            }
        }
    }
    refresh();
}

void ncursesLib::drawScores(std::string player1, int score, std::string player2, int highScore)
{
    mvprintw(2, 70, "HighScore :");
    mvprintw(3, 70, "%s : %d", player2.c_str(), highScore);
    mvprintw(4, 70, "Score :");
    mvprintw(5, 70, "%s : %d", player1.c_str(), score);
    refresh();
}


const std::string &ncursesLib::getPlayerName() const
{
    return (_playerName);
}

void ncursesLib::drawGameOver(int score)
{
    std::string str = std::to_string(score);
    getmaxyx(stdscr, _ymax, _xmax);
    attron(COLOR_PAIR(2));
    mvprintw(4, _xmax / 2 - 45, "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$        /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ ");
    mvprintw(5, _xmax / 2 - 45, " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/       /$$__  $$| $$   | $$| $$_____/| $$__  $$");
    mvprintw(6, _xmax / 2 - 45, "| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$            | $$  \\ $$| $$   | $$| $$      | $$  \\ $$");
    mvprintw(7, _xmax / 2 - 45, "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$         | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/");
    mvprintw(8, _xmax / 2 - 45, "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/         | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$");
    mvprintw(9, _xmax / 2 - 45, "| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$            | $$  | $$  \\  $$$/  | $$      | $$  \\ $$");
    mvprintw(10, _xmax / 2 - 45, "|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$      |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$");
    mvprintw(11, _xmax / 2 - 45, " \\______/ |__/  |__/|__/     |__/|________/       \\______/     \\_/    |________/|__/  |__/");
    attroff(COLOR_PAIR(2));
    attron(A_BOLD);
    mvprintw(24, _xmax / 2 - (13 + str.length()) / 2 - 1, "Your score : %s", str.c_str());
    mvprintw(30, _xmax / 2 - 9, "PRESS R TO RESTART");
    mvprintw(32, _xmax / 2 - 10, "PRESS ESCAPE TO QUIT");
    attroff(A_BOLD);
}