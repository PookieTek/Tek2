/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "core.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <dlfcn.h>


Core::Core()
{
    actualGraph = -1;
    actualGame = -1;
    interact = Interaction::Bind::NONEB;
    menuInfo.data["graphical"] = "";
    menuInfo.data["game"] = "";
    menuInfo.data["pseudo"] = "";
    menuInfo.index = 0;
    listGame = FillGame();
    listGraph = FillGraph();
    menuInfo.isPseudo = false;
    menuInfo.isStart = false;
    menuInfo.isEnter = false;
    game = NULL;
    handle = new HandleLib;
    timer = new HandleTime;
}

Core::~Core()
{
}

int Core::StartArcade(std::string lib)
{
    int todo = 0;
    bool toClear = true;

    timer->Restart();
    LoadGraphicalLib(lib);
    while (todo != -1) {
        if (todo == 0) {
            todo = graphical->DisplayMenu(listGraph, listGame, menuInfo, toClear);
            menuInfo = graphical->GetData(menuInfo);
        } else if (todo == 1) {
            if (game == NULL) {
                LoadGameLib(menuInfo.data["game"]);
                graphical->InitAsset(game->GetAsset());
            }
            if (timer->TimeLapsed(3000)) {
                todo = graphical->DisplayBoard(game->Refresh(), menuInfo.data, game->GetScore());
                if (game->GameOver()) {
                    graphical->DisplayGameOver(menuInfo.data["pseudo"], game->GetScore());
                    SaveScore(menuInfo.data["pseudo"], game->GetScore(), game->GetName());
                    interact = Interaction::Bind::NONEB;
                    game->Quit();
                    game = NULL;
                    todo = OverProg();
                    interact = Interaction::Bind::NONEB;
                } else if (game->GameWin()) {
                    graphical->DisplayGameWin(menuInfo.data["pseudo"], game->GetScore());
                    SaveScore(menuInfo.data["pseudo"], game->GetScore(), game->GetName());
                    interact = Interaction::Bind::NONEB;
                    game->Quit();
                    game = NULL;
                    todo = OverProg();
                    interact = Interaction::Bind::NONEB;
                }
                timer->Restart();
            }
        }
        if (!menuInfo.isPseudo)
            toClear = false;
        if (ParseEvent(graphical->GetKey()) != -1)
            toClear = true;
        if (todo == 0) {
            if (!menuInfo.isPseudo) {
                if (interact == Interaction::Bind::DOWN) {
                    menuInfo.index++;
                } else if (interact == Interaction::Bind::UP) {
                    menuInfo.index--;
                } if (menuInfo.index == menuInfo.menuX.size()) {
                    menuInfo.index = 0;
                } if (menuInfo.index < 0)
                    menuInfo.index = menuInfo.menuX.size() - 1;
            } 
            if (interact == Interaction::Bind::ENTER) {
                menuInfo.isEnter = true;
            }
        }
        if (todo == 1) {
            if (interact == Interaction::Bind::RESTART) {
                todo = -2;
            } else if (interact == Interaction::Bind::MENU) {
                game->Quit();
                game = NULL;
                graphical->setStart(false);
                todo = 0;
            } else if (interact == Interaction::Bind::BREAK) {
                interact = Interaction::Bind::NONEB;
                graphical->displayPauseScreen();
                todo = pauseProg();
                toClear = true;
            } else if (interact != Interaction::Bind::NONEB)
                game->Move(interact);
            if (todo == -2) {
                game->Quit();
                game = NULL;
                todo = 1;
            }
        }
        if (interact == Interaction::Bind::EXIT) {
            todo = -1;
        } else if (interact == Interaction::Bind::GR_NEXT || interact == Interaction::Bind::GR_PREVIOUS) {
            switchGraphics();
            if (todo == 1) {
                graphical->setStart(true);
                graphical->InitAsset(game->GetAsset());
            }
            toClear = true;
        } else if (interact == Interaction::Bind::GA_NEXT || interact == Interaction::Bind::GA_PREVIOUS) {
            switchGames();
            toClear = true;
        }
        interact = Interaction::Bind::NONEB; 
    }
    graphical->Quit();
    return 0;
}