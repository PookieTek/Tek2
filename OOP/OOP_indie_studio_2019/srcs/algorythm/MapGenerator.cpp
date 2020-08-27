/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019 [WSL]
** File description:
** main
*/

#include "Block.hpp"
#include "Board.hpp"
#include "Map.hpp"

#include <stddef.h>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>

board Map::resizeMap(board map, int x, int y)
{
    std::vector<std::shared_ptr<Block>> v1;
    board v2;

    for (int i = 1; i < x + 1; i++) {
        for (int j = 1; j < y + 1; j++)
            v1.push_back(map[i][j]);
        v2.push_back(v1);
        v1.clear();
    }
    return (v2);
}

board Map::breakableWall(board map, int x, int y)
{
    int r;

    for (int i = 1; i < x; i++)
        for (int j = 1; j < y; j++) {
            r = rand() % 3;
            if (r == 0 && map[i][j]->GetBlockType() == Types::HARD)
                map[i][j]->SetBlockType(Types::SOFT);
        }
    return (map);
}

int Map::checkRandom(std::vector<int> way)
{
    int r = rand() % 4;
    while (way[r] != 1)
        r = rand() % 4;
    return (r);
}

std::vector<std::pair<int, int>> Map::dig(std::vector<std::pair<int, int>> digger, std::vector<int> way, int step)
{
    int x = digger[step].first;
    int y = digger[step].second;
    int r = checkRandom(way);

    if (r == 0)
        digger.push_back(std::make_pair(x - 1, y));
    else if (r == 1)
        digger.push_back(std::make_pair(x + 1, y));
    else if (r == 2)
        digger.push_back(std::make_pair(x, y - 1));
    else if (r == 3)
        digger.push_back(std::make_pair(x, y + 1));
    return (digger);
}

std::vector<int> Map::fillWay(board map, std::vector<std::pair<int, int>> digger, std::vector<int> way, int step, std::pair<int, int> map_size)
{
    int x = digger[step].first;
    int y = digger[step].second;
    int mx = map_size.first;
    int my = map_size.second;
    int h = Types::HARD;
    int w = Types::WALKABLE;

    if (x > 1 && y > 0 && y < my - 2 && map[x - 1][y]->GetBlockType() == h &&
        map[x - 2][y - 1]->GetBlockType() != w && map[x - 2][y + 1]->GetBlockType() != w &&
        map[x - 1][y - 1]->GetBlockType() != w && map[x - 1][y + 1]->GetBlockType() != w)
        way[0] = 1;
    if (x < mx - 2 && y > 0 && y < my - 1 && map[x + 1][y]->GetBlockType() == h &&
        map[x + 2][y - 1]->GetBlockType() != w && map[x + 2][y + 1]->GetBlockType() != w &&
        map[x + 1][y - 1]->GetBlockType() != w && map[x + 1][y + 1]->GetBlockType() != w)
        way[1] = 1;
    if (x > 0 && x < mx - 1 && y > 1 && map[x][y - 1]->GetBlockType() == h &&
        map[x - 1][y - 2]->GetBlockType() != w && map[x + 1][y - 2]->GetBlockType() != w &&
        map[x - 1][y - 1]->GetBlockType() != w && map[x + 1][y - 1]->GetBlockType() != w)
        way[2] = 1;
    if (x > 0 && x < mx - 1 && y < my - 2 && map[x][y + 1]->GetBlockType() == h &&
        map[x - 1][y + 2]->GetBlockType() != w && map[x + 1][y + 2]->GetBlockType() != w &&
        map[x - 1][y + 1]->GetBlockType() != w && map[x + 1][y + 1]->GetBlockType() != w)
        way[3] = 1;
    return (way);
}

board Map::digPath(board map, std::vector<std::pair<int, int>> digger, std::vector<int> way, std::pair<int, int> map_size)
{
    for (int step = 10000; step != 0 && step != -1;) {
        if (step == 10000)
            step = 0;
        for (int i = 0; i <= 3; i++)
            way[i] = 0;
        way = fillWay(map, digger, way, step, map_size);
        if (way[0] == 1 || way[1] == 1 || way[2] == 1 || way[3] == 1) {
            digger = dig(digger, way, step);
            step++;
            map[digger[step].first][digger[step].second]->SetBlockType(Types::BlockType::WALKABLE);
        } else {
            digger.pop_back();
            step--;
        }
    }
    return (map);
}

board Map::createMap(int x, int y)
{
    board map;

    for (int i = 0; i < x; i++) {
        std::vector<std::shared_ptr<Block>> axeY;
        for (int j = 0; j < y; j++)
            axeY.push_back(std::make_shared<Block>(Types::BlockType::HARD, std::make_pair<float, float>(x * BLOCK_SIZE, y * BLOCK_SIZE)));
        map.push_back(axeY);
    }
    return map;
}

board Map::mapGenerator(int x, int y)
{
    board map = createMap(x + 2, y + 2);
    std::vector<std::pair<int, int>> digger;
    std::vector<int> way = {0,0,0,0};
    std::pair<int, int> map_size = std::make_pair(x + 2, y + 2);

    srand(time(0));
    digger.push_back(std::make_pair(1, 1));
    map = digPath(map, digger, way, map_size);
    for (int i = y - 1; map[1][i]->GetBlockType() == 2; i--)
        map[1][i]->SetBlockType(Types::WALKABLE);
    for (int i = x - 1; map[i][1]->GetBlockType() == 2; i--)
        map[i][1]->SetBlockType(Types::WALKABLE);
    for (int i = y - 1; map[x][i]->GetBlockType() == 2; i--)
        map[x][i]->SetBlockType(Types::WALKABLE);
    map[1][1]->SetBlockType(Types::BlockType::WALKABLE);
    map[map_size.first - 2][1]->SetBlockType(Types::BlockType::WALKABLE);
    map[1][map_size.second - 2]->SetBlockType(Types::BlockType::WALKABLE);
    map[map_size.first - 2][map_size.second - 2]->SetBlockType(Types::BlockType::WALKABLE);
    map = breakableWall(map, x, y);
    /* map = resizeMap(map, x, y); */
    return (map);
}
