/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGameModule.hpp"
#include <list>

class Pacman: public IGameModule {
    public:
        Pacman();
        ~Pacman();

        enum State {
            CHASE,
            FLEE
        };

        //Map
        void initGame();
        void generateMap();
        const std::vector<std::string> &getMap() const;
        int refreshGame();
        void resetGame();

        //Pacman
        void generateSnake();
        void movePacman(int x, int y);
        void makeAction(DIRECTION direction);
        int getScore() const;
        const std::string &getName() const;
        void eatPacgums(int x, int y);
        const std::map<char, Entity> &getMapEntity() const;
        void eatBigPacgum();
        void eatGhosts(char ghost);

        //Ghosts
        void moveGhost(int x, int y, char ghost);
        void ghostMoves();
        int checkFrontGhost(int ghost);
        int checkWall(int x, int y) const;
        void checkNotWall(int x, int y);
        int setDirectionGhost(int x, int y, int dir, int ghost);
        void exitGhost(char ghost);
        int setRandomDirection(int x, int y);
        int setBrainyDirection(int x, int y, int dir);
        int fleePacman(int x, int y, int dir);
        void moveGhost(int x, int y, char ghost, char color);
        void generateFruit();

    protected:
    private:
        std::vector<std::string> _map;
        std::vector<std::string> _map2;
        std::string _name = "Pacman";
        std::pair<int, int> _pacmanPos;
        std::map<char, Entity> _mapEntity;
        std::pair<int, int> *_tpPos;
        std::map<char, std::pair<int, int>> _ghostPos;
        std::map<char, int> _ghostDir;
        std::map<char, int> _ghostIntel;
        std::map<char, bool> _ghostExit;
        std::vector<int> _choice;
        std::map<char, int> _ghostState;
        int _time;
        int _dir;
        int _score;
        time_t _t1;
        std::map<char, time_t> _t2;
        time_t _t3;
        time_t _t4;
        double _timeToWait;
        double _fleeModeTime;
        std::map<char, clock_t> _t5;
        std::map<char, clock_t> _t6;
        int _combo;
        time_t _tFruit;
        time_t _tFruit2;


};

extern "C" IGameModule *loadGames()
{
    return new Pacman();
}

#endif /* !PACMAN_HPP_ */
