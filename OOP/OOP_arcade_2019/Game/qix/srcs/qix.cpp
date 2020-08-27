/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <iostream>
#include "qix.hpp"
#include <utility>
#include <time.h>
#include <unistd.h>
#include <experimental/random>
/*
    TYPE :
    0 : empty
    1 : player
    2 : trail
    3 : n-wakable
    4 : qix


*/

Qix::Qix() : IGameLib()
{
    std::vector<AssetInfo> tmp(76, AssetInfo{Types::EMPTY, "empty", AssetOrientation::UP});

    player.cols = 0;
    player.lines = 18;
    player.dir = 1;
    lastPoint.cols = 0;
    lastPoint.lines = 18;
    monster.lines = 30;
    monster.cols = 70;
    for (int i = 0; i < 36; i++) {
        board.push_back(tmp);
    }

    for (int i = 0; i < 36; i++) {
        board.at(i).at(0) = AssetInfo{Types::BORDER, "border/", 0};
        board.at(i).at(75) = AssetInfo{Types::BORDER, "border/", 0}; 
    }
    for (int i = 1; i < 75; i++) {
        board.at(0).at(i) = AssetInfo{Types::BORDER, "border/", 1};
        board.at(35).at(i) = AssetInfo{Types::BORDER, "border/", 1};
    }
    assetpath = "/qix/asset/";
    gameName = "Qix";
    score = 0;
    gameOver = false;
}

std::vector<std::vector<AssetInfo>> Qix::Refresh() {
    srand(time(NULL));
    return board;
}

/*
    Trail => list chainée
*/

bool Qix::IsInDrawn(int l, int c) {
    int count = 0;

    if (l > 0 && (board.at(l - 1).at(c).type == Types::NWAKABLE || board.at(l - 1).at(c).type == Types::SPARKLE || board.at(l - 1).at(c).type == Types::BORDER))
        count++;
    if (l < 35 && (board.at(l + 1).at(c).type == Types::NWAKABLE || board.at(l + 1).at(c).type == Types::SPARKLE || board.at(l + 1).at(c).type == Types::BORDER))
        count++; 
    if (c > 0 && (board.at(l).at(c - 1).type == Types::NWAKABLE || board.at(l).at(c - 1).type == Types::SPARKLE || board.at(l).at(c - 1).type == Types::BORDER))
        count++;
   if (c < 75 && (board.at(l).at(c + 1).type == Types::NWAKABLE || board.at(l).at(c + 1).type == Types::SPARKLE || board.at(l).at(c + 1).type == Types::BORDER))
        count++;
    if (count >= 3)
        return true;
    return false;
}

void Qix::ResetPlayer() {
    board.at(player.lines).at(player.cols) = AssetInfo{Types::EMPTY, "empty/", 0};
    player.lines = lastPoint.lines;
    player.cols = lastPoint.cols;
    EraseTrail();
}

void Qix::SetQix() {
    AssetInfo tmp = AssetInfo{Types::QIX, "qix/", 0};
    AssetInfo empty = AssetInfo{Types::EMPTY, "empty/", 0};
    int newLines = 0;
    int newCols = 0;

    while (newLines < 2 || newLines > 33 || newCols < 2 || newCols > 70 || IsInDrawn(newLines - 2, newCols - 2) || IsInDrawn(newLines + 2, newCols + 2)) {
        newLines = monster.lines + std::experimental::randint(-1, 1);
        newCols = monster.cols + std::experimental::randint(-1, 1);
    }
    board.at(monster.lines - 1).at(monster.cols - 1) = empty;
    board.at(monster.lines - 1).at(monster.cols + 1) = empty;
    board.at(monster.lines).at(monster.cols - 1) = empty;
    board.at(monster.lines).at(monster.cols) = empty;
    board.at(monster.lines).at(monster.cols + 1) = empty;
    board.at(monster.lines + 1).at(monster.cols - 1) = empty;
    board.at(monster.lines + 1).at(monster.cols) = empty;
    board.at(monster.lines + 1).at(monster.cols + 1) = empty;
    board.at(monster.lines + 2).at(monster.cols - 2) = empty;
    board.at(monster.lines + 2).at(monster.cols + 2) = empty;
    monster.lines = newLines;
    monster.cols = newCols;
    for (int i = -2; i < 3; i++) {
        if (board.at(monster.lines + i).at(monster.cols + i).type == Types::TRAIL)
            ResetPlayer();
    }
    board.at(monster.lines - 1).at(monster.cols - 1) = tmp;
    board.at(monster.lines - 1).at(monster.cols + 1) = tmp;
    board.at(monster.lines).at(monster.cols - 1) = tmp;
    board.at(monster.lines).at(monster.cols) = tmp;
    board.at(monster.lines).at(monster.cols + 1) = tmp;
    board.at(monster.lines + 1).at(monster.cols - 1) = tmp;
    board.at(monster.lines + 1).at(monster.cols) = tmp;
    board.at(monster.lines + 1).at(monster.cols + 1) = tmp;
    board.at(monster.lines + 2).at(monster.cols - 2) = tmp;
    board.at(monster.lines + 2).at(monster.cols + 2) = tmp;
}

void Qix::fillBoard() {
    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board.at(i).size(); j++) {
            if (board.at(i).at(j).type == Types::PLAYER) {
                if (player.lines != i || (player.cols != j && !IsInDrawn(player.lines, player.cols))) {
                    board.at(i).at(j) = AssetInfo{Types::TRAIL, "trail/", player.dir};
                }
            }
        }
    }
    for (int i = 0; i < 36; i++) {
        board.at(i).at(0) = AssetInfo{Types::BORDER, "border/", 0};
        board.at(i).at(75) = AssetInfo{Types::BORDER, "border/", 0}; 
    }
    for (int i = 1; i < 75; i++) {
        board.at(0).at(i) = AssetInfo{Types::BORDER, "border/", 1};
        board.at(35).at(i) = AssetInfo{Types::BORDER, "border/", 1};
    }
    board.at(player.lines).at(player.cols) = AssetInfo{Types::PLAYER, "player/", player.dir};
    SetQix();
}

void Qix::EraseTrail() {
    for (int l = 0; l < (int)board.size(); l++) {
        for (int c = 0; c < (int)board.at(l).size(); c++) {
            if (board.at(l).at(c).type == Types::TRAIL) {
                if (IsInDrawn(l, c))
                    board.at(l).at(c) = AssetInfo{Types::NWAKABLE, "nwakable/", 0};
                else if (l == 0 || c == 0 || l == (int)board.size() - 1 || c == (int)board.at(0).size() - 1)
                    board.at(l).at(c) = AssetInfo{Types::BORDER, "border/", 0};
                else
                    board.at(l).at(c) = AssetInfo{Types::EMPTY, "empty/", 0};
            }
        }
    }
}

int Qix::GetQixMapPosition(int lines, int cols) {
    if (copyboard.at(lines).at(cols).type == Types::QIX)
        return (-1);
    if (copyboard.at(lines).at(cols).type == Types::BORDER || copyboard.at(lines).at(cols).type == Types::TRAIL || copyboard.at(lines).at(cols).type == Types::PLAYER)
        return (0);
    copyboard.at(lines).at(cols).type = Types::NWAKABLE;
    if (lines > 0 && copyboard.at(lines - 1).at(cols).type != Types::NWAKABLE) {
        if (GetQixMapPosition(lines - 1, cols) == -1)
            return (-1);
    }
    if (lines < 34 && copyboard.at(lines + 1).at(cols).type != Types::NWAKABLE) {
        if (GetQixMapPosition(lines + 1, cols) == -1)
            return (-1);
    }
    if (cols > 0 && copyboard.at(lines).at(cols - 1).type != Types::NWAKABLE) {
        if (GetQixMapPosition(lines, cols - 1) == -1)
            return (-1);
    }
    if (cols < 74 && copyboard.at(lines).at(cols + 1).type != Types::NWAKABLE) {
        if (GetQixMapPosition(lines, cols + 1) == -1)
            return (-1);
    }
    return (0);
}

std::pair<int, int> Qix::choseCorner() {
    int lines, cols;
    std::pair<int, int> coord;

    copyboard = board;
    lines = (player.lines == 0) ? 1 : player.lines - 1;
    cols = (player.cols == 0) ? 1 : player.cols - 1;
    if (GetQixMapPosition(lines, cols) == 0) {
        coord.first = lines;
        coord.second = cols;
        return (coord);
    }
    copyboard = board;
    lines = (player.lines == 35) ? player.lines - 1 : player.lines + 1;
    cols = (player.cols == 75) ? player.cols - 1 : player.cols + 1;
    if (GetQixMapPosition(lines, cols) == 0) {
        coord.first = lines;
        coord.second = cols;
        return (coord);
    }
    copyboard = board;
    lines = (player.lines == 0) ? 1 : player.lines - 1;
    cols = (player.cols == 75) ? player.cols - 1 : player.cols + 1;
    if (GetQixMapPosition(lines, cols) == 0) {
        coord.first = lines;
        coord.second = cols;
        return (coord);
    }
    copyboard = board;
    lines = (player.lines == 35) ? player.lines - 1 : player.lines + 1;
    cols = (player.cols == 0) ? player.cols + 1 : player.cols - 1;
    GetQixMapPosition(lines, cols);
    coord.first = lines;
    coord.second = cols;
    return (coord);
}

void Qix::fillBorderMap(void) {
    for (int lines = 0; lines < 35; lines++) {
        for (int cols = 0; cols < 75; cols++) {
            if (copyboard.at(lines).at(cols).type == Types::NWAKABLE || copyboard.at(lines).at(cols).type == Types::TRAIL) {
                board.at(lines).at(cols) = AssetInfo{Types::NWAKABLE, "nwakable/", 0};
            }
        }
    }
}

void Qix::CreateAreaNW() {
    choseCorner();
    fillBorderMap();
    lastPoint = Point{player.lines, player.cols};
    EraseTrail();
}

void Qix::Move(Interaction::Bind dir) {
    bool moveOtherSide = false;

    if (dir == Interaction::Bind::RIGHT) {
        player.cols++;
        player.dir = 1;
        if (player.lines == 0 || player.lines == 35)
            moveOtherSide = true;
    } if (dir == Interaction::Bind::LEFT) {
        player.cols--;
        player.dir = 3;
        if (player.lines == 0 || player.lines == 35)
            moveOtherSide = true;
    } if (dir == Interaction::Bind::UP) {
        player.lines--;
        player.dir = 0;
        if (player.cols == 0 || player.cols == 75)
            moveOtherSide = true;
    } if (dir == Interaction::Bind::DOWN) {
        player.lines++;
        player.dir = 2;
        if (player.cols == 0 || player.cols == 75)
            moveOtherSide = true;
    }
    score += 10;
    if (player.cols > 75) {
        player.cols = 0;
        moveOtherSide = true;
    }
    if (player.cols < 0) {
        player.cols = 75;
        moveOtherSide = true;
    }
    if (player.lines > 35) {
        player.lines = 0;
        moveOtherSide = true;
    }
    if (player.lines < 0) {
        player.lines = 35;
        moveOtherSide = true;
    }
    if (moveOtherSide == false && (board.at(player.lines).at(player.cols).type == Types::BORDER || board.at(player.lines).at(player.cols).type == Types::NWAKABLE)) {
        CreateAreaNW();
        score += 150;
    }
    fillBoard();
}


int Qix::GetScore() {
    return score;
}


void Qix::Quit() {
    this->~Qix();
}

bool Qix::GameWin() {
    int count = 0;

    for (int lines = 0; lines < 36; lines++) {
        for (int cols = 0; cols < 76; cols++) {
            if (board.at(lines).at(cols).type == Types::EMPTY)
                count++;
        }
    }
    if (count <= 684) {
        return true;
    }
    return false;
}

bool Qix::GameOver() {
    return gameOver;
}

std::string Qix::GetName() { return gameName;}

std::string Qix::GetAsset() { return assetpath; }



extern "C" IGameLib *creatorGame() {
    return (new Qix);
}