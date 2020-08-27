/*
** EPITECH PROJECT, 2020
** srcs
** File description:
** EventReceiver
*/

#include <fstream>
#include <thread>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "EventReceiver.hpp"
#include "include/IrrlichtDevice.h"
#include "Gameinfo.hpp"
#include "EditBox.hpp"

#include "SoundTest.hpp"

MyEventReceiver::MyEventReceiver()
{
    for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
        KeyIsDown[i] = false;
    anyPressed = false;
}

MyEventReceiver::~MyEventReceiver()
{
}

bool MyEventReceiver::IsAnyPressed() { return anyPressed; }

bool MyEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        anyPressed = true;
    }
    return false;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool MyMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 select;
        irr::s32 id = event.GUIEvent.Caller->getID();
        irr::gui::IGUIEnvironment *env = Context.device->getGUIEnvironment();
        irr::gui::IGUIElement *root = env->getRootGUIElement();
        int index = 0;
        bool boxbot = false;

        switch (event.GUIEvent.EventType)
        {
        case irr::gui::EGET_BUTTON_CLICKED :
            if (id == GUI_ID_QUIT_BUTTON) {
                Context.status = quit;
                Context.device->closeDevice();
                return true;
            }
            if (id == GUI_ID_NEW_GAME_BUTTON) {
                soundTest.SoundPlay(CLICK);
                env->clear();
                Context.status = newGame;
            }
            if (id == GUI_ID_ADD_PLAYER_BUTTON) {
                if (box.getNbEditBoxPlayer() < 4) {
                    if (box.getNbEditBoxPlayer() >= 2)
                        boxbot = true;
                    irr::core::stringc name ("Name");
                    name.append(box.getNbEditBoxPlayer() + 48);
                    Context.Text.push_back(name);
                    Context.Bots.push_back(boxbot);

                    env->addEditBox(L"Name", irr::core::rect<irr::s32>(box.getX(), box.getY(), box.getX2(), box.getY2()), true, 0, GUI_ID_EDIT_BOX_1 + box.getNbEditBoxPlayer());
                    env->addCheckBox(boxbot, irr::core::rect<irr::s32>(box.getX(), box.getY() + 30, box.getX2(), box.getY2() + 30), 0, GUI_ID_CHECK_BOX_1 + box.getNbEditBoxPlayer());
                }
                box.addNbEditBoxPlayer();
                box.setX(450);
                box.setX2(450);
            }
            if (id == GUI_ID_LOAD_GAME_BUTTON) {
                env->clear();
                Context.status = loadGame;
            }
            if (id == GUI_ID_MENU_BUTTON) {
                env->clear();
                Context.status = menu;
                box.resetEditBoxPlayer();
            }
            if (id == GUI_ID_START_BUTTON) {
                if ((Context.status == newGame && Context.Text.size() > 1) || (Context.status == loadGame && Context.svgName.size() > 0)) {
                    env->clear();
                    Context.status = game;
                }
            }
            return true;
        case irr::gui::EGET_EDITBOX_CHANGED:
            for (irr::s32 i = GUI_ID_EDIT_BOX_1; i <= GUI_ID_EDIT_BOX_4; i++, index++) {
                if (id == i) {
                    Context.Text[index] = root->getElementFromId(i, true)->getText();
                    if (std::count(Context.Text.begin(), Context.Text.end(), Context.Text[index]) > 1) {
                        Context.Text[index].append("_");
                    }
                }
            }
            return true;
        case irr::gui::EGET_CHECKBOX_CHANGED:
            if (id == GUI_ID_CHECK_BOX_1)
                Context.Bots[0] = static_cast<irr::gui::IGUICheckBox *>(root->getElementFromId(GUI_ID_CHECK_BOX_1, true))->isChecked();
            if (id == GUI_ID_CHECK_BOX_2)
                Context.Bots[1] = static_cast<irr::gui::IGUICheckBox *>(root->getElementFromId(GUI_ID_CHECK_BOX_2, true))->isChecked();
        default:
            return false;
        }
    }
    return false;
}