/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** IA.cpp
*/

#include "Board.hpp"
#include <algorithm>

int Board::CheckPlayerPresence(std::pair<int, int> pos, std::string name) {
    std::vector<std::pair<int, int>> playersPos;
    std::vector<int> distance;
    bool block = false;
    int dist = -1;

    for (auto player : players) {
        if (player->GetName() != name && (player->GetPositionRelative().first == pos.first || player->GetPositionRelative().second == pos.second))
            playersPos.push_back(player->GetPositionRelative());
    }
    for (auto targ : playersPos) {
        block = false;
        if (targ.first == pos.first) {
            int dep = targ.second > pos.second ? pos.second : targ.second;
            int end = targ.second < pos.second ? pos.second : targ.second;

            for (; dep < end && block != true; dep++)
                if (GetBlock(std::make_pair<float, float>(pos.first * BLOCK_SIZE, dep * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
                    block = true;
            dep = targ.second > pos.second ? pos.second : targ.second;
            if (!block && (dist > end - dep || dist == -1))
                dist = end - dep;
        }
        if (targ.second == pos.second) {
            int dep = targ.first > pos.first ? pos.first : targ.first;
            int end = targ.first < pos.first ? pos.first : targ.first;

            for (; dep < end && block != true; dep++)
                if (GetBlock(std::make_pair<float, float>( dep * BLOCK_SIZE, pos.second * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
                    block = true;
            dep = targ.first > pos.first ? pos.first : targ.first;
            if (!block && (dist > end - dep || dist == -1))
                dist = end - dep;
        }
    }
    return (dist);
}

void Board::AStar(std::pair<int, int> d, std::pair<int, int> a, std::vector<std::vector<int>> *mapstar, int count) {
    if (d.first + 1 < mapstar->size() && (mapstar->at(d.first + 1).at(d.second) == -2 || count < mapstar->at(d.first + 1).at(d.second))) {
        if (d.first + 1 < board.size() && GetBlock(std::make_pair<float, float>((d.first + 1) * BLOCK_SIZE, d.second * BLOCK_SIZE))->GetBlockType() == Types::BlockType::WALKABLE) {
            mapstar->at(d.first + 1).at(d.second) = mapstar->at(d.first).at(d.second) + 1;
            AStar(std::make_pair<int, int>(d.first + 1, d.second + 0), a, mapstar, count + 1);
        } else if (GetBlock(std::make_pair<float, float>((d.first + 1) * BLOCK_SIZE, d.second * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
            mapstar->at(d.first + 1).at(d.second) = -1;
    }

  if (d.first - 1 > 0 && (mapstar->at(d.first - 1).at(d.second) == -2 || count < mapstar->at(d.first - 1).at(d.second))) {
        if (GetBlock(std::make_pair<float, float>((d.first - 1) * BLOCK_SIZE, d.second * BLOCK_SIZE))->GetBlockType() == Types::BlockType::WALKABLE) {
            mapstar->at(d.first - 1).at(d.second) = mapstar->at(d.first).at(d.second) + 1;
            AStar(std::make_pair<int, int>(d.first - 1, d.second + 0), a, mapstar, count + 1);
        } else if (GetBlock(std::make_pair<float, float>((d.first - 1) * BLOCK_SIZE, d.second * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
            mapstar->at(d.first - 1).at(d.second) = -1;
    }

    if (d.second + 1 < mapstar->at(0).size() && (mapstar->at(d.first).at(d.second + 1) == -2 || count < mapstar->at(d.first).at(d.second + 1))) {
        if (d.second + 1 < board[0].size() && GetBlock(std::make_pair<float, float>(d.first * BLOCK_SIZE, (d.second + 1) * BLOCK_SIZE))->GetBlockType() == Types::BlockType::WALKABLE) {
            mapstar->at(d.first).at(d.second + 1) = mapstar->at(d.first).at(d.second) + 1;
            AStar(std::make_pair<int, int>(d.first + 0, d.second + 1), a, mapstar, count + 1);
        } else if (GetBlock(std::make_pair<float, float>(d.first * BLOCK_SIZE, (d.second + 1) * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
            mapstar->at(d.first).at(d.second + 1) = -1;
    }
    if (d.second - 1 > 0 && (mapstar->at(d.first).at(d.second - 1) == -2 || count < mapstar->at(d.first).at(d.second - 1))) {
        if (GetBlock(std::make_pair<float, float>(d.first * BLOCK_SIZE, (d.second - 1) * BLOCK_SIZE))->GetBlockType() == Types::BlockType::WALKABLE) {
            mapstar->at(d.first).at(d.second - 1) = mapstar->at(d.first).at(d.second) + 1;
            AStar(std::make_pair<int, int>(d.first + 0, d.second - 1), a, mapstar, count + 1);
        } else if (GetBlock(std::make_pair<float, float>(d.first * BLOCK_SIZE, (d.second - 1) * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
            mapstar->at(d.first).at(d.second - 1) = -1;
    }
}

std::pair<int, int> Board::FindPath(std::pair<int, int> init, std::pair<int, int> target, std::shared_ptr<Player> bot) {
    std::vector<std::vector<int>> mapStar(RESOLUTION_X / BLOCK_SIZE, std::vector<int>(RESOLUTION_Y / BLOCK_SIZE, -2));
    int next = 0;
    int xCell = 0;
    int yCell = 0;
    int closer = 0;
    
    mapStar[init.first][init.second] = 0;
    AStar(init, target, &mapStar, 1);
    if (bot->GetRun()) {
        xCell = bot->GetSpawn().first;
        yCell = bot->GetSpawn().second;
        next = mapStar[xCell][yCell];
    } else {
        for (auto pl : players) {
            if (pl->GetName() != bot->GetName() && pl->GetStatus() == Types::Status::ALIFE) {
                closer =  mapStar[pl->GetPositionRelative().first][pl->GetPositionRelative().second];
                if (next == 0)
                    next = closer;
                if (next >= closer) {
                    next = closer;
                    xCell = pl->GetPositionRelative().first;
                    yCell = pl->GetPositionRelative().second;
                }
            }
        }
    }
    while (next > 1) {
        if (xCell + 1 < mapStar.size() && mapStar[xCell + 1][yCell] < next && mapStar[xCell + 1][yCell] != -1) {
            xCell += 1;
        } else if (xCell - 1 > 0 && mapStar[xCell - 1][yCell] < next && mapStar[xCell - 1][yCell] != -1) {
            xCell -= 1;
        } else if (yCell + 1 < mapStar[0].size() && mapStar[xCell][yCell + 1] < next && mapStar[xCell][yCell + 1] != -1) {
            yCell += 1;
        } else if (yCell - 1 > 0 && mapStar[xCell][yCell - 1] < next && mapStar[xCell][yCell - 1] != -1) {
            yCell -= 1;
        } else
            next++;
        next--;
    }
    return (std::make_pair<int, int>(xCell - init.first, yCell - init.second));
}

void Board::BotAsset(std::shared_ptr<Player> bot, std::pair<int, int>vector) {
    if (vector.first != 0 || vector.second != 0) {
        bot->SetFrame(bot->GetFrame() > 2 ? 0 : bot->GetFrame() + 1);
    }
    if (vector.first < 0)
        bot->SetOrientation(Types::PlayerOrientation::LEFT);
    else if (vector.first > 0)
        bot->SetOrientation(Types::PlayerOrientation::RIGHT);
    else if (vector.second < 0)
        bot->SetOrientation(Types::PlayerOrientation::UP);
    else if (vector.second > 0)
        bot->SetOrientation(Types::PlayerOrientation::DOWN);
}

bool Board::IsBombInZone(std::pair<int, int> pos) {
    bool block;
    int dist = -1;

    for (auto bomb : bombs) {
        block = false;
        auto targ = bomb->GetPositionRelative();
        if (targ.first == pos.first) {
            int dep = targ.second > pos.second ? pos.second : targ.second;
            int end = targ.second < pos.second ? pos.second : targ.second;

            for (; dep < end && block != true; dep++)
                if (GetBlock(std::make_pair<float, float>(pos.first * BLOCK_SIZE, dep * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
                    block = true;
            dep = targ.second > pos.second ? pos.second : targ.second;
            if (!block && (dist > end - dep || dist == -1))
                dist = end - dep;
        }
        if (targ.second == pos.second) {
            int dep = targ.first > pos.first ? pos.first : targ.first;
            int end = targ.first < pos.first ? pos.first : targ.first;

            for (; dep < end && block != true; dep++)
                if (GetBlock(std::make_pair<float, float>( dep * BLOCK_SIZE, pos.second * BLOCK_SIZE))->GetBlockType() != Types::BlockType::WALKABLE)
                    block = true;
            dep = targ.first > pos.first ? pos.first : targ.first;
            if (!block && (dist > end - dep || dist == -1))
                dist = end - dep;
        }
        if (dist <= GetPlayerByName(bomb->GetOwner())->GetRadius() && dist != -1)
            return true;
    }
    return false;
}

void Board::IABot(std::shared_ptr<Player> bot) {
    int xCell;
    int yCell;
    int distance = 0;

    if (bot->GetStatus() != Types::Status::ALIFE)
        return;
    std::pair<float, float> vectorMove;
    auto nextPos = FindPath(bot->GetPositionRelative(), std::make_pair<int, int>(1, 1), bot);
    xCell = bot->GetSpeed() * PLAYER_SPEED;
    yCell = bot->GetSpeed() * PLAYER_SPEED;


    if (nextPos.first == 0) {
        if ((bot->GetPosition().first - (bot->GetPositionRelative().first * BLOCK_SIZE)) < 20)
            vectorMove = std::make_pair<float, float>(1 * xCell, 0);
        else if ((bot->GetPosition().first - (bot->GetPositionRelative().first * BLOCK_SIZE)) > 45)
            vectorMove = std::make_pair<float, float>(-1 * xCell, 0);
        else
            vectorMove = std::make_pair<float, float>(0, nextPos.second * yCell);
    } else {
        if ((bot->GetPosition().second - (bot->GetPositionRelative().second * BLOCK_SIZE)) < 20)
            vectorMove = std::make_pair<float, float>(0, 1 * yCell);
        else if ((bot->GetPosition().second - (bot->GetPositionRelative().second * BLOCK_SIZE)) > 45)
            vectorMove = std::make_pair<float, float>(0, -1 * yCell);
        else
            vectorMove = std::make_pair<float, float>(nextPos.first * xCell, 0);
    }
    
    if (Move(bot->GetName(), vectorMove))
        BotAsset(bot, vectorMove);
    distance = CheckPlayerPresence(bot->GetPositionRelative(), bot->GetName());
    if (distance != -1 && distance <= (bot->GetRadius() / 2))
        SetBomb(bot->GetName());
    if (!bot->GetRun())
        bot->SetRun(IsBombInZone(bot->GetPositionRelative()));
}