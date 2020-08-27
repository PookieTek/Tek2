/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ncurse
*/

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include "../../include/IGraphicalLib.hpp"
#include <iostream>
#include <curses.h>

struct AssetAscii {
    std::string caracs;
    int red;
    int green;
    int blue;
};

class Ncurse : public IGraphicalLib
{
    public:
        Ncurse();
        ~Ncurse() {
            ResetWindow(false);
            clear();
            endwin();
        };

        int DisplayMenu(std::vector<std::string>,  std::vector<std::string>, MenuData, bool);
        int DisplayBoard(std::vector<std::vector<AssetInfo>>, std::map<std::string, std::string>, int);
        int DisplayGameOver(std::string, int);
        int DisplayGameWin(std::string player, int score);
        void Quit();
        MenuData GetData(MenuData);
        int GetKey();
        std::map<Interaction::Bind, int> GetMapping();
        void InitAsset(std::string);
        void DisplayBack();
        void DisplayList(std::vector<std::string> graph, std::vector<std::string> game);
        void DisplayButton(MenuData, int);
        void DisplayCursor(MenuData);
        void DisplayContent(std::vector<std::vector<AssetInfo>>);
        void ValidSelection(MenuData, std::vector<std::string>, std::vector<std::string>);
        void displayPauseScreen(void);
        void setStart(bool);

        int CheckWin();
        void ResetWindow(bool);
        void PrintError(std::string);
        void DispCh(char c);


        std::string cursGraph;
        std::string cursGame;
        std::string pseudo;
        WINDOW *leftMenu;
        WINDOW *rightMenu;
        WINDOW *scorebox;
        WINDOW *startbutton;
        WINDOW *pseudobox;
        WINDOW *gameBox;
        std::vector<int> menuX;
        std::vector<int> menuY;
        bool isStart;
        bool isPseudo;
        bool isEnter;
        bool Nclear;

        std::map<std::string, AssetAscii> assets;

};

std::vector<std::string> ReadScores();
const char *parseLib(std::string);

#endif /* !NCURSE_HPP_ */
