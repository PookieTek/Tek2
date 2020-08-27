/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IGame.hpp
*/

#ifndef _IGAME_HPP_
#define _IGAME_HPP_

#include "Interface/IBoard.hpp"
#include "Interface/IPlayer.hpp"
#include "Interface/IDrawable.hpp"
#include <vector>
#include <memory>
#include "Config.hpp"
#ifdef _WIN32
#include <string>
#endif

namespace Types {
    enum Stage {
        MENU,
        GAME,
        PAUSE,
        END,
        QUIT,
    };
};

class IGame {
    public:
        virtual ~IGame() {};

        virtual std::shared_ptr<IBoard> GetBoard() = 0;
        virtual std::vector<std::shared_ptr<IPlayer>> GetPlayers() = 0;
        virtual Types::Stage GetStatus() = 0;
        virtual void SetStatus(Types::Stage) = 0;
        virtual int GetTimeLeft() = 0;
        virtual void AddPlayer(std::string) = 0;
        virtual void AddPlayer(std::string, bool) = 0;
        virtual void DelPlayer(std::string) = 0;
        virtual bool StartGame() = 0;
        virtual bool StartGame(std::string) = 0;
        virtual void SaveGame() = 0;
        virtual std::vector<std::shared_ptr<IDrawable>> GetEntities() = 0;
        virtual std::vector<std::shared_ptr<IDrawable>> GetEntities(Types::Entity) = 0;
        virtual std::shared_ptr<IPlayer> GetPlayerByName(std::string) = 0;

};

#endif