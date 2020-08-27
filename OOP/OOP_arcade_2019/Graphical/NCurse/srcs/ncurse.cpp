/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ncurse
*/

#include "ncurse.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

Ncurse::Ncurse() : IGraphicalLib()
{
    initscr();
    start_color();
    noecho();
    keypad(stdscr, true);
    attron(A_BOLD);
    init_color(COLOR_BLACK, 184, 208, 216);
    init_color(COLOR_YELLOW, 183, 28, 168);
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    curs_set(0);
    leftMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, 0);
    rightMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, (2 * COLS / 3) + (COLS / 20));
    scorebox = subwin(stdscr, LINES / 2, COLS / 3, LINES / 5, COLS / 3);
    startbutton = subwin(stdscr, 3, 9, LINES - 6, COLS / 2 - 4);
    pseudobox = subwin(stdscr, 3, pseudo.size() + 4, 2, COLS / 2 + 2);
    isStart = false;
    isPseudo = false;
    isEnter = false;
}


std::map<Interaction::Bind, int> Ncurse::GetMapping() {
    std::map<Interaction::Bind, int> mapping;

    mapping[Interaction::Bind::RIGHT] = 261;
    mapping[Interaction::Bind::LEFT] = 260;
    mapping[Interaction::Bind::UP] = 259;
    mapping[Interaction::Bind::DOWN] = 258;
    mapping[Interaction::Bind::GR_PREVIOUS] = 338;
    mapping[Interaction::Bind::GR_NEXT] = 339;
    mapping[Interaction::Bind::GA_PREVIOUS] = 262;
    mapping[Interaction::Bind::GA_NEXT] = 360;
    mapping[Interaction::Bind::RESTART] = 114;
    mapping[Interaction::Bind::BREAK] = 112;
    mapping[Interaction::Bind::EXIT] = 27;
    mapping[Interaction::Bind::MENU] = KEY_BACKSPACE;
    mapping[Interaction::Bind::ENTER] = 10;
    mapping[Interaction::Bind::SPEED] = 32;
    return (mapping);
}

void Ncurse::ResetWindow(bool toSet) {
    delwin(scorebox);
    delwin(startbutton);
    delwin(leftMenu);
    delwin(rightMenu);
    delwin(pseudobox);
    if (toSet) {
        leftMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, 0);
        rightMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, (2 * COLS / 3) + (COLS / 20));
        scorebox = subwin(stdscr, LINES / 2, COLS / 3, LINES / 5, COLS / 3);
        startbutton = subwin(stdscr, 3, 9, LINES - 6, COLS / 2 - 4);
        pseudobox = subwin(stdscr, 3, pseudo.size() + 4, 2, COLS / 2 + 2);
    }
}

AssetAscii ncurse_Asset(std::string filename)
{
    AssetAscii asset;
    std::string tmp;
    std::ifstream file(filename, std::ifstream::in);

    if (!file)
        exit(84);
    std::getline(file, asset.caracs);
    std::getline(file, tmp);
    asset.red = atoi(tmp.c_str());
    std::getline(file, tmp);
    asset.green = atoi(tmp.c_str());
    std::getline(file, tmp);
    asset.blue = atoi(tmp.c_str());
    if (asset.caracs == "\0")
        exit (84);
    return (asset);
}


void Ncurse::InitAsset(std::string path) {
    std::string totalpath = "./Game";
    totalpath.append(path);

    DIR *dir = opendir(totalpath.c_str());
    struct dirent *dirdata;
    std::string tmp = totalpath;

    while ((dirdata = readdir(dir)) != NULL) {
        if (strcmp(dirdata->d_name, ".") != 0 && strcmp(dirdata->d_name, "..") != 0) {
            tmp.append(dirdata->d_name);
            tmp.append("/ascii");
            assets[dirdata->d_name] = ncurse_Asset(tmp);
            tmp = totalpath;
        }
    }
}

MenuData Ncurse::GetData(MenuData data) {
    data.data["game"] = cursGame;
    data.data["graphical"] = cursGraph;
    data.data["pseudo"] = pseudo;
    data.menuX = menuX;
    data.menuY = menuY;
    data.isStart = isStart;
    data.isPseudo = isPseudo;
    data.isEnter = isEnter;
    return data;
}

int Ncurse::GetKey() {
    int key = -1;

    timeout(1);
    key = getch();
    if (key == KEY_RESIZE) {
        ResetWindow(true);
        Nclear = true;
    }
    return key;
}

void Ncurse::Quit() {
    this->~Ncurse();
}

void Ncurse::setStart(bool start) { isStart = start; }

extern "C" IGraphicalLib *creatorGraph() {
    return (new Ncurse);
}