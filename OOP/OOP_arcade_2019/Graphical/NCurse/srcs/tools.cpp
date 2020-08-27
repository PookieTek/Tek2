/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#include "ncurse.hpp"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>

struct ScoresReg {
    std::string name;
    std::string game;
    int score;
};

void Ncurse::displayPauseScreen(void) {
    WINDOW *pauseBox = subwin(stdscr, 14, 30, (LINES / 2) - 7, (COLS / 2) - 15);

    clear();
    box(pauseBox, ACS_VLINE, ACS_HLINE);
    attron(COLOR_PAIR(3));
    mvprintw ((LINES / 2) - 7 + 2, (COLS / 2) - 15 + 3, "CONTINUE (ENTER)");
    mvprintw ((LINES / 2) - 7 + 5, (COLS / 2) - 15 + 3, "RESTART GAME (R)");
    mvprintw ((LINES / 2) - 7 + 8, (COLS / 2) - 15 + 3, "RETURN TO MENU (DEL)");
    mvprintw ((LINES / 2) - 7 + 11, (COLS / 2) - 15 + 3, "QUIT (ESC)");
    attron(COLOR_PAIR(1));
    delwin(pauseBox);
    refresh();
}

int Ncurse::DisplayGameOver(std::string player, int score) {
    WINDOW *OverBox = subwin(stdscr, 20, 50, (LINES / 2) - 10, (COLS / 2) - 25);

    clear();
    box(OverBox, ACS_VLINE, ACS_HLINE);
    mvprintw ((LINES / 2) - 9 + 2, (COLS / 2) - 3, "You Lose");
    mvprintw ((LINES / 2) - 7 + 2, (COLS / 2) - 25 + 3, "PLAYER:");
    mvprintw ((LINES / 2) - 7 + 3, (COLS / 2) - 25 + 3, "SCORE:");
    mvprintw ((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 15, ") TO RESTART GAME");
    mvprintw ((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 13, ") TO RETURN TO MENU");
    mvprintw ((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 13, ") TO QUIT");
    attron(COLOR_PAIR(3));
    mvprintw ((LINES / 2) - 7 + 2, (COLS / 2) - 25 + 11, "%s", player.c_str());
    mvprintw ((LINES / 2) - 7 + 3, (COLS / 2) - 25 + 11, "%d", score);
    mvprintw((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 10, "ENTER");
    mvprintw((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 10, "DEL");
    mvprintw((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 10, "ESC");
    attron(COLOR_PAIR(1));
    refresh();
    return 0;
}


int Ncurse::DisplayGameWin(std::string player, int score) {
    WINDOW *OverBox = subwin(stdscr, 20, 50, (LINES / 2) - 10, (COLS / 2) - 25);

    clear();
    box(OverBox, ACS_VLINE, ACS_HLINE);
    mvprintw ((LINES / 2) - 9 + 2, (COLS / 2) - 3, "You Win");
    mvprintw ((LINES / 2) - 7 + 2, (COLS / 2) - 25 + 3, "PLAYER:");
    mvprintw ((LINES / 2) - 7 + 3, (COLS / 2) - 25 + 3, "SCORE:");
    mvprintw ((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 15, ") TO RESTART GAME");
    mvprintw ((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 13, ") TO RETURN TO MENU");
    mvprintw ((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 3, "PRESS (");
    mvprintw ((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 13, ") TO QUIT");
    attron(COLOR_PAIR(3));
    mvprintw ((LINES / 2) - 7 + 2, (COLS / 2) - 25 + 11, "%s", player.c_str());
    mvprintw ((LINES / 2) - 7 + 3, (COLS / 2) - 25 + 11, "%d", score);
    mvprintw((LINES / 2) - 7 + 8, (COLS / 2) - 25 + 10, "ENTER");
    mvprintw((LINES / 2) - 7 + 11, (COLS / 2) - 25 + 10, "DEL");
    mvprintw((LINES / 2) - 7 + 14, (COLS / 2) - 25 + 10, "ESC");
    attron(COLOR_PAIR(1));
    refresh();
    return 0;
}


std::vector<std::string> ReadScores() {
    std::vector<std::string> tmpScores;
    std::vector<std::string> Scores;
    std::vector<ScoresReg> data;
    std::ifstream file("./games/.scores");
    std::string line;
    std::string sub;
    int lastScore = -1;
    int index = 0;

    while (std::getline(file, line)) {
        std::istringstream tok(line);
        while (std::getline(tok, sub, ';'))
            tmpScores.push_back(sub);
        ScoresReg tmp = {tmpScores.at(1), tmpScores.at(0), atoi(tmpScores.at(2).c_str())};
        data.push_back(tmp);
        tmpScores.clear();
    }
    while (data.size() > 0) {
        for (int i = 0; i < data.size(); i++) {
            if (data.at(i).score > lastScore) {
                lastScore = data.at(i).score;
                index = i;
            }
        }
        Scores.push_back(data.at(index).game + " : " + data.at(index).name + " " + std::to_string(data.at(index).score));
        data.erase(data.begin() + index);
        lastScore = -1;
    }
    return Scores;
}

const char *parseLib(std::string str) {
    std::string delim1 = "_";
    std::string ret = "- ";
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delim1)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delim1.length());
    }
    str.erase(str.size() - 3, str.size());
    ret.append(str);
    return ret.c_str();
}

int Ncurse::CheckWin() {
    if (LINES < 30 || COLS < 90)
        return -1;
    return 0;
}
