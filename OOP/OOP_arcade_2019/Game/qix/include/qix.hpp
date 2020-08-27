/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** qix
*/

#ifndef QIX_HPP_
#define QIX_HPP_

#include "../../include/IGameLib.hpp"

struct Player {
    int lines;
    int cols;
    int dir;
};

struct Monster {
    int lines;
    int cols;
    int dir;
};

struct Sparks {
    int lines;
    int cols;
    int dir;
};

struct Point {
    int lines;
    int cols;
};

enum Types {
    EMPTY,
    PLAYER,
    TRAIL,
    NWAKABLE,
    QIX,
    SPARKLE,
    BORDER
};

class Qix : public IGameLib
{
    public:
        Qix();
        ~Qix() {};

        std::vector<std::vector<AssetInfo>> Refresh();
        void Move(Interaction::Bind);
        void Quit();
        bool GameOver();
        bool GameWin();
        int GetScore();
        std::string GetAsset();
        std::string GetName();
        void fillBoard();
        bool IsInDrawn(int, int);
        void CreateAreaNW();
        void EraseTrail();
        std::pair<int, int> choseCorner();
        void fillBorderMap(void);
        void SetQix();
        int GetQixMapPosition(int lines, int cols);
        void ResetPlayer();


        std::string assetpath;
        std::string gameName;
        std::vector<std::vector<AssetInfo>> board;
        std::vector<std::vector<AssetInfo>> copyboard;
        Player player;
        Monster monster;
        std::vector<Sparks> mobs;
        bool gameOver;
        int score;
        Point lastPoint;
};

#endif
