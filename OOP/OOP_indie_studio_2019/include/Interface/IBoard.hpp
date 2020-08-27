/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IBoard.hpp
*/

#ifndef _IBOARD_HPP_
#define _IBOARD_HPP_

#include "Interface/IBlock.hpp"
#include "Interface/IBonus.hpp"
#include <vector>
#include <utility>
#include <memory>
#include "Interface/IPlayer.hpp"
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif
class Player;

class IBoard {
    public:
        virtual ~IBoard() {};

        virtual std::pair<float, float> GetSize() = 0;
        virtual std::vector<std::vector<std::shared_ptr<IBlock>>> GetBoard() = 0;
        virtual std::shared_ptr<IBlock> GetBlock(std::pair<float, float>) = 0;
        virtual std::pair<int, int> GetRelativeSize() = 0;
        virtual bool SetBomb(std::string) = 0;
        virtual bool Move(std::string name, std::pair<float, float>) = 0;
        virtual void IABot(std::shared_ptr<Player>) = 0;



};

#endif