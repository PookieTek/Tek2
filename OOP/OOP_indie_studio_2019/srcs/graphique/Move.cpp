/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Move
*/

#include "Gameinfo.hpp"
#include "Tools.hpp"

void Gameinfo::HandleMovement(MyEventReceiver receiver)
{
    std::pair<float, float> vectorMove1;
    std::pair<float, float> vectorMove2;
    int playable = 0;
    auto players = Tools::ExtractList<Player, IDrawable>(game->GetEntities(Types::Entity::PLAYER));
    int index1 = 0;
    int index2 = 0;

    for (; index1 < players.size() && players[index1]->IsBot(); index1++);
    for (index2 = index1 + 1; index2 < players.size() && players[index2]->IsBot(); index2++);

    if (index1 < players.size() && !players[index1]->IsBot() && players[index1]->GetStatus() == Types::Status::ALIFE && players[index1]->GetLife() > 0) {
        players[index1]->SetFrame(players[index1]->GetFrame() > 2 ? 0 : players[index1]->GetFrame() + 1);
        if (receiver.IsKeyDown(UP_PLAYER_1)) {
            vectorMove1 = std::make_pair<float, float>(0, -1 * players[index1]->GetSpeed() * PLAYER_SPEED);
            players[index1]->SetOrientation(Types::PlayerOrientation::UP);
        } else if (receiver.IsKeyDown(DOWN_PLAYER_1)) {
            vectorMove1 = std::make_pair<float, float>(0, players[index1]->GetSpeed() * PLAYER_SPEED);
            players[index1]->SetOrientation(Types::PlayerOrientation::DOWN);
        } else if (receiver.IsKeyDown(RIGHT_PLAYER_1)) {
            vectorMove1 = std::make_pair<float, float>(players[index1]->GetSpeed() * PLAYER_SPEED, 0);
            players[index1]->SetOrientation(Types::PlayerOrientation::RIGHT);
        } else if (receiver.IsKeyDown(LEFT_PLAYER_1)) {
            vectorMove1 = std::make_pair<float, float>(-1 * players[index1]->GetSpeed() * PLAYER_SPEED, 0);
            players[index1]->SetOrientation(Types::PlayerOrientation::LEFT);
        } else
            players[index1]->SetFrame(0);
        if (receiver.IsKeyDown(THROW_BOMB_1)) {
            if (game->GetBoard()->SetBomb(players[index1]->GetName()))
                soundTest.SoundPlay(BOMB_POSE);
        }
    }
    if (index2 != index1 && index2 < players.size() && !players[index2]->IsBot() && players[index2]->GetStatus() == Types::Status::ALIFE && players[index2]->GetLife() > 0) {
        players[index2]->SetFrame(players[index2]->GetFrame() > 2 ? 0 : players[index2]->GetFrame() + 1);
        if (receiver.IsKeyDown(UP_PLAYER_2)) {
            vectorMove2 = std::make_pair<float, float>(0, -1 * players[index2]->GetSpeed() * PLAYER_SPEED);
            players[index2]->SetOrientation(Types::PlayerOrientation::UP);
        } else if (receiver.IsKeyDown(DOWN_PLAYER_2)) {
            vectorMove2 = std::make_pair<float, float>(0, players[index2]->GetSpeed() * PLAYER_SPEED);
            players[index2]->SetOrientation(Types::PlayerOrientation::DOWN);
        } else if (receiver.IsKeyDown(RIGHT_PLAYER_2)) {
            vectorMove2 = std::make_pair<float, float>(players[index2]->GetSpeed() * PLAYER_SPEED, 0);
            players[index2]->SetOrientation(Types::PlayerOrientation::RIGHT);
        } else if (receiver.IsKeyDown(LEFT_PLAYER_2)) {
            vectorMove2 = std::make_pair<float, float>(-1 * players[index2]->GetSpeed() * PLAYER_SPEED, 0);
            players[index2]->SetOrientation(Types::PlayerOrientation::LEFT);
        } else
            players[index2]->SetFrame(0);
        if (receiver.IsKeyDown(THROW_BOMB_2)) {
            if (game->GetBoard()->SetBomb(players[index2]->GetName()))
                soundTest.SoundPlay(BOMB_POSE);
        }
    }
    if (!receiver.IsAnyPressed())
        return;
    if (index1 < players.size())
        game->GetBoard()->Move(players[index1]->GetName(), vectorMove1);
    if (index2 < players.size())
        game->GetBoard()->Move(players[index2]->GetName(), vectorMove2);

}

