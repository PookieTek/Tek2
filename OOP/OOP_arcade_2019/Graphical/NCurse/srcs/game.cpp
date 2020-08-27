/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** game
*/

#include "ncurse.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>

void Ncurse::DispCh(char c) {
    if (c != '\0')
        addch(c);
    else
        addch(' ');
}

void Ncurse::DisplayContent(std::vector<std::vector<AssetInfo>> board) {
    std::string tmp;
    int posx = COLS / 2 - (board.at(0).size() / 2);
    int posy = LINES / 2 - (board.size() / 2);
    char disp;
    /*
        board => LINES
        board.at().dretersdf => COLS
    */
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.at(i).size(); j++) {
            tmp = board.at(i).at(j).path;
            tmp.erase(tmp.size() - 1);
            mvprintw(posy + i, posx + j, "");
            disp = assets[tmp].caracs.c_str()[board.at(i).at(j).orientation];
            DispCh(disp);
        }
    }
}

int Ncurse::DisplayBoard(std::vector<std::vector<AssetInfo>> board, std::map<std::string, std::string> data, int score) {
    clear();
    int height = (int)board.size();
    int width = (int)board.at(0).size();
    mvprintw ((LINES / 2) - (height / 2) - 2, (COLS / 2) - (width / 2) + 1, "PLAYER:  %s", data["pseudo"].c_str());
    mvprintw((LINES / 2) - (height / 2) - 2, (COLS / 2) + (width / 2) - 11, "SCORE: %d", score);
    gameBox = subwin(stdscr, height + 2, width + 2, (LINES / 2) - (height / 2) - 1, (COLS / 2) - (width / 2) - 1);
    box(gameBox, ACS_VLINE, ACS_HLINE);
    DisplayContent(board);
    attron(COLOR_PAIR(4));
    if (COLS > 35 + width + 2) {
        mvprintw(LINES / 2 - 4, 1, "Page Down   : Previous Graphics");
        mvprintw(LINES / 2 - 3, 1, "Page Up     : Next Graphics");
        mvprintw(LINES / 2 - 2, 1, "ESC         : Exit");
        mvprintw(LINES / 2 - 1, 1, "Begin       : Previous Game");
        mvprintw(LINES / 2 + 0, 1, "End         : Next Game");
        mvprintw(LINES / 2 + 1, 1, "Arrow       : Move");
        mvprintw(LINES / 2 + 2, 1, "P           : Break");
        mvprintw(LINES / 2 + 3, 1, "R           : Restart");
        mvprintw(LINES / 2 + 4, 1, "DEL         : Menu");
    }
    attron(COLOR_PAIR(1));
    refresh();
    return 1;
}