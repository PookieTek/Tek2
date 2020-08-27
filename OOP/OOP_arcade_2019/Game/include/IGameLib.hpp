/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGameLib
*/

#ifndef IGAMELIB_HPP_
#define IGAMELIB_HPP_

#include "../../Core/include/interaction.hpp"
#include <iostream>
#include <vector>

enum AssetOrientation {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

struct AssetInfo {
    int type;
    std::string path;
    int orientation;
};

class IGameLib {
    public:
        virtual ~IGameLib() {};
        
        virtual std::vector<std::vector<AssetInfo>> Refresh() = 0; // Type Return a définir (renvoie le board a jour)
        virtual void Move(Interaction::Bind) = 0;
        virtual void Quit() = 0; // DTOR + Free
        virtual bool GameOver() = 0;
        virtual bool GameWin() = 0;
        virtual int GetScore() = 0;
        virtual std::string GetName() = 0;

        virtual std::string GetAsset() = 0;
    protected:
    private:
};

extern "C" IGameLib *creatorGame();

#endif /* !IGAMELIB_HPP_ */
