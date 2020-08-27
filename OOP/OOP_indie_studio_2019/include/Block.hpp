/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Block.hpp
*/

#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include "Interface/IBlock.hpp"
#include "Timer.hpp"

class Block : public IBlock {
    public:
        Block(Types::BlockType, std::pair<float, float> pos);
        ~Block();

        std::pair<float, float> GetPosition();
        Types::Entity GetType();
        std::pair<int, int> GetPositionRelative();
        Types::BlockType GetBlockType();
        void SetBlockType(Types::BlockType);
        int GetFireStatus();
        bool IsBreak();
        bool IsBlocking();
        bool IsBreakable();
        void SetBreak(bool);
        void SetInFire(int);

        Timer                   fireTime;
    private:
        Types::BlockType        type;
        bool                    isBlocking;
        bool                    isBreakable;
        bool                    isBreak;
        int                     isInFire;
        std::pair<float, float> pos;
};

#endif