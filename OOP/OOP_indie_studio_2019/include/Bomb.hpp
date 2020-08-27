/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Interface/IBomb.hpp"
#include "Timer.hpp"
#include <memory>


class Player;

class Bomb : public IBomb {
    public:
        Bomb(std::shared_ptr<Player>);
        ~Bomb();

        std::pair<float, float> GetPosition();
        Types::Entity GetType();
        std::pair<int, int> GetPositionRelative();

        std::string GetOwner();
        Types::BombStatus GetStatus();
        bool IsMoving();
        bool IsExplode();
        void MovePosition(std::pair<float, float>);
        void Pause();
        void Resume();
        void SetMove();
        void SetVector(std::pair<float, float>);
        std::pair<float, float> GetVector();
        void ForceExplosion();

    protected:
    private:
        std::pair<float, float> position;
        std::string owner;
        Timer timer;
        Types::BombStatus status;
        bool isMoving;
        bool isExploded;
        std::pair<float, float> vectorMove;
};

#endif /* !BOMB_HPP_ */
