/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** player.cpp
*/

#include <thread>
#include "Player.hpp"
#include "Bomb.hpp"
#include "MyException.hpp"
#include <random>

Player::Player(std::string name, int indexPlayer) : pseudo(name)
{
    speed = INIT_SPEED;
    bombs = INIT_BOMBS;
    life = INIT_LIFE;
    BombInUse = 0;
    score = 0;
    orientation = Types::PlayerOrientation::DOWN;
    frame = 0;
    status = Types::Status::ALIFE;
    playerModel = static_cast<Types::PlayerModel>(indexPlayer);
    radiusBonus = INIT_RADIUS;
    SetSpawn(indexPlayer);
    position = std::make_pair<float, float>(spawn.first * BLOCK_SIZE, spawn.second * BLOCK_SIZE);
    isBot = false;
    walkThrough = false;
    runAway = false;
} 

Player::Player(std::string name, bool _IsBot, int indexPlayer) : pseudo(name), isBot(_IsBot)
{
    speed = INIT_SPEED;
    bombs = INIT_BOMBS;
    life = INIT_LIFE;
    BombInUse = 0;
    score = 0;
    orientation = Types::PlayerOrientation::DOWN;
    frame = 0;
    status = Types::Status::ALIFE;
    playerModel = static_cast<Types::PlayerModel>(indexPlayer);
    radiusBonus = INIT_RADIUS;
    SetSpawn(indexPlayer);
    position = std::make_pair<float, float>(spawn.first * BLOCK_SIZE, spawn.second * BLOCK_SIZE);
    walkThrough = false;
    runAway = false;
}

Player::~Player() {}


void Player::AddScore(int toAdd) { score += toAdd; }
void Player::AddBomb() {
    BombInUse++;
    dropBomb.Restart();
};


void Player::PlayerStatus() {
    if (status == Types::Status::ALIFE) {
        soundTest.SoundPlay(DIE); // On ne l'entend pas à cause de l'explosion
        SetPosition(std::make_pair<float, float>(0, 0));
        life --;
        if (life > 0) {
            status = Types::Status::DIE;
            statusUpdate.Restart();
        } else
            status = Types::Status::LOOSE;
    } else if (status != Types::Status::LOOSE && statusUpdate.GetTimeLapsed() > RESPAWN_TIMER) {
        soundTest.SoundPlay(SPAWN);
        status = Types::Status::ALIFE;
        SetPosition(std::make_pair<float, float>(spawn.first * BLOCK_SIZE, spawn.second * BLOCK_SIZE));
    }
}


void Player::DelBomb() {
    BombInUse--;
}


void Player::AddBonus(Types::BonusType type) {
    switch(type) {
        case Types::BonusType::LIFE: life++; break;
        case Types::BonusType::WALKTHROUGH: walkThrough = true; break;
        case Types::BonusType::RADIUS: radiusBonus++; break;
        case Types::BonusType::BOMBBONUS: bombs++; break;
        case Types::BonusType::SPEED: speed++; break;
        default: break;
    }
}


std::pair<float, float> Player::GetPosition() { return position; }
Types::Entity Player::GetType() { return (Types::Entity::PLAYER); }
std::pair<int, int> Player::GetPositionRelative() {
    return (std::make_pair((position.first + 62) / BLOCK_SIZE, (position.second + 45) / BLOCK_SIZE));
}
std::string Player::GetName() { return pseudo; }
int Player::GetSpeed() { return speed; }
int Player::GetBomb() { return bombs; }
int Player::GetLife() { return life; }
int Player::GetScore() { return score; }
int Player::GetFrame() { return frame; }
Types::PlayerOrientation Player::GetOrientation() { return orientation; }
int Player::GetRadius() { return radiusBonus; }
int Player::GetBombUse() { return BombInUse; }
std::pair<int, int> Player::GetSpawn() { return spawn; }
Types::PlayerModel Player::GetPlayerModel() { return playerModel; }
Types::Status Player::GetStatus() { return status; }
bool Player::CouldPutBomb() {return (dropBomb.GetTimeLapsed() > 500);}
bool Player::GetRun() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> distrib(0, 3);

    int result = distrib(gen);

    if (botTimerCheck.GetTimeLapsed() > EXPLODE_TIME + FIRE_TIME + (result * 1000))
        runAway = false;
    return runAway;
}

void Player::SetBomb(int _bomb) {bombs = _bomb;}
void Player::SetRadius(int _radius) { radiusBonus = _radius;}
void Player::SetSpeed(int _speed) { speed = _speed;}
void Player::SetLife(int _life) { life = _life;}
void Player::SetWalk(bool walk) { walkThrough = walk;}
void Player::SetPlayerModel(Types::PlayerModel model) { playerModel = model; }
void Player::SetStatus(Types::Status stat) { status = stat; }
void Player::SetFrame(int fr) {frame = fr;}
void Player::SetSpawn(std::pair<int, int> _spawn) { spawn = _spawn; }
void Player::SetOrientation(Types::PlayerOrientation _orient) {orientation = _orient;}
void Player::SetBot(bool bot) {isBot = bot;}
void Player::SetRun(bool run) { 
    runAway = run;
    botTimerCheck.Restart();
}

void Player::SetSpawn(int indexPlayer) {
    int resolutionX = RESOLUTION_X / BLOCK_SIZE;
    int resolutionY = RESOLUTION_Y / BLOCK_SIZE;
    std::pair<int, int> spawnList[4];
    
    spawnList[0] = std::make_pair<int, int>(1, 1);
    spawnList[1] = std::make_pair<int, int>(resolutionX - 2, 1);
    spawnList[2] = std::make_pair<int, int>(1, resolutionY - 2);
    spawnList[3] = std::make_pair<int, int>(resolutionX - 2, resolutionY - 2);

    if (indexPlayer >= 0 && indexPlayer <= 3)
        spawn = spawnList[indexPlayer];
}

void Player::SetPosition(std::pair<float, float> pos) { 
    if (pos.first < 0 || pos.first > RESOLUTION_X || pos.second < 0 || pos.second > RESOLUTION_Y) {
        std::cout << "Invalid Position : " << pos.first << " " << pos.second << std::endl;
        throw MyException("Error : Invalid Position");
    }
    position = pos;
}

bool Player::IsBot() { return isBot; }

bool Player::IsWalkThrough() { return walkThrough; }
