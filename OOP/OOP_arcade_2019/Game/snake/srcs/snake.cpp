/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#include "snake.hpp"
#include <iostream>
#include <time.h>

Snake::Snake() : IGameLib() {
    std::vector<AssetInfo> tmp(76, AssetInfo {0, "empty/", AssetOrientation::UP});
    Player stock;

    stock.x = 18;
    stock.y = 38;
    stock.position = 1;
    stock.dir = 1;
    
    for (int i = 0; i < 36; i++) {
        board.push_back(tmp);
    }
    player.push_front(stock);
    for (int i = 0; i < 3; i++) {
        stock.y--;
        stock.position++;
        player.push_back(stock);
    }
    direction = 1;
    isFood = false;
    isFeed = false;
    gameOver = false;

    assetpath = "/snake/asset/";
    score = 0;
    gameName = "Nibbler";
}

bool isOver(int x, int y, std::list<Player> player) {
    std::list<Player>::iterator it;

    if (x < 0 || x >= 36 || y < 0 || y >= 76)
        return true;
    for (it = player.begin(); it != player.end(); it++) {
        if (it->x == x && it->y == y)
            return true;
    }    
    return false;
}

bool Snake::AddTail() {
    std::list<Player>::iterator tail = player.end();

    tail--;
    int x = tail->x;
    int y = tail->y;

    if (tail->dir == 0)
        x++;
    else if (tail->dir == 1)
        y--;
    else if (tail->dir == 2)
        x--;
    else
        y++;
    if (x < 0 || x >= 36 || y < 0 || y >= 76)
        return false;
    player.push_back(Player{x, y, tail->position + 1, tail->dir});
    return true;
}


std::vector<std::vector<AssetInfo>> Snake::Refresh() {
    srand(time(NULL));
    if (!isFood)
        SetApple();
    if (Foward() != 0)
        gameOver = true;
    else
        FillMap();
    return board;
}

void Snake::Quit() {
    this->~Snake();
}

void Snake::Feed() {
    isFeed = 1;
    score += 10;
}

std::string Snake::GetAsset() { return assetpath; }

int Snake::GetScore() { return score;}

std::string Snake::GetName() { return gameName;}

bool Snake::GameOver() {
    return gameOver;
}

bool Snake::GameWin() {
    return false;
}

extern "C" IGameLib *creatorGame() {
    return (new Snake);
}