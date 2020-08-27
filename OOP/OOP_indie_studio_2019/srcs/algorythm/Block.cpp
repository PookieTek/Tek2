/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Block.cpp
*/

#include "Block.hpp"

Block::Block(Types::BlockType _type, std::pair<float, float> _pos) : type(_type), pos(_pos) {
    if (type != Types::BlockType::WALKABLE)
        isBlocking = true;
    if (type == Types::BlockType::SOFT)
        isBreakable = true;
    isInFire = -1;
    isBreak = false;
}

Block::~Block() {}

Types::BlockType Block::GetBlockType() { return (type); }
int Block::GetFireStatus() {return (isInFire); }
bool Block::IsBreak() { return (isBreak); }
bool Block::IsBlocking() { return (isBlocking); }
bool Block::IsBreakable() { return (isBreakable); }

void Block::SetBreak(bool _isBreak) {
    if (type == Types::BlockType::SOFT)
        isBreak = _isBreak;
}

std::pair<float, float> Block::GetPosition() { return (pos); }

Types::Entity Block::GetType() { return (Types::Entity::BLOCK); }

std::pair<int, int> Block::GetPositionRelative() {
    return (std::make_pair(pos.first / BLOCK_SIZE, pos.second / BLOCK_SIZE));
}

void Block::SetInFire(int fire) {
    isInFire = fire; 
    fireTime.Restart();
}

void Block::SetBlockType(Types::BlockType _type) { type = _type; }