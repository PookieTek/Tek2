/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** event
*/

#include "core.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <dlfcn.h>
#include <time.h>
#include <unistd.h>

int Core::ParseEvent(int key)
{
    if (key == -1)
        return -1;
    else if (key == mapping[Interaction::Bind::EXIT])
        interact = Interaction::Bind::EXIT;
    else if (key == mapping[Interaction::Bind::LEFT])
        interact = Interaction::Bind::LEFT;
    else if (key == mapping[Interaction::Bind::RIGHT])
        interact = Interaction::Bind::RIGHT;
    else if (key == mapping[Interaction::Bind::UP])
        interact = Interaction::Bind::UP;
    else if (key == mapping[Interaction::Bind::DOWN])
        interact = Interaction::Bind::DOWN;
    else if (key == mapping[Interaction::Bind::GR_PREVIOUS])
        interact = Interaction::Bind::GR_PREVIOUS;
    else if (key == mapping[Interaction::Bind::GR_NEXT])
        interact = Interaction::Bind::GR_NEXT;
    else if (key == mapping[Interaction::Bind::GA_NEXT])
        interact = Interaction::Bind::GA_NEXT;
    else if (key == mapping[Interaction::Bind::GA_PREVIOUS])
        interact = Interaction::Bind::GA_PREVIOUS;
    else if (key == mapping[Interaction::Bind::RESTART])
        interact = Interaction::Bind::RESTART;
    else if (key == mapping[Interaction::Bind::MENU])
        interact = Interaction::Bind::MENU;
    else if (key == mapping[Interaction::Bind::BREAK])
        interact = Interaction::Bind::BREAK;
    else if (key == mapping[Interaction::Bind::ENTER])
        interact = Interaction::Bind::ENTER;
    else if (key == mapping[Interaction::Bind::SPEED])
        interact = Interaction::Bind::SPEED;
    return 0;
}

void Core::switchGraphics() {
    usleep(500);
    if (interact == Interaction::Bind::GR_NEXT) {
        graphical->Quit();
        actualGraph++;
        if (actualGraph >= listGraph.size())
            actualGraph = 0;
    } else {
        graphical->Quit();
        actualGraph--;
        if (actualGraph < 0)
            actualGraph = listGraph.size() - 1;
    }
    LoadGraphicalLib(listGraph.at(actualGraph));
    usleep(5000);
}

void Core::switchGames() {
    if (interact == Interaction::Bind::GA_NEXT) {
        if (game != NULL) {
            game->Quit();
            game = NULL;
        }
        actualGame++;
        if (actualGame >= listGame.size())
            actualGame = 0;
    } else {
        if (game != NULL) {
            game->Quit();
            game = NULL;
        }
        actualGame--;
        if (actualGame < 0)
            actualGame = listGame.size() - 1;
    }
    menuInfo.data["game"] = listGame.at(actualGame);
}

int Core::OverProg() {
    ParseEvent(graphical->GetKey());

    if (interact == Interaction::Bind::EXIT) {
        return (-1);
    } else if (interact == Interaction::Bind::ENTER)
        return (1);
    else if (interact == Interaction::Bind::MENU) {
        graphical->setStart(false);
        return (0);
    }
    return (pauseProg());
}


int Core::pauseProg() {
    while (1) {
        ParseEvent(graphical->GetKey());
        if (interact == Interaction::Bind::EXIT)
            return (-1);
        else if (interact == Interaction::Bind::ENTER || interact == Interaction::Bind::BREAK)
            return (1);
        else if (interact == Interaction::Bind::RESTART)
            return (-2);
        else if (interact == Interaction::Bind::MENU) {
            graphical->setStart(false);
            return (0);
        }
        usleep(100);
    }
    return 0;
}
