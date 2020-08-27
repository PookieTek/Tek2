/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** lib
*/

#include "core.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <dlfcn.h>
#include <time.h>


std::vector<std::string> FillGame()
{
    std::vector<std::string> list;
    DIR *dir = opendir("games");
    struct dirent *dirdata;
    std::string tmp = "games/";

    while ((dirdata = readdir(dir)) != NULL) {
        if (strcmp(dirdata->d_name, ".") != 0 && strcmp(dirdata->d_name, "..") != 0 && strcmp(dirdata->d_name, ".scores") != 0) {
            tmp.append(dirdata->d_name);
            list.push_back(tmp);
            tmp = "games/";
        }
    }
    closedir(dir);
    return list;
}


void Core::LoadGraphicalLib(std::string lib)
{
    std::string tmp;

    listGraph = FillGraph();
    for (int i = 0; i < listGraph.size(); i++) {
        tmp = listGraph.at(i);
        if (tmp.compare(lib) == 0)
            this->actualGraph = i;
    }
    menuInfo.data["graphical"] = lib;
    if (InitGraphical(lib) == -1)
        exit(84);
    mapping = graphical->GetMapping();
}

void Core::LoadGameLib(std::string lib)
{
    std::string tmp;
    listGame = FillGame();
    for (int i = 0; i < listGame.size(); i++) {
        tmp = listGame.at(i);
        if (tmp.compare(lib) == 0)
            actualGame = i;
    }
    menuInfo.data["game"] = lib;
    if (InitGame(lib) == -1)
        exit(84);
}


int Core::InitGraphical(std::string lib) { return ((graphical = handle->GetGraph(lib)) ? 0 : -1); }

int Core::InitGame(std::string lib) { return ((game = handle->GetGame(lib)) ? 0 : -1); }

std::vector<std::string> FillGraph()
{
    std::vector<std::string> list;
    DIR *dir = opendir("lib");
    struct dirent *dirdata;
    std::string tmp = "lib/";

    while ((dirdata = readdir(dir)) != NULL) {
        if (strcmp(dirdata->d_name, ".") != 0 && strcmp(dirdata->d_name, "..") != 0 && strcmp(dirdata->d_name, ".data") != 0) {
            tmp.append(dirdata->d_name);
            list.push_back(tmp);
            tmp = "lib/";
        }
    }
    closedir(dir);
    return list;
}
