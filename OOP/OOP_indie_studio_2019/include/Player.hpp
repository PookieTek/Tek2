/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include "Interface/IPlayer.hpp"
#include "Interface/IBonus.hpp"
#include "Bomb.hpp"
#include "Timer.hpp"
#include "SoundTest.hpp"

class Player : public IPlayer {
    public:
        Player(std::string, int);
        Player(std::string, bool, int);
        ~Player();


        void AddBomb();
        void DelBomb();
        void AddScore(int);
        void AddBonus(Types::BonusType);
        void PlayerStatus();

        /* GETTER IDRAWABLE */
        std::pair<float, float> GetPosition();
        Types::Entity GetType();
        std::pair<int, int> GetPositionRelative();

        /* GETTER */
        std::string GetName();
        int GetSpeed();
        int GetBomb();
        int GetLife();
        int GetScore();
        int GetRadius();
        Types::Status GetStatus();
        std::pair<int, int> GetSpawn();
        int GetFrame();
        Types::PlayerOrientation GetOrientation();
        Types::PlayerModel GetPlayerModel();
        int GetBombUse();
        bool IsWalkThrough();
        bool IsBot();
        bool GetRun();

        /* SETTER */
        void SetStatus(Types::Status);
        void SetSpawn(std::pair<int, int>);
        void SetSpawn(int);
        void SetPosition(std::pair<float, float>);
        void SetPlayerModel(Types::PlayerModel);
        void SetBomb(int);
        void SetRadius(int);
        void SetSpeed(int);
        void SetLife(int);
        void SetWalk(bool);
        void SetFrame(int);
        void SetOrientation(Types::PlayerOrientation);
        bool CouldPutBomb();
        void SetBot(bool);
        void SetRun(bool);

    SoundTest                               soundTest;

    protected:
    private:
        std::string                         pseudo;
        unsigned int                        speed;
        unsigned int                        bombs;
        int                                 BombInUse;
        unsigned int                        life;
        bool                                walkThrough;
        unsigned int                        radiusBonus;
        std::pair<float, float>             position;
        Types::Status                       status;
        std::pair<int, int>                 spawn;
        unsigned int                        score;
        bool                                isBot;
        Types::PlayerModel                  playerModel;
        Types::PlayerOrientation            orientation;
        int                                 frame;
        Timer                               statusUpdate;
        Timer                               dropBomb;
        bool                                runAway;
        Timer                               botTimerCheck;
};

#endif /* !PLAYER_HPP_ */
