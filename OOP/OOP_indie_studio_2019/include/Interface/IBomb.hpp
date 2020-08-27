/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IBomb.hpp
*/

#ifndef _IBOMB_HPP_
#define _IBOMB_HPP_


#include "Interface/IDrawable.hpp"
#include "Interface/IPlayer.hpp"
#include <memory>
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif

namespace Types {
    enum BombStatus {
        FULL,
        HALF,
        IMMINENT,
        EXPLODE,
    };
};

class IBomb : public IDrawable{
    public:
        virtual ~IBomb() {};

        virtual Types::BombStatus GetStatus() = 0;
        virtual bool IsMoving() = 0;
};

#endif