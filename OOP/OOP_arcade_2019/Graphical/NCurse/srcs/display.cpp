/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** display
*/

#include "ncurse.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>

void PrintLine(int x, int y, int size) {
    attron(COLOR_PAIR(3));
    mvhline(x, y, ACS_HLINE, size);
    attron(COLOR_PAIR(1));
}

void Ncurse::DisplayButton(MenuData data, int graphsize)
{
    std::vector<std::string> Scores = ReadScores();
    attron(COLOR_PAIR(2));
    box(scorebox, ACS_VLINE, ACS_HLINE);
    box(startbutton, ACS_VLINE, ACS_HLINE);
    if (data.data["pseudo"].size() > 0)
        box(pseudobox, ACS_BULLET, ACS_BULLET);
    attron(COLOR_PAIR(1));
    mvprintw(3, COLS / 2 - 8, "Pseudo :");
    menuX.at(graphsize) = COLS / 2 + 8 + data.data["pseudo"].size();
    menuY.at(graphsize) = 3;
    if (data.data["pseudo"].size() > 0)
        mvprintw(3, COLS / 2 + 4, "%s", data.data["pseudo"].c_str());
    mvprintw(LINES / 5 + 1, COLS / 2 - 7, "High Score");
    PrintLine(LINES / 5 + 2, COLS / 3 + COLS / 20, COLS / 3 - COLS / 10);
    for (int a = 0; a < (3 * LINES / 18) && a < Scores.size(); a++)
        mvprintw(LINES / 5 + 5 + (a * 2), COLS / 3 + 1, "- %s", Scores.at(a).c_str());
    mvprintw(LINES - 5, COLS / 2 - 2, "START");
    attron(COLOR_PAIR(4));
    mvprintw(LINES - 1, COLS / 2 - 17, "Arrow : navigate  Enter : validate");
    attron(COLOR_PAIR(1));
    menuX.at(graphsize + 1) = COLS / 2 + 6;
    menuY.at(graphsize + 1) = LINES - 5;
}

void Ncurse::DisplayList(std::vector<std::string> graph, std::vector<std::string> game) {

    for (int i = 0; i < (int)graph.size(); i++) {
        mvprintw(LINES / 8 + (2 * i), 3, parseLib(graph.at(i)));
        menuX.push_back(5 + strlen(parseLib(graph.at(i))));
        menuY.push_back(LINES / 8 + (2 * i));
        if (cursGraph.compare(graph.at(i)) == 0) {
            mvprintw(LINES / 8 + (2 * i), 4 + strlen(parseLib(graph.at(i))), "");
            addch(ACS_DIAMOND);
        }
    }
    menuX.push_back(0);
    menuX.push_back(0);
    menuY.push_back(0);
    menuY.push_back(0);
    for (int i = 0; i < (int)game.size(); i++) {
        mvprintw(LINES / 8 + (2 * i), 2 * COLS / 3 + 13, parseLib(game.at(i)));
        menuX.push_back(2 * COLS / 3 + 15 + strlen(parseLib(game.at(i))));
        menuY.push_back(LINES / 8 + ( 2 * i));
        if (cursGame.compare(game.at(i)) == 0) {
            mvprintw(LINES / 8 + (2 * i), 2 * COLS / 3 + 14 + strlen(parseLib(game.at(i))), "");
            addch(ACS_DIAMOND);
        }
    }
}

void Ncurse::DisplayBack() {
    attron(COLOR_PAIR(2));
    leftMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, 0);
    rightMenu = subwin(stdscr, LINES, COLS / 3 - COLS / 20, 0, (2 * COLS / 3) + (COLS / 20));
    box(leftMenu, ACS_VLINE, ACS_HLINE);
    box(rightMenu, ACS_VLINE, ACS_HLINE);
    attron(COLOR_PAIR(1));
    mvprintw(1, (COLS / 3 - COLS / 20) / 2 - 5, "Graphicals");
    PrintLine(2, COLS / 20,  COLS / 3 - COLS / 20 - COLS / 10);
    mvprintw(1, (2 * COLS / 3) + ((COLS / 20) + (COLS / 3 - COLS / 20) / 2) - 3, "Games");
    PrintLine(2,  (2 * COLS / 3) + (COLS / 20) + COLS / 20,  COLS / 3 - COLS / 20 - COLS / 10);
}

void Ncurse::DisplayCursor(MenuData data) {
    mvprintw(menuY.at(data.index), menuX.at(data.index), "");
    if (isPseudo) {
        attron(COLOR_PAIR(3));
    }
    addch(ACS_LARROW);
    attron(COLOR_PAIR(1));
}

void Ncurse::PrintError(std::string msg) {
    attron(COLOR_PAIR(3));
    mvprintw(LINES - (LINES / 5), COLS / 2 - (msg.size() / 2), msg.c_str());
    attron(COLOR_PAIR(1));
}

void Ncurse::ValidSelection(MenuData data, std::vector<std::string> graph, std::vector<std::string> game) {
    if (data.isPseudo) {
        isPseudo = false;
    } else if (data.index < (int)graph.size()) {
       cursGraph = graph.at(data.index);
    } else if (data.index > (int)graph.size() + 1) {
        cursGame = game.at(data.index - 2 - graph.size());
    } else if (data.index == (int)graph.size() + 1) {
        if (data.data["pseudo"].size() == 0)
            PrintError("Please, Chose a Pseudonyme.");
        else if (data.data["game"].size() == 0)
            PrintError("Please, Chose a Game.");
        else
            isStart = true;
    } else if (data.index == (int)graph.size()) {
        isPseudo = true;
    }
    isEnter = false;
}


int Ncurse::DisplayMenu(std::vector<std::string> listGraph, std::vector<std::string> listGame, MenuData data, bool toClear) {
    int key = -1;

    cursGraph = data.data["graphical"];
    cursGame = data.data["game"];
    pseudo = data.data["pseudo"];
    if (toClear)
        Nclear = toClear;
    if (!Nclear)
        return 0;
    menuX.clear();
    menuY.clear();
    clear();
    if (data.isEnter)
        ValidSelection(data, listGraph, listGame);
    if (CheckWin() == -1) { 
        printw("Le terminal est trop petit pour afficher le Menu.");
    } else {
        ResetWindow(true);
        DisplayBack();
        DisplayList(listGraph, listGame);
        DisplayButton(data, listGraph.size());
        DisplayCursor(data);
    }
    
    if (data.isPseudo) {
        timeout(-1);
        key = getch();
        delwin(pseudobox);
        if (((key > 41 && key < 91) || (key > 96 && key < 123)) && pseudo.size() < 20)
            pseudo.push_back(key);
        else if (key == 10)
            data.isPseudo = false;
        else if (key == KEY_BACKSPACE) {
            if (pseudo.size() > 0)
                pseudo.resize(pseudo.size() - 1);
        }
        pseudobox = subwin(stdscr, 3, pseudo.size() + 4, 2, COLS / 2 + 2);
        ungetch(key);
    }
    refresh();
    if (isStart) {
        ResetWindow(false);
        return 1;
    }
    Nclear = false;
    return 0;
}