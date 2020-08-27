/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IPlayer.hpp
*/

#ifndef _IPLAYER_HPP_
#define _IPLAYER_HPP_

#include "Interface/IDrawable.hpp"
#include <memory>
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif
class IBomb;

namespace Types {
    enum Status {
        ALIFE,
        DIE,
        SPAWN,
        GETBONUS,
        WIN,
        LOOSE,
    };

    enum PlayerModel {
        MODEL1,
        MODEL2,
        MODEL3,
        MODEL4,
    };

    enum PlayerOrientation {
        DOWN,
        UP,
        RIGHT,
        LEFT,
    };
};

class IPlayer : public IDrawable {
    public:
        virtual ~IPlayer() {};

        virtual std::string GetName() = 0;
        virtual int GetSpeed() = 0;
        virtual int GetBomb() = 0;
        virtual int GetLife() = 0;
        virtual int GetScore() = 0;
        virtual int GetRadius() = 0;
        virtual bool IsWalkThrough() = 0;
        virtual Types::Status GetStatus() = 0;
        virtual void SetStatus(Types::Status) = 0;
        virtual bool IsBot() = 0;
        virtual Types::PlayerModel GetPlayerModel() = 0;
        virtual void SetPlayerModel(Types::PlayerModel) = 0;
        virtual void SetSpawn(std::pair<int, int>) = 0;
        virtual void SetPosition(std::pair<float, float>) = 0;
        virtual Types::PlayerOrientation GetOrientation() = 0;
        virtual int GetFrame() = 0;
        virtual void SetFrame(int) = 0;
        virtual void SetOrientation(Types::PlayerOrientation) = 0;
        virtual bool CouldPutBomb() = 0;
        virtual void SetBot(bool) = 0;
    };

#endif