/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Gameinfo.cpp
*/

#include <thread>
#include "Gameinfo.hpp"
#include "Tools.hpp"
#include "Interface/IPlayer.hpp"

Gameinfo::Gameinfo()
{
    device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(RESOLUTION_X, RESOLUTION_Y));
;
	is_loadingGame = false;
    status = menu;
    is_loadingGame = false;
    initMenuWindow(L"Bomberman - Menu");
    game = std::make_unique<Game>(Game());

}

void Gameinfo::ResetAll() {
    game.reset();
    game = std::make_unique<Game>(Game());
}

int Gameinfo::startGame() {

    if (is_loadingGame == false)
        game->StartGame();
    else {
        game->StartGame(SaveName);
        is_loadingGame = false;
    }

    MyEventReceiver receiver;
    device->setWindowCaption(L"Bomberman - Game");
    device->setEventReceiver(&receiver);
    device->getCursorControl()->setVisible(false);
    driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
    driver->getMaterial2D().AntiAliasing=irr::video::EAAM_FULL_BASIC;

    while (device->run() && driver)
    {
        if (device->isWindowActive())
        {
                if (receiver.IsKeyDown(irr::KEY_ESCAPE)) {
                soundTest.SoundPlay(CLICK);
                if (game->GetStatus() == Types::Stage::GAME)
                    game->SetStatus(Types::Stage::PAUSE);
                else
                    game->SetStatus(Types::Stage::GAME);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            if (game->GetStatus() == Types::Stage::GAME) {
                if (tickSpeed.GetTimeLapsed() > 60) {
                    HandleMovement(receiver);
                    driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
                    tickSpeed.Restart();
                    DisplayBoard();
                    env->drawAll();
                    driver->endScene();
                }
                if (game->GetStatus() == Types::Stage::END) {
                    status = end;
                    EndGame();
                    break;
                }
                if (receiver.IsKeyDown(irr::KEY_SPACE)) {
                    status = menu;
                    game->SaveGame();
                    break;
                }
                driver->endScene();
            }
        }
    }
    device->getCursorControl()->setVisible(true);
	return 0;
}


void Gameinfo::EndGame() {
    auto players = Tools::ExtractList<Player, IDrawable>(game->GetEntities(Types::Entity::PLAYER));
    std::vector<int> index;
    int c;

    for (int a = 0; a < players.size(); a++)
        index.push_back(a);
    for (int a = 0; a < index.size() - 1;) {
        if (players[index[a]]->GetScore() < players[index[a + 1]]->GetScore()) {
            c = index[a];
            index[a] = index[a + 1];
            index[a + 1] = c;
            a = 0;
        } else
            a++;
    }

    device->setWindowCaption(L"Bomberman - Game - End Game");
    device->getCursorControl()->setVisible(true);

    irr::video::ITexture *green = driver->getTexture("assets/LargeGreenButton.png");
    irr::video::ITexture *blue = driver->getTexture("assets/LargeBlueButton.png");
    irr::gui::IGUIButton *newGameButton= env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 2), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_NEW_GAME_BUTTON, L"New Game", L"Start New Game");
    irr::gui::IGUIButton *menu_button = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 4), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 5), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_MENU_BUTTON, L"Menu", L"Return To Menu");
    irr::gui::IGUIButton *quitButton = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 7), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 8), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    irr::gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();

    menu_button->setImage(green);
    newGameButton->setImage(green);
    quitButton->setImage(green);
    menu_button->setPressedImage(blue);
    newGameButton->setPressedImage(blue);
    quitButton->setPressedImage(blue);

    this->soundTest.MusicPlay(SCORE);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.status = status;
    MyMenuEventReceiver receiver(context);
    device->setEventReceiver(&receiver);
    while (device->run() && context.status == end)
    {
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        for (int a = 0; a < index.size(); a++) {
            font->draw(irr::core::stringw(a + 1).c_str(), irr::core::rect<irr::s32>(((RESOLUTION_X / (index.size() + 1)) * (a + 1)), 380, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index[a]]->GetName().c_str()).c_str(), irr::core::rect<irr::s32>(((RESOLUTION_X / (index.size() + 1)) * (a + 1)) - 10, 400, 300, 90), irr::video::SColor(255, 0, 0, 255));
            DisplayPlayer(players[index[a]]->GetPlayerModel(), std::make_pair<float, float>(((RESOLUTION_X / (index.size() + 1)) * (a + 1)) - 60, 500), 0, Types::PlayerOrientation::DOWN);
            font->draw(L"Score :", irr::core::rect<irr::s32>(((RESOLUTION_X / (index.size() + 1)) * (a + 1)) - 15, 420, 300, 90), irr::video::SColor(255, 0, 255, 0));
            font->draw(irr::core::stringw(players[index[a]]->GetScore()).c_str(), irr::core::rect<irr::s32>(((RESOLUTION_X / (index.size() + 1)) * (a + 1)) + 15, 420, 300, 90), irr::video::SColor(255, 0, 255, 0));

        }
        env->drawAll();
        driver->endScene();
    }
    this->soundTest.MusicStop();
    status = context.status;
}


int Gameinfo::GetStatus() { return status; }
void Gameinfo::SetStatus(int _status) { status = _status; }
void Gameinfo::Drop() { device->drop(); }