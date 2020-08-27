/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** map
*/

#include "snake.hpp"
#include <iostream>
#include <time.h>

void Snake::SetApple() {
    int x;
    int y;
    bool succes = true;

    x = rand() % 36;
    y = rand() % 76;
    for (std::list<Player>::iterator it = player.begin(); it != player.end(); it++) {
        if (it->x == x && it->y == y)
            succes = false;
    }
    if (!succes)
        SetApple();
    else {
        foodX = x;
        foodY = y;
    }
    isFood = true;
}

void Snake::CleanMap() {
    for (int i = 0; i < (int)board.size(); i++)
        for (int j = 0; j < (int)board.at(i).size(); j++)
            board.at(i).at(j) = AssetInfo {0, "empty/", AssetOrientation::UP};
}

void Snake::FillMap() {
    std::list<Player>::iterator it;

    CleanMap();
    for (it = player.begin(); it != player.end(); it++) {
        if (it->position == 1) {
            board.at(it->x).at(it->y) = AssetInfo {2, "head/", it->dir};
        } else if (it->position != player.back().position) {
            board.at(it->x).at(it->y) = AssetInfo {3, "body/", it->dir};
        } else {
            board.at(it->x).at(it->y) = AssetInfo {4, "tail/", it->dir};
        }
    }
    if (isFood)
        board.at(foodX).at(foodY) = AssetInfo {1, "apple/", AssetOrientation::UP};
}
