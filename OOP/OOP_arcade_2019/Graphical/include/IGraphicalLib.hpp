/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGraphicalLib
*/

#ifndef IGRAPHICALLIB_HPP_
#define IGRAPHICALLIB_HPP_
#include <iostream>
#include <map>
#include <vector>
#include "../../Core/include/structInfo.hpp"
#include "../../Game/include/IGameLib.hpp"


class IGraphicalLib {
    public:
        virtual ~IGraphicalLib() {};

        virtual int DisplayMenu(std::vector<std::string> listGraph, std::vector<std::string> listGame, MenuData data, bool) = 0;
        virtual int DisplayBoard(std::vector<std::vector<AssetInfo>>, std::map<std::string, std::string>, int) = 0;
        virtual int DisplayGameOver(std::string, int) = 0;
        virtual int DisplayGameWin(std::string, int) = 0;
        virtual void Quit() = 0; // Call DTOR + free;
        virtual MenuData GetData(MenuData) = 0;
        virtual int GetKey() = 0;
        virtual void InitAsset(std::string) = 0;
        virtual std::map<Interaction::Bind, int> GetMapping() = 0;
        virtual void displayPauseScreen(void) = 0;
        virtual void setStart(bool) = 0;
    protected:
    private:
};

extern "C" IGraphicalLib *creatorGraph();

#endif /* !IGRAPHICALLIB_HPP_ */
