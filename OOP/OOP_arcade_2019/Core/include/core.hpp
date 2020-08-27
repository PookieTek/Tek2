/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include "../../Game/include/IGameLib.hpp"
#include "../../Graphical/include/IGraphicalLib.hpp"
#include <vector>
#include "interaction.hpp"
#include <map>
#include "structInfo.hpp"
#include <sys/types.h>
#include <dlfcn.h>
#include <time.h>


class HandleLib {
    public:
        HandleLib();
        ~HandleLib();
    
        IGraphicalLib *GetGraph(std::string);
        IGameLib *GetGame(std::string);
};

class HandleTime {
    public:
        HandleTime();
        ~HandleTime();

        void Restart();
        bool TimeLapsed(int);
    private:
        int timer;
};

class Core
{
    public:
        Core();
        ~Core();

        int StartArcade(std::string);
        void GetKeyPress();

    private:
        void LoadGraphicalLib(std::string);
        void LoadGameLib(std::string);
        int InitGraphical(std::string);
        int InitGame(std::string);
        int ParseEvent(int);
        void switchGraphics();
        void switchGames();
        int pauseProg(void);
        int OverProg();
        void SaveScore(std::string, int, std::string);



        int actualGraph;
        int actualGame;
        Interaction::Bind interact;
        std::vector<std::string> listGraph;
        std::vector<std::string> listGame;
        IGraphicalLib *graphical;
        IGameLib *game;
        std::map<Interaction::Bind, int> mapping;
        MenuData menuInfo;
        HandleLib *handle;
        HandleTime *timer;
};

std::vector<std::string> FillGraph();
std::vector<std::string> FillGame();
#endif /* !CORE_HPP_ */
