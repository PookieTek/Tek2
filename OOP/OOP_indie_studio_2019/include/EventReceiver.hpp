/*
** EPITECH PROJECT, 2020
** srcs
** File description:
** EventReceiver
*/

#include <include/irrlicht.h>

#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

#include <vector>
#include "EditBox.hpp"
#include "Sound.hpp"
#include "SoundTest.hpp"

enum {
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_START_BUTTON,
    GUI_ID_NEW_GAME_BUTTON,
    GUI_ID_LOAD_GAME_BUTTON,
    GUI_ID_MENU_BUTTON,
    GUI_ID_ADD_PLAYER_BUTTON,
    GUI_ID_ADD_BOT_BUTTON,
    GUI_ID_LISTBOX_SVG,
    GUI_ID_CHECK_BOX_1,
    GUI_ID_CHECK_BOX_2,
    GUI_ID_EDIT_BOX_1,
    GUI_ID_EDIT_BOX_2,
    GUI_ID_EDIT_BOX_3,
    GUI_ID_EDIT_BOX_4,
};

struct SAppContext
{
    irr::IrrlichtDevice *device;
    irr::s32 counter;
    irr::gui::IGUIListBox *listbox;
    std::vector<irr::core::stringc> Text;
    std::vector<bool> Bots;
    std::string svgName;
    bool newName;
    int status;
};


class MyEventReceiver : public irr::IEventReceiver
{
    public:
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE KeyCode) const;
        bool IsAnyPressed();
        MyEventReceiver();
        ~MyEventReceiver();
    private:
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        bool anyPressed;
};

class MyMenuEventReceiver : public irr::IEventReceiver
{
    public:
        MyMenuEventReceiver();
        ~MyMenuEventReceiver() {};
        MyMenuEventReceiver(SAppContext & context) : Context(context) {}
        virtual bool OnEvent(const irr::SEvent &event);
        editBoxPlayer box;
    private :
        SAppContext & Context;
        Sound           sound;
        SoundTest       soundTest;
};

#endif
