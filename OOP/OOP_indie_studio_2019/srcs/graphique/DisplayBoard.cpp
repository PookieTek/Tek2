/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** DisplayBoard
*/

#include <algorithm>
#include "Gameinfo.hpp"
#include "Tools.hpp"


void Gameinfo::DisplayBonus(Types::BonusType type, int x, int y) {
    if (type == Types::BonusType::LIFE)
        driver->draw2DImage(driver->getTexture("assets/1upbonus.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
    else if (type == Types::BonusType::WALKTHROUGH)
        driver->draw2DImage(driver->getTexture("assets/walkbonus.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
    else if (type == Types::BonusType::RADIUS)
        driver->draw2DImage(driver->getTexture("assets/radiusbonus.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
    else if (type == Types::BonusType::BOMBBONUS)
        driver->draw2DImage(driver->getTexture("assets/bombbonus.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
    else if (type == Types::BonusType::SPEED)
        driver->draw2DImage(driver->getTexture("assets/speedbonus.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
}

void Gameinfo::DisplayBomb(Types::BombStatus status, int x, int y) {
    switch (status) {
        case Types::BombStatus::FULL: driver->draw2DImage(driver->getTexture("assets/bombs.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 128, 130), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::BombStatus::HALF: driver->draw2DImage(driver->getTexture("assets/bombs.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 136, 128, 266), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::BombStatus::IMMINENT: driver->draw2DImage(driver->getTexture("assets/bombs.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 272, 128, 392), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::BombStatus::EXPLODE:driver->draw2DImage(driver->getTexture("assets/bombs.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 391, 128, 511), 0, irr::video::SColor(255, 255, 255, 255), true);
            soundTest.SoundPlay(EXPLOSION);
            break;
        default: break;
    }
}

void Gameinfo::DisplayPlayer(Types::PlayerModel model, std::pair<float, float> position, int frame, Types::PlayerOrientation orientation) {
    switch (model) {
        case Types::PlayerModel::MODEL1: driver->draw2DImage(driver->getTexture("assets/player_blue.png"), irr::core::position2d<irr::s32>(position.first - 36, position.second - 96), irr::core::rect<irr::s32>(192 * frame, static_cast<int>(orientation) * 192, (192 * frame) + 192, (static_cast<int>(orientation) * 192) + 192), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::PlayerModel::MODEL2: driver->draw2DImage(driver->getTexture("assets/player_dark.png"), irr::core::position2d<irr::s32>(position.first - 36, position.second - 96), irr::core::rect<irr::s32>(192 * frame, static_cast<int>(orientation) * 192, (192 * frame) + 192, (static_cast<int>(orientation) * 192) + 192), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::PlayerModel::MODEL3: driver->draw2DImage(driver->getTexture("assets/player_red.png"), irr::core::position2d<irr::s32>(position.first - 36, position.second - 96), irr::core::rect<irr::s32>(192 * frame, static_cast<int>(orientation) * 192, (192 * frame) + 192, (static_cast<int>(orientation) * 192) + 192), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        case Types::PlayerModel::MODEL4: driver->draw2DImage(driver->getTexture("assets/player_zombie.png"), irr::core::position2d<irr::s32>(position.first - 36, position.second - 96), irr::core::rect<irr::s32>(192 * frame, static_cast<int>(orientation) * 192, (192 * frame) + 192, (static_cast<int>(orientation) * 192) + 192), 0, irr::video::SColor(255, 255, 255, 255), true);
            break;
        default: break;
    }
}

void Gameinfo::DisplayHud() {
    auto players = Tools::ExtractList<Player, IDrawable>(game->GetEntities(Types::Entity::PLAYER));
    int index1 = 0;
    int index2 = 0;
    
    for (; index1 < players.size() && players[index1]->IsBot(); index1++);
    for (index2 = index1 + 1; index2 < players.size() && players[index2]->IsBot(); index2++);
    if (index1 == players.size())
       return;
    irr::gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
    int timeleft = game->GetTimeLeft() / 1000;
    font->draw(irr::core::stringw(timeleft / 60).c_str(), irr::core::rect<irr::s32>(950, 10, 1000, 50), irr::video::SColor(255, 255, 0, 255));
    font->draw(L" : ", irr::core::rect<irr::s32>(960, 10, 1000, 50), irr::video::SColor(255, 255, 0, 255));
    font->draw(irr::core::stringw(timeleft % 60).c_str(), irr::core::rect<irr::s32>(970, 10, 1000, 50), irr::video::SColor(255, 255, 0, 255));

    

    if (index1 != players.size() && !players[index1]->IsBot()) {
        if (font) {
            font->draw(irr::core::stringw(players[index1]->GetName().c_str()).c_str(), irr::core::rect<irr::s32>(40, 30, 300, 90), irr::video::SColor(255, 0, 0, 255));
            font->draw(L"Score", irr::core::rect<irr::s32>(130, 10, 300, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Life", irr::core::rect<irr::s32>(160, 10, 300, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Bombs", irr::core::rect<irr::s32>(190, 10, 300, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Radius", irr::core::rect<irr::s32>(220, 10, 300, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Speed", irr::core::rect<irr::s32>(250, 10, 300, 50), irr::video::SColor(255, 255, 0, 0));

            font->draw(irr::core::stringw(players[index1]->GetScore()).c_str(), irr::core::rect<irr::s32>(130, 30, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index1]->GetLife()).c_str(), irr::core::rect<irr::s32>(160, 30, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index1]->GetBomb()).c_str(), irr::core::rect<irr::s32>(190, 30, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index1]->GetRadius()).c_str(), irr::core::rect<irr::s32>(220, 30, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index1]->GetSpeed()).c_str(), irr::core::rect<irr::s32>(250, 30, 300, 90), irr::video::SColor(255, 0, 255, 0));
        }
    }
    if (index2 != players.size() && !players[index2]->IsBot() && index2 != index1) {
        if (font) {
            font->draw(irr::core::stringw(players[index2]->GetName().c_str()).c_str(), irr::core::rect<irr::s32>(1570, 30, 1830, 90), irr::video::SColor(255, 0, 0, 255));
            font->draw(L"Score", irr::core::rect<irr::s32>(1660, 10, 1830, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Life", irr::core::rect<irr::s32>(1690, 10, 1830, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Bombs", irr::core::rect<irr::s32>(1720, 10, 1830, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Radius", irr::core::rect<irr::s32>(1750, 10, 1830, 50), irr::video::SColor(255, 255, 0, 0));
            font->draw(L"Speed", irr::core::rect<irr::s32>(1780, 10, 1830, 50), irr::video::SColor(255, 255, 0, 0));

            font->draw(irr::core::stringw(players[index2]->GetScore()).c_str(), irr::core::rect<irr::s32>(1660, 30, 1830, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index2]->GetLife()).c_str(), irr::core::rect<irr::s32>(1690, 30, 1830, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index2]->GetBomb()).c_str(), irr::core::rect<irr::s32>(1720, 30, 1830, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index2]->GetRadius()).c_str(), irr::core::rect<irr::s32>(1750, 30, 1830, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index2]->GetSpeed()).c_str(), irr::core::rect<irr::s32>(1780, 30, 1830, 90), irr::video::SColor(255, 0, 255, 0));
        }
    }
}

void Gameinfo::DisplayBoard() {
    int y = 0;
    int x = 0;
    auto board = game->GetBoard()->GetBoard();
    auto bonus = Tools::ExtractList<Bonus, IDrawable>(game->GetEntities(Types::Entity::BONUS));
    auto bombs = Tools::ExtractList<Bomb, IDrawable>(game->GetEntities(Types::Entity::BOMB));
    auto players = Tools::ExtractList<Player, IDrawable>(game->GetEntities(Types::Entity::PLAYER));
    for (auto pl : players)
        if (pl->IsBot())
            game->GetBoard()->IABot(pl);
    
    driver->draw2DImage(driver->getTexture("assets/grass.png"), irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(0, 0, 1920, 1080));
    for (int indexx = 0; indexx < board[0].size(); indexx++) {
        for (int indexy = 0; indexy < board.size(); indexy++) {
            if (board[indexy][indexx]->GetBlockType() == 1)
                driver->draw2DImage(driver->getTexture("assets/box.png"), irr::core::position2d<irr::s32>(x, y - 61), irr::core::rect<irr::s32>(0, 0, 155, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
            else if (board[indexy][indexx]->GetBlockType() == 2)
                driver->draw2DImage(driver->getTexture("assets/frontWall.png"), irr::core::position2d<irr::s32>(x, y - 61), irr::core::rect<irr::s32>(0, 0, 189, 189), 0, irr::video::SColor(255, 255, 255, 255), true);
           std::for_each(bonus.begin(), bonus.end(), [&](std::shared_ptr<Bonus> bon) {
                if (bon->GetPositionRelative() == std::make_pair<int, int>(x / BLOCK_SIZE, y / BLOCK_SIZE))
                    DisplayBonus(bon->GetBonusType(), x, y);
            });
            std::for_each(bombs.begin(), bombs.end(), [&](std::shared_ptr<Bomb> bomb) {
                if (bomb->GetPositionRelative() == std::make_pair<int, int>(x / BLOCK_SIZE, y / BLOCK_SIZE))
                    DisplayBomb(bomb->GetStatus(), x, y);
            });
            if (board[indexy][indexx]->GetFireStatus() > -1)
                driver->draw2DImage(driver->getTexture("assets/fire.png"), irr::core::position2d<irr::s32>(x, y), irr::core::rect<irr::s32>(0, 0, 128, 128), 0, irr::video::SColor(255, 255, 255, 255), true);
            x += BLOCK_SIZE;
        }
        x = 0;
        for (int indexy = 0; indexy < board.size(); indexy++) {
            std::for_each(players.begin(), players.end(), [&](std::shared_ptr<Player> player) {
                if (player->GetPositionRelative() == std::make_pair<int, int>(x / BLOCK_SIZE, y / BLOCK_SIZE) && player->GetStatus() != Types::Status::DIE && player->GetStatus() != Types::Status::LOOSE && player->GetLife() > 0)
                    DisplayPlayer(player->GetPlayerModel(), player->GetPosition(), player->GetFrame(), player->GetOrientation());
            });
            x += BLOCK_SIZE;
        }
        x = 0;
        y += BLOCK_SIZE;
    }
    DisplayHud();
}