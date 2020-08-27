/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Bomberman game
*/

#ifndef MAP_HPP_
#define MAP_HPP_


#include <vector>
#include <iostream>
#include "Board.hpp"
#include "Block.hpp"

typedef std::vector<std::vector<std::shared_ptr<Block>>> board;

class Map {
    public:
        Map() {};
        ~Map() {};

        board mapGenerator(int x, int y);
        board createMap(int x, int y);
        board digPath(board map, std::vector<std::pair<int, int>> digger, std::vector<int> way, std::pair<int, int> map_size);
        std::vector<int> fillWay(board map, std::vector<std::pair<int, int>> digger, std::vector<int> way, int step, std::pair<int, int> map_size);
        std::vector<std::pair<int, int>> dig(std::vector<std::pair<int, int>> digger, std::vector<int> way, int step);
        int checkRandom(std::vector<int> way);
        board breakableWall(board map, int x, int y);
        board resizeMap(board map, int x, int y);
    protected:
    private:
};

#endif /* !MAP_HPP_ */
