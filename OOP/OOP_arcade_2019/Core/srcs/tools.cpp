/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#include "core.hpp"
#include <fstream>

void Core::SaveScore(std::string pseudo, int score, std::string game) {
    std::string line = game + ";" + pseudo + ";" + std::to_string(score) + "\n";
    std::ofstream file("./games/.scores", std::ios_base::app | std::ios_base::out);

    file << line;
    file.close();
}

