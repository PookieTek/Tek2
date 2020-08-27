/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Bonus.hpp"
#include "Bomb.hpp"
#include "Tools.hpp"
#include "MyException.hpp"
#include <fstream>
#include <chrono>
#include <ctime>
#include <exception>
#include <sstream>

Game::Game() {
    duration = GAME_TIME;
    stage = Types::Stage::MENU;
    CheckConfig();
}

Game::~Game() {}

std::shared_ptr<IBoard> Game::GetBoard() {
    GameOver();
    return board;
}

std::vector<std::shared_ptr<IPlayer>> Game::GetPlayers() {
    return (Tools::ExtractList<IPlayer, Player>(players));
}

Types::Stage Game::GetStatus() { return stage; }

void Game::LoadPlayer(std::string file) {
    std::ifstream save(file, std::ios::in);
    std::string line;
    int counter = 0;

    if (!save.is_open())
        throw MyException("No Save Found");
    while (std::getline(save, line)) {
        if (line == "ENDPLAYER") {
            std::cout << "end player";
            return;
        }
        std::stringstream ss(line);
        std::string sub;
        int subcount = 0;

        while (ss.good()) {
            std::getline(ss, sub, ';');
            if (subcount == 0) AddPlayer(sub);
            if (subcount == 1) players[players.size() - 1]->SetBomb(std::stoi(sub));
            if (subcount == 2) players[players.size() - 1]->SetRadius(std::stoi(sub));
            if (subcount == 3) players[players.size() - 1]->SetSpeed(std::stoi(sub));
            if (subcount == 4) players[players.size() - 1]->SetLife(std::stoi(sub));
            if (subcount == 5) players[players.size() - 1]->SetWalk(std::stoi(sub));
            if (subcount == 6) players[players.size() - 1]->SetBot(std::stoi(sub));
            if (subcount == 7) {
                std::stringstream subpos(sub);
                float xPos = (std::getline(subpos, sub, ':') ? std::stoi(sub) : (players[players.size() - 1]->GetSpawn().first * BLOCK_SIZE));
                float yPos = (std::getline(subpos, sub, ':') ? std::stoi(sub) : (players[players.size() - 1]->GetSpawn().second * BLOCK_SIZE));
                players[players.size() - 1]->SetPosition(std::make_pair<float, float>(xPos + 0, yPos + 0));
            }
            if (subcount == 8) players[players.size() - 1]->AddScore(std::stoi(sub));
            subcount++;
        }
    }
}

void Game::LoadGame(std::string file) {
    std::ifstream save(file, std::ios::in);
    std::string line;
    int counter = -1;

    if (!save.is_open())
        throw MyException("No Save Found");
    while (std::getline(save, line) && line != "ENDBOARD") {
        if (counter > -1 && counter < RESOLUTION_X / BLOCK_SIZE) {
            for (int i = 0; i < line.size(); i++) {
                static_cast<Block *>(board->GetBoard()[counter][i].get())->SetBlockType(static_cast<Types::BlockType>(line[i] - 48));
            }
            counter++;
        }
        if (line == "ENDPLAYER")
            counter = 0;
    }
}

void Game::SaveGame() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(40,'\0');
    std::strftime(&s[0], s.size(), "save/%H-%M-%S_%d-%m-%Y.dat", std::localtime(&now));
    std::ofstream save(s, std::ios::out | std::ios::binary);
   
    for (auto player : players) {
        save << player->GetName() << ";";
        save << player->GetBomb() << ";";
        save << player->GetRadius() << ";";
        save << player->GetSpeed() << ";";
        save << player->GetLife() << ";";
        save << (player->IsWalkThrough() ? 1 : 0) << ";";
        save << (player->IsBot() ? 1 : 0) << ";";
        save << player->GetPosition().first << ":" << player->GetPosition().second << ";";
        save << player->GetScore() << "\n";
    }
    save << "ENDPLAYER\n";
    for (int i = 0; i < GetBoard()->GetBoard().size(); i++) {
        for (int j = 0; j < GetBoard()->GetBoard().at(i).size(); j++)
            save << GetBoard()->GetBoard()[i][j]->GetBlockType();
        save << "\n";
    }
    save << "ENDBOARD\n";
    save.close();
}

void Game::SetStatus(Types::Stage status) {
    if (status == Types::Stage::PAUSE) {
        auto bombs = Tools::ExtractList<Bomb, IDrawable>(GetEntities(Types::Entity::BOMB));
        for (auto b : bombs)
            b->Pause();
        timer.Pause();
    }
    else if (status == Types::Stage::GAME && stage == Types::Stage::PAUSE) {
        auto bombs = Tools::ExtractList<Bomb, IDrawable>(GetEntities(Types::Entity::BOMB));
        for (auto b : bombs)
            b->Resume();
        timer.Resume();
    } else if (status == Types::Stage::GAME)
        timer.Restart();
    else if (status == Types::Stage::QUIT)
        SaveGame();
    stage = status;
}

void Game::GameOver() {
    int stillAlive = players.size();

    for (int a = 0; a < players.size(); a++) {
        if (players[a]->GetLife() == 0)
            players[a]->SetStatus(Types::Status::LOOSE);
        if (players.at(a)->GetStatus() == Types::Status::LOOSE)
            stillAlive --;
    }
    if (stillAlive < 2) {
        stage = Types::Stage::END;
        for (int a = 0; a < players.size(); a++) {
            if (players.at(a)->GetStatus() != Types::Status::LOOSE)
                players.at(a)->SetStatus(Types::Status::WIN);
        }
    } else if ((duration - timer.GetTimeLapsed()) <= 0)
        stage = Types::Stage::END;
}

int Game::GetTimeLeft() { 
    return (duration - timer.GetTimeLapsed());
 }

void Game::AddPlayer(std::string _name) {
    players.push_back(std::make_shared<Player>(_name, players.size()));
}

void Game::AddPlayer(std::string _name, bool _IsBot) {
    players.push_back(std::make_shared<Player>(_name, _IsBot, players.size()));
}

void Game::DelPlayer(std::string _name) {
    int index = 0;

    for (; index < players.size() && players.at(index)->GetName() != _name; index++);
    if (index != players.size())
        players.erase(players.begin() + index);
}

bool Game::StartGame() {
    board = std::make_shared<Board>(players);
    SetStatus(Types::Stage::GAME);
    return true;
}

bool Game::StartGame(std::string _filename) {
    LoadPlayer(_filename);
    board = std::make_shared<Board>(players);
    LoadGame(_filename);
    std::remove(_filename.c_str());
    SetStatus(Types::Stage::GAME);
    return true;
}

std::vector<std::shared_ptr<IDrawable>> Game::GetEntities() {
    std::vector<std::shared_ptr<IDrawable>> list;

    for (auto p : players)
        list.push_back(p);
    for (auto cols : board->GetBoard())
        for (auto cell : cols)
            list.push_back(cell);
    for (auto bon : board->GetBonus())
        list.push_back(bon);
    for (auto b : board->GetBombs())
        list.push_back(b);
    return list;
}

std::vector<std::shared_ptr<IDrawable>> Game::GetEntities(Types::Entity entity) {
    std::vector<std::shared_ptr<IDrawable>> listtmp = GetEntities();
    std::vector<std::shared_ptr<IDrawable>> list;

    for (int i = 0; i < listtmp.size(); i++)
        if (listtmp.at(i)->GetType() == entity)
            list.push_back(listtmp.at(i));
    return list;
}

std::shared_ptr<IPlayer> Game::GetPlayerByName(std::string _name) {
    for (int i = 0; i < players.size(); i++)
        if (players.at(i)->GetName() == _name)
            return players.at(i);
    return nullptr;
}

void Game::CheckConfig() {
    if (BLOCK_SIZE <= 0)
        throw MyException("Error:\tBad Value For Block Size In Config.hpp");
    if (EXPLODE_TIME <= 0)
        throw MyException("Error:\tBad Value For Explode Time In Config.hpp");
    if (RESOLUTION_X <= 0)
        throw MyException("Error:\tBad Value For Resolution X In Config.hpp");
    if (RESOLUTION_Y <= 0)
        throw MyException("Error:\tBad Value For Resolution Y In Config.hpp");
    if (INIT_SPEED <= 0)
        throw MyException("Error:\tBad Value For Init Speed In Config.hpp");
    if (INIT_BOMBS <= 0)
        throw MyException("Error:\tBad Value For Init Bombs In Config.hpp");
    if (INIT_LIFE <= 0)
        throw MyException("Error:\tBad Value For Init Life In Config.hpp");
    if (INIT_RADIUS <= 0)
        throw MyException("Error:\tBad Value For Init Radius In Config.hpp");
    if (GAME_TIME < 1000)
        throw MyException("Error:\tBad Value For Game Time In Config.hpp");
    if (CINETIC_TRANSMISSION < 10)
        throw MyException("Error:\tBad Value For Cinetic Transmission In Config.hpp");
    if (RESPAWN_TIMER < 0)
        throw MyException("Error:\tBad Value For Respawn Timer In Config.hpp");
    if (CHANCE_BONUS < 0)
        throw MyException("Error:\tBad Value For Chance Bonus In Config.hpp");

}