/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Game.hpp
*/

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Interface/IGame.hpp"
#include "Timer.hpp"
#include "Player.hpp"
#include "Board.hpp"

class Game : public IGame {
    public:
        Game();
        ~Game();

        std::shared_ptr<IBoard> GetBoard();
        std::vector<std::shared_ptr<IPlayer>> GetPlayers();
        Types::Stage GetStatus();
        int GetTimeLeft();
        void AddPlayer(std::string);
        void AddPlayer(std::string, bool);
        void DelPlayer(std::string);
        bool StartGame();
        bool StartGame(std::string);
        void SetStatus(Types::Stage);
        void GameOver();
        std::vector<std::shared_ptr<IDrawable>> GetEntities();
        std::vector<std::shared_ptr<IDrawable>> GetEntities(Types::Entity);
        std::shared_ptr<IPlayer> GetPlayerByName(std::string);
        void SaveGame();
        void LoadGame(std::string);
        void LoadPlayer(std::string);
        void CheckConfig();


    private:
        std::shared_ptr<Board> board;
        std::vector<std::shared_ptr<Player>> players;
        Types::Stage stage;
        Timer timer;
        int duration;
};

#endif