/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** structInfo
*/

#ifndef STRUCTINFO_HPP_
#define STRUCTINFO_HPP_
#include <map>
#include <vector>
#include <iostream>

struct MenuData {
    std::map<std::string, std::string>data; // graphical / game / pseudo
    std::vector<int> menuX;
    std::vector<int> menuY;
    int index;
    bool isPseudo;
    bool isStart;
    bool isEnter;
};

#endif /* !STRUCTINFO_HPP_ */
