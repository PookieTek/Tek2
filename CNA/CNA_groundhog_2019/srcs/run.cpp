/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** run
*/

#include "groundhog.hpp"
#include <string>
#include <sstream>

bool isFloat(std::string str) {
    size_t pos = str.find("\n");

    if (pos != std::string::npos)
        str = str.substr(0, pos);
    std::istringstream iss(str);
    float res;

    iss >> std::noskipws >> res;
    return iss.eof() && iss;
}

void Weather::DisplayData() {
    std::cout << "g=";
    GetIncrease();
    std::cout << "\t\tr=";
    GetEvolution();
    std::cout << "%\t\ts=";
    GetDeviation();
    if (IsSwitch())
        std::cout << "\t\ta switch occurs";
    std::cout << std::endl;
}

void Weather::RunProgram() {
    std::string keyword = "";

    std::cin >> keyword;
    while (keyword.compare("STOP") != 0 && keyword != "") {
        if (isFloat(keyword)) {
            Temp.push_back(atof(keyword.c_str()));
            DisplayData();
            Day++;
        } else {
            exit (84);
        }
        keyword = "";
        std::cin >> keyword;
    }
    if (Switch.size() > 0) {
        std::cout << "Global tendency switched " << Switch.size() << " times" << std::endl;
        DisplayWeirdValue();
    }
}
