/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "../../include/IGameLib.hpp"
#include <vector>
#include <list>
#include <map>

struct Player {
    int x;
    int y;
    int position;
    int dir;
};

class Snake : public IGameLib
{
    public:
        Snake();
        ~Snake() {};

        std::vector<std::vector<AssetInfo>> Refresh();
        void Move(Interaction::Bind);
        void Quit();
        bool GameOver();
        bool GameWin();
        int GetScore();
        std::string GetName();



        void Feed();
        void SetApple();
        int Foward();
        void FillMap();
        void CleanMap();
        bool AddTail();
       
        std::string GetAsset();

        std::list <Player> player;
        std::vector <std::vector <AssetInfo>> board;
        int direction;
        bool isFood;
        int foodX;
        int foodY;
        int isFeed;
        bool gameOver;
        int score;
        std::string assetpath;
        std::string gameName;
        bool speedup;
};

bool isOver(int x, int y, std::list<Player>);

#endif /* !SNAKE_HPP_ */
