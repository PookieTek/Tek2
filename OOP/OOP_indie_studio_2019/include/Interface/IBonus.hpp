/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IBonus.hpp
*/

#ifndef _IBONUS_HPP_
#define _IBONUS_HPP_

#include "Interface/IDrawable.hpp"
#include "Config.hpp"
#include <memory>
#ifdef _WIN32
#include <string>
#endif
namespace Types {
    enum BonusType {
        LIFE,
        WALKTHROUGH,
        RADIUS,
        BOMBBONUS,
        SPEED,
    };
};

class IBonus : public IDrawable {
    public:
        virtual ~IBonus() {};

        virtual Types::BonusType GetBonusType() = 0;

};


#endif