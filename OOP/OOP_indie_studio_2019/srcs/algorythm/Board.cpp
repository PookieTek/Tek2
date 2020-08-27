/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Board
*/

#include "Board.hpp"
#include "MyException.hpp"
#include <algorithm>
#include <ctime>
#include <vector>
#include "Tools.hpp"
#include "Map.hpp"

Board::Board(std::vector<std::shared_ptr<Player>> playerlist) : players(playerlist)
{
    Map generator;
    size = std::make_pair(RESOLUTION_X / BLOCK_SIZE, RESOLUTION_Y / BLOCK_SIZE);
    board = generator.mapGenerator((RESOLUTION_X / BLOCK_SIZE) - 2, (RESOLUTION_Y / BLOCK_SIZE) - 2);
}

Board::~Board()
{
}

std::shared_ptr<Player> Board::GetPlayerByName(std::string name) {
    for (auto pl : players)
        if (pl->GetName() == name)
            return pl;
    return nullptr;
}

std::pair<float, float> Board::GetSize() {
    return std::make_pair(size.first * BLOCK_SIZE, size.second * BLOCK_SIZE);
}

int Board::SetFire(std::shared_ptr<Bomb> boum) {
    int relativeX = boum->GetPositionRelative().first;
    int relativeY = boum->GetPositionRelative().second;
    int score = 0;

    for (int i = relativeX, toEpiCenter = 0; i < relativeX + (GetPlayerByName(boum->GetOwner())->GetRadius()); i++, toEpiCenter++) {
        if (i < 0 || i >= RESOLUTION_X / BLOCK_SIZE)
            continue;
        if (board.at(i).at(relativeY)->GetBlockType() != Types::BlockType::HARD) {
            board.at(i).at(relativeY)->SetInFire(toEpiCenter);
            if (board.at(i).at(relativeY)->GetBlockType() == Types::BlockType::SOFT) {
                board.at(i).at(relativeY)->SetBreak(true);
                score += 100;
                break;
            }
        } else
            break;
    }
    for (int i = relativeX, toEpiCenter = 0; i > relativeX - (GetPlayerByName(boum->GetOwner())->GetRadius()); i--, toEpiCenter++) {
        if (i < 0 || i >= RESOLUTION_X / BLOCK_SIZE)
            continue;
        if (board.at(i).at(relativeY)->GetBlockType() != Types::BlockType::HARD) {
            board.at(i).at(relativeY)->SetInFire(toEpiCenter);
            if (board.at(i).at(relativeY)->GetBlockType() == Types::BlockType::SOFT) {
                board.at(i).at(relativeY)->SetBreak(true);
                score += 100;
                break;
            }
        } else
            break;
    }
    for (int i = relativeY, toEpiCenter = 0; i < relativeY + (GetPlayerByName(boum->GetOwner())->GetRadius()); i++, toEpiCenter++) {
        if (i < 0 || i >= RESOLUTION_Y / BLOCK_SIZE)
            continue;
        if (board.at(relativeX).at(i)->GetBlockType() != Types::BlockType::HARD) {
            board.at(relativeX).at(i)->SetInFire(toEpiCenter);
            if (board.at(relativeX).at(i)->GetBlockType() == Types::BlockType::SOFT) {
                board.at(relativeX).at(i)->SetBreak(true);
                score += 100;
                break;
            }
        } else
            break;
    }
    for (int i = relativeY, toEpiCenter = 0; i > relativeY - (GetPlayerByName(boum->GetOwner())->GetRadius()); i--, toEpiCenter++) {
        if (i < 0 || i >= RESOLUTION_Y / BLOCK_SIZE)
            continue;
        if (board.at(relativeX).at(i)->GetBlockType() != Types::BlockType::HARD) {
            board.at(relativeX).at(i)->SetInFire(toEpiCenter);
            if (board.at(relativeX).at(i)->GetBlockType() == Types::BlockType::SOFT) {
               board.at(relativeX).at(i)->SetBreak(true);
                score += 100;
                break;
            }
        } else
            break;
    }
    return score;
}

bool Board::IsPlayer(std::pair<float, float> pos) {
    for (int i = 0; i < players.size(); i++)
        if (players.at(i)->GetPositionRelative() == std::make_pair<int, int>(pos.first / BLOCK_SIZE, pos.second / BLOCK_SIZE))
            return true;
    return false;
}

void Board::AddBonus(std::shared_ptr<Bonus> _bonus) {bonus.push_back(_bonus); }

std::vector<std::vector<std::shared_ptr<IBlock>>> Board::GetBoard()
{
    int a = 0;
    int score = 0;
    int rd = -1;

    if (board.size() == 0) {
        throw MyException("Error\tThe Board Should Not Be Empty");
        std::vector<std::vector<std::shared_ptr<IBlock>>> tmp;
        return tmp;
    }
    std::for_each(players.begin(), players.end(),
    [&](std::shared_ptr<Player> player) {
        if (player->GetStatus() != Types::Status::ALIFE)
            player->PlayerStatus();
    });
    for (int x = 0; x < board.size(); x++) {
        for (int y = 0; y < board.at(x).size(); y++) {
            if (board[x][y]->fireTime.GetTimeLapsed() > FIRE_TIME)
                board.at(x).at(y)->SetInFire(-1);
            if (board.at(x).at(y)->IsBreak()) {
                board.at(x).at(y)->SetBreak(false);
                board.at(x).at(y) = std::make_shared<Block>(Types::BlockType::WALKABLE, std::make_pair<float, float>(x * BLOCK_SIZE, y * BLOCK_SIZE));
                rd = Bonus::RandomBonus();
                if (rd != -1) {
                    AddBonus(std::make_shared<Bonus>(static_cast<Types::BonusType>(rd), std::make_pair<int, int>(x + 0, y + 0)));
                }
            }
        }
    }
    for (int i = 0; i < bombs.size(); i++) {
        auto vectorbomb = bombs.at(i)->GetVector();
        if (vectorbomb.first != 0 || vectorbomb.second != 0) {
            std::pair<float, float> cible = std::make_pair<float, float>(vectorbomb.first + bombs.at(i)->GetPosition().first, vectorbomb.second + bombs.at(i)->GetPosition().second);
            if (GetBlock(cible)->GetBlockType() != Types::BlockType::WALKABLE || IsPlayer(cible))
                bombs.at(i)->SetVector(std::make_pair<float, float>(0, 0));
            else  {
                bombs.at(i)->MovePosition(std::make_pair<float, float>(vectorbomb.first * (CINETIC_TRANSMISSION / 100.0), vectorbomb.second * (CINETIC_TRANSMISSION / 100.0)));
            }
        }
        if (bombs.at(i)->IsExplode()) {
            GetPlayerByName(bombs.at(i)->GetOwner())->AddScore(SetFire(bombs.at(i)));

            for (auto pl : players) {
                if (GetBlock(pl->GetPosition())->GetFireStatus() > -1) {
                    pl->PlayerStatus();
                    if (pl->GetName() == bombs[i]->GetOwner())
                        pl->AddScore(-100);
                    else
                        GetPlayerByName(bombs[i]->GetOwner())->AddScore(500);
                }
            }
        }
        if (GetBlock(bombs.at(i)->GetPosition())->GetFireStatus() != -1)
            bombs.at(i)->ForceExplosion();
    }
    for (int i = 0; i < bombs.size(); i++) {
        if (bombs.at(i)->IsExplode()) {
            GetPlayerByName(bombs.at(i)->GetOwner())->DelBomb();
            bombs.erase(bombs.begin() + i);
            i = 0;
        }
    }
    std::vector<std::vector<std::shared_ptr<IBlock>>> tmp;
    for (int i = 0; i < board.size(); i++)
        tmp.push_back(Tools::ExtractList<IBlock, Block>(board.at(i)));
    return tmp;
}

std::shared_ptr<IBlock> Board::GetBlock(std::pair<float, float> target) {
    if (target.first > RESOLUTION_X || target.first < 0 || target.second > RESOLUTION_Y || target.second < 0) {
        throw MyException("Error:\tInvalid Position");
    }
    int first = target.first / BLOCK_SIZE;
    int second = target.second / BLOCK_SIZE;

    if (board.size() > first && board.at(first).size() > second)
        return board.at(first).at(second);
    return NULL;
}

std::pair<int, int> Board::GetRelativeSize() { return size; }



bool Board::SetBomb(std::string name) {
    auto pl = GetPlayerByName(name);
    if (pl->GetStatus() != Types::Status::ALIFE)
        return false;
    if (pl != nullptr) {
        if (pl->GetBombUse() < pl->GetBomb() && pl->CouldPutBomb()) {
            pl->AddBomb();
            bombs.push_back(std::make_shared<Bomb>(pl));
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Bonus>> Board::GetBonus() {return bonus; }
std::vector<std::shared_ptr<Bomb>> Board::GetBombs() {return bombs; }

bool Board::Move(std::string name, std::pair<float, float> movement) {
    int index = 0;
    for (; index < players.size() && players.at(index)->GetName() != name; index++);
    if (index == players.size()) {
        return false;
    }
    std::pair<float, float> target(players.at(index)->GetPosition().first + movement.first + 60, players.at(index)->GetPosition().second + movement.second + 48);
    std::pair<float, float> finalTarget(players.at(index)->GetPosition().first + movement.first, players.at(index)->GetPosition().second + movement.second);
    if (GetBlock(target)->GetBlockType() == Types::BlockType::SOFT && !players.at(index)->IsWalkThrough()) {
        return false;
    }
    else if (GetBlock(target)->GetBlockType() == Types::BlockType::HARD) {
        return false;
    }
    for (int i = 0; i < players.size(); i++)
        if (players.at(i)->GetPositionRelative() == std::make_pair<int, int>(target.first / BLOCK_SIZE, target.second / BLOCK_SIZE) && i != index) {
            return false;
        }
    for (auto b : bombs) {
        if (b->GetOwner() == players[index]->GetName())
            if (b->GetPositionRelative() != std::make_pair<int, int>(target.first / BLOCK_SIZE, target.second / BLOCK_SIZE))
                b->SetMove();
    }

    for (auto b : bombs) {
        if (b->GetPositionRelative() == std::make_pair<int, int>(target.first / BLOCK_SIZE, target.second / BLOCK_SIZE))
            if (b->GetOwner() != name)
                return false;
            else if (b->IsMoving())
                b->SetVector(std::make_pair<float, float>(target.first - players.at(index)->GetPosition().first - 48, target.second - players.at(index)->GetPosition().second - 48));
    }

    for (int i = 0; i < bonus.size(); i++)
        if (bonus.at(i)->GetPositionRelative() == std::make_pair<int, int>(target.first / BLOCK_SIZE, target.second / BLOCK_SIZE)) {
            soundTest.SoundPlay(BONUS);
            players.at(index)->AddBonus(bonus.at(i)->GetBonusType());
            bonus.erase(bonus.begin() + i);
            i = 0;
        }
    players.at(index)->SetPosition(finalTarget);
    if (GetBlock(target)->GetFireStatus() != -1)
        players[index]->PlayerStatus();
    return true;
}
