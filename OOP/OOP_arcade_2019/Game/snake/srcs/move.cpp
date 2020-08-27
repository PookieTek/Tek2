/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** move
*/

#include "snake.hpp"
#include <iostream>
#include <time.h>

int Snake::Foward() {
    int x = player.front().x;
    int y = player.front().y;
    std::list<Player>::iterator it, nit;

    switch (direction) {
        case 0:
            x--;
            break;
        case 1:
            y++;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        default:
            break;
    }
    if (isOver(x, y, player))
        return -1;
    if (isFood && x == foodX && y == foodY) {
        Feed();
        isFood = false;
    }
    it = player.end();
    nit = player.end();
    it--;
    nit--;
    nit--;
    for (; it->position > 1 && nit->position > 0; --it, --nit) {
        it->x = nit->x;
        it->y = nit->y;
        it->dir = nit->dir;
    }
    player.front().x = x;
    player.front().y = y;
    player.front().dir = direction;
    if (isFeed > 4)
        return -1;
    if (isFeed > 0) {
        if (AddTail())
            isFeed = 0;
        else
            isFeed++;
    }
    score += 1;
    if (speedup) {
        speedup = false;
        return Foward();
    }
    return 0;
}

void Snake::Move(Interaction::Bind dir) {
    if (dir == Interaction::Bind::RIGHT)
        direction++;
    else if (dir == Interaction::Bind::LEFT)
        direction--;
    if (direction > 3)
        direction = 0;
    else if (direction < 0)
        direction = 3;
    if (dir == Interaction::Bind::SPEED)
        speedup = true;
}