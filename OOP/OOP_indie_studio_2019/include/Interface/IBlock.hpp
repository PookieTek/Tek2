/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IBlock.hpp
*/

#ifndef _IBLOCK_HPP
#define _IBLOCK_HPP

#include "Interface/IDrawable.hpp"
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif
namespace Types {
    enum BlockType {
        WALKABLE,
        SOFT,
        HARD,
    };
};

class IBlock : public IDrawable {
    public:
        virtual ~IBlock() {};

        virtual Types::BlockType GetBlockType() = 0;
        virtual int GetFireStatus() = 0;
        virtual bool IsBreak() = 0;
};

#endif