/*
** EPITECH PROJECT, 2020
** srcs
** File description:
** Graphique
*/

#ifndef _GAMEINFO_HPP_
#define _GAMEINFO_HPP_

#include <memory>
#include <vector>
#include <include/irrlicht.h>
#include "Game.hpp"
#include "EventReceiver.hpp"
#include "Timer.hpp"
#include "Sound.hpp"

#ifdef __has_include
#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<expermiental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem
#endif
#endif

enum {
    menu,
    newGame,
    loadGame,
    game,
    option,
    quit,
    end,
};



class Gameinfo {
    public:
        Gameinfo();
        int startGame();
        void startMenu();
        void startNewGame();
        void startLoadGame();
        void EndGame();
        void initMenuWindow(const wchar_t *windowName);
        int GetStatus();
        void SetStatus(int);
        void DisplayBoard();
        void Drop();
        void DisplayBonus(Types::BonusType, int, int);
        void DisplayBomb(Types::BombStatus, int, int);
        void DisplayPlayer(Types::PlayerModel, std::pair<float, float>, int, Types::PlayerOrientation);
        void DisplayHud();
        void HandleMovement(MyEventReceiver);
        void ResetAll();

        Sound                           sound;
        SoundTest                       soundTest;
    private:
        int                             status;
        bool                            is_loadingGame;
        std::string                     SaveName;
        irr::IrrlichtDevice             *device;
        irr::video::IVideoDriver        *driver;
        irr::gui::IGUIEnvironment       *env;
        irr::video::ITexture            *titleScreen;
        std::unique_ptr<IGame>          game;
        Timer                           tickSpeed;
};

irr::IrrlichtDevice* initScreen();

#endif /* !GRAPHIQUE_H_ */
