/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** StartMenu
*/

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <locale>
#include <codecvt>
#include "Gameinfo.hpp"
#include "EventReceiver.hpp"
#include "Config.hpp"
#include "MyException.hpp"

irr::gui::IGUIListBox *filledSaveGame(irr::gui::IGUIListBox *savegame)
{
    std::vector<const wchar_t *> listName;

	for (auto entry : fs::directory_iterator("save")) {
		const size_t length = entry.path().string().size() + 1;
		wchar_t* text_wchar = new wchar_t[length];
		mbstowcs(text_wchar, entry.path().string().c_str(), length);
		if (entry.path().string() != "save/.init" && entry.path().string() != "save\\.init") {
        	listName.push_back(text_wchar);
        }
	}
    
	for (auto list : listName)
		savegame->addItem(list);
    return savegame;
}

void Gameinfo::initMenuWindow(const wchar_t *windowName)
{
    if (!device)
		throw MyException("Fail Create Device");
    device->setWindowCaption(windowName);
    device->setResizable(false);
    driver = device->getVideoDriver();
    env = device->getGUIEnvironment();
    titleScreen = driver->getTexture("assets/menuScreen.png");
};

void Gameinfo::startLoadGame()
{
    device->setWindowCaption(L"Bomberman - Menu - Load Game");
    irr::video::ITexture *green = driver->getTexture("assets/LargeGreenButton.png");
    irr::video::ITexture *blue = driver->getTexture("assets/LargeBlueButton.png");
    irr::gui::IGUIButton *back = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 7), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 8), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_MENU_BUTTON, L"Back", L"Return to the Menu");
    irr::gui::IGUIButton *play = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 2), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_START_BUTTON, L"Play", L"Launch the Game");
    irr::gui::IGUIListBox *SvgGame = env->addListBox(irr::core::rect<irr::s32>((RESOLUTION_X / 3), (RESOLUTION_Y / 3 * 2), (RESOLUTION_X / 3 * 2), (RESOLUTION_Y / 3 * 3) - 60));
    back->setImage(green);
    play->setImage(green);
    play->setPressedImage(blue);
    back->setPressedImage(blue);
    SvgGame = filledSaveGame(SvgGame);
    irr::s32 selected;
    std::wstring WsaveName;
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.status = status;
    MyMenuEventReceiver receiver(context);
    device->setEventReceiver(&receiver);
    while (device->run() && driver)
    {
        if (device->isWindowActive())
        {
            driver->draw2DImage(titleScreen, irr::core::position2d<irr::s32>(0, 0),
                                irr::core::rect<irr::s32>(0, 0, 1000, 700));
            env->drawAll();
            if (context.status != loadGame)
                break;
            if ((selected = SvgGame->getSelected()) != -1) {
                WsaveName = SvgGame->getListItem(selected);
                using convert_type = std::codecvt_utf8<wchar_t>;
                std::wstring_convert<convert_type, wchar_t> convert;
                SaveName = convert.to_bytes(WsaveName);
                context.svgName = SaveName;
                is_loadingGame = true;
            }
            driver->endScene();
        }
    }
    status = context.status;
}

void Gameinfo::startNewGame()
{
    device->setWindowCaption(L"Bomberman - Menu - New Game");

    irr::video::ITexture *green = driver->getTexture("assets/LargeGreenButton.png");
    irr::video::ITexture *blue = driver->getTexture("assets/LargeBlueButton.png");
    irr::gui::IGUIButton *menu_button = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 7), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 8), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_MENU_BUTTON, L"Back", L"Return to the Menu");
    irr::gui::IGUIButton *button_add_player = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 4), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 5), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_ADD_PLAYER_BUTTON, L"Add Player", L"Add a Player");
    irr::gui::IGUIButton *button_play= env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3), (RESOLUTION_Y / 3 / 3 * 8), (RESOLUTION_X / 3 / 3 * 2), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_START_BUTTON, L"Play", L"Launch the Game");
    menu_button->setImage(green);
    button_add_player->setImage(green);
    button_play->setImage(green);
    menu_button->setPressedImage(blue);
    button_add_player->setPressedImage(blue);
    button_play->setPressedImage(blue);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.status = status;
    context.newName =false;
    MyMenuEventReceiver receiver(context);
    device->setEventReceiver(&receiver);
    while (device->run() && driver)
    {
        if (device->isWindowActive())
        {
            driver->draw2DImage(titleScreen, irr::core::position2d<irr::s32>(0, 0),
                                irr::core::rect<irr::s32>(0, 0,RESOLUTION_X, RESOLUTION_Y));
            env->drawAll();
            if (context.status == 3) {
                    for (int a = 0; a < context.Text.size(); a++)
                        game->AddPlayer(context.Text[a].c_str(), context.Bots[a]);
                    break;
            } else if (context.status != newGame)
                break;
            driver->endScene();
        }
    }
    status = context.status;
}

void Gameinfo::startMenu()
{
    irr::video::ITexture *green = driver->getTexture("assets/LargeGreenButton.png");
    irr::video::ITexture *blue = driver->getTexture("assets/LargeBlueButton.png");
    irr::gui::IGUIButton *button_quit = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 7), (RESOLUTION_Y / 3 / 3 * 8),
        (RESOLUTION_X / 3 / 3 * 8), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"Exit the Program");
    irr::gui::IGUIButton *button_loadGame = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3 * 4), (RESOLUTION_Y / 3 / 3 * 8),
    (RESOLUTION_X / 3 / 3 * 5), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_LOAD_GAME_BUTTON, L"Load Game", L"Load a Game");
    irr::gui::IGUIButton *button_newGame = env->addButton(irr::core::rect<irr::s32>((RESOLUTION_X / 3 / 3), (RESOLUTION_Y / 3 / 3 * 8),
    (RESOLUTION_X / 3 / 3 * 2), (RESOLUTION_Y / 3 / 3 * 9) - 60), 0, GUI_ID_NEW_GAME_BUTTON, L"New Game", L"Create a New Game");
    button_quit->setImage(green);
    button_loadGame->setImage(green);
    button_newGame->setImage(green);
    button_quit->setPressedImage(blue);
    button_loadGame->setPressedImage(blue);
    button_newGame->setPressedImage(blue);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.status = status;
    MyMenuEventReceiver receiver(context);
    device->setEventReceiver(&receiver);
    while (device->run() && driver)
    {
        if (device->isWindowActive())
        {
            driver->draw2DImage(titleScreen, irr::core::position2d<irr::s32>(0, 0),
                                irr::core::rect<irr::s32>(0, 0, RESOLUTION_X, RESOLUTION_Y));
            env->drawAll();
            if (context.status != menu)
                break;
            driver->endScene();
        }
    }
    status = context.status;
}