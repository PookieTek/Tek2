/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include <SFML/Audio.hpp>
#include <include/irrlicht.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <memory>
#include "Gameinfo.hpp"
#include "Bonus.hpp"
#include "Bomb.hpp"
#include "Board.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"
#include "MyException.hpp"

#include "SoundTest.hpp"

int main() {
    try {
        std::unique_ptr<Gameinfo> info = std::make_unique<Gameinfo>();
        int status;

        while (info->GetStatus() != quit) {
            info->soundTest.MusicPlay(MENU);
            if (info->GetStatus() == menu) {
                info->startMenu();
                if (info->GetStatus() == menu) {
                    info->SetStatus(quit);
                }
            }
            if (info->GetStatus() == newGame) {
                info->startNewGame();
                if (info->GetStatus() == newGame) {
                    info->SetStatus(quit);
                }
            }
            if (info->GetStatus() == loadGame) {
                info->startLoadGame();
                if (info->GetStatus() == loadGame) {
                    info->SetStatus(quit);
                }
            }
            if (info->GetStatus() == game) {
                info->soundTest.MusicStop();
                info->soundTest.SoundPlay(START);
                info->soundTest.MusicPlay(GAME);
                info->startGame();
                if (info->GetStatus() == game || info->GetStatus() == end)
                    info->SetStatus(quit);
                else if (info->GetStatus() != quit) {
                    status = info->GetStatus();
                    info->ResetAll();
                    info->SetStatus(status);
                }
            }
        }
        info->soundTest.MusicStop();
    } catch (MyException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
