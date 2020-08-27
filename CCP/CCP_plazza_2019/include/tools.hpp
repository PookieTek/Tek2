/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <vector>
#include <iostream>
#include "command.hpp"

namespace Tools {
    bool IsInt(char *str);
    std::vector<std::string> Parser(std::string str, char c);
    int CmpCase(std::string str1, std::string str2);
    int GetCookTime(PizzaType type);
    Commande Unpack(std::string);
    std::string Pack(Commande);
    std::string GetInput();
    std::string GetIngName(PizzaIngredient);
};

#endif /* !TOOLS_HPP_ */