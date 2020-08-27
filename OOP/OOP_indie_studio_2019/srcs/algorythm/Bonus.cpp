/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Bonus
*/

#include "Bonus.hpp"
#include <random>

Bonus::Bonus(Types::BonusType _type, std::pair<int, int> pos)
{
    type = _type;
    position = pos;
}

Bonus::~Bonus() {}

std::pair<float, float> Bonus::GetPosition() { 
    return std::make_pair(position.first * BLOCK_SIZE, position.second * BLOCK_SIZE);
}

std::pair<int, int> Bonus::GetPositionRelative() { return position; }

Types::Entity Bonus::GetType() { return Types::Entity::BONUS; }

Types::BonusType Bonus::GetBonusType() { return type; }
