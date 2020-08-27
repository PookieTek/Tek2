/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include <iostream>
#include "Player.hpp"

Bomb::Bomb(std::shared_ptr<Player> _owner)
{
    owner = _owner->GetName();
    position = std::make_pair<float, float>(_owner->GetPositionRelative().first * BLOCK_SIZE, (_owner->GetPositionRelative().second * BLOCK_SIZE) + 10);
    status = Types::BombStatus::FULL;
    isExploded = false;
    isMoving = false;
    vectorMove = std::make_pair<float, float>(0, 0);
}

Bomb::~Bomb()
{
}

std::pair<float, float> Bomb::GetPosition() {return position;}
Types::Entity Bomb::GetType() { return Types::Entity::BOMB; }
std::pair<int, int> Bomb::GetPositionRelative() {
    return (std::make_pair(position.first / BLOCK_SIZE, position.second / BLOCK_SIZE));
} 

std::string Bomb::GetOwner() { return owner;}
bool Bomb::IsMoving() { return isMoving; }
bool Bomb::IsExplode() { return isExploded; }

void Bomb::SetMove() {isMoving = true;}

void Bomb::MovePosition(std::pair<float, float> targ) {
    position.first += targ.first;
    position.second += targ.second;
}

void Bomb::Pause() { timer.Pause();}
void Bomb::Resume() { timer.Resume(); }

Types::BombStatus Bomb::GetStatus() {
    if (timer.IsBreak())
        return status;
    if (timer.GetTimeLapsed() < EXPLODE_TIME / 2)
        status = Types::BombStatus::FULL;
    else if (timer.GetTimeLapsed() < 3 * EXPLODE_TIME / 4)
        status = Types::BombStatus::HALF;
    else if (timer.GetTimeLapsed() < EXPLODE_TIME)
        status = Types::BombStatus::IMMINENT;
    else {
        status = Types::BombStatus::EXPLODE;
        isExploded = true;
    }
    return status;
}

void Bomb::SetVector(std::pair<float, float> vector) { vectorMove = vector; }
std::pair<float, float> Bomb::GetVector() { return vectorMove;}

void Bomb::ForceExplosion() {
    timer.Pause();
    status = Types::BombStatus::EXPLODE;
    isExploded = true;
}