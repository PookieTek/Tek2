/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IDrawable.hpp
*/

#ifndef _IDRAWABLE_HPP_
#define _IDRAWABLE_HPP_
#include <vector>
#include <utility>
#include <iostream>
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif

namespace Types {
    enum Entity {
        PLAYER,
        BONUS,
        BOMB,
        BLOCK,
    };
};

class IDrawable {
    public:
        virtual ~IDrawable() {};

        virtual std::pair<float, float> GetPosition() = 0;
        virtual Types::Entity GetType() = 0;
        virtual std::pair<int, int> GetPositionRelative() = 0;
};


#endif