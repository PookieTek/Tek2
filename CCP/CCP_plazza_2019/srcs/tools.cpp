/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#include "tools.hpp"
#include "plazza.hpp"
#include <iomanip>
#include <chrono>
#include <future>

bool Tools::IsInt(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (!std::isdigit(str[i]))
            return false;
    return true;
}

std::string Tools::GetInput() {
    fd_set rfds;
    std::string msg;
    struct timeval tv;
    int ret;
    char buff[64];

    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1;
    ret = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);
    if (FD_ISSET(STDIN_FILENO, &rfds)) {
        if (fgets(buff, 64, stdin)) {
            msg = buff;
            msg.pop_back();
            return msg;
        }
    }
    return msg;
}

std::string Tools::GetIngName(PizzaIngredient ing) {
    std::string name;

    switch(ing) {
        case PizzaIngredient::Doe: { name = "Doe"; } break;
        case PizzaIngredient::Tomato: { name = "Tomato"; } break;
        case PizzaIngredient::Gruyere: { name = "Gruyere"; } break;
        case PizzaIngredient::Ham: { name = "Ham"; } break;
        case PizzaIngredient::Mushroom: { name = "Mushroom"; } break;
        case PizzaIngredient::Steak: { name = "Steak"; } break;
        case PizzaIngredient::Eggplant: { name = "Egg plant"; } break;
        case PizzaIngredient::GoatCheese: { name = "Goat Cheese"; } break;
        case PizzaIngredient::ChiefLove: { name = "Chief Love"; } break;
    }
    return name;
}

std::vector<std::string> Tools::Parser(std::string str, char c) {
    std::vector<std::string> tab;
    std::string tmp = "";

    for (int a = 0; a < str.size(); ) {
        for ( ; a < str.size() && str[a] != c; a++)
            tmp = tmp + str[a];
        if (tmp.size() > 0)
            tab.push_back(tmp);
        tmp = "";
        for ( ; a < str.size() && str[a] == c; a++);
    }
    return (tab);
}

int Tools::CmpCase(std::string str1, std::string str2) {
    char c1, c2;

    if (str1.size() != str2.size())
        return (-1);
    for (int a = 0; a < str1.size(); a++) {
        c1 = (str1[a] >= 'a' && str1[a] <= 'z') ? str1[a] - 32 : str1[a];
        c2 = (str2[a] >= 'a' && str1[a] <= 'z') ? str2[a] - 32 : str2[a];
        if (c1 != c2)
            return (-1);
    }
    return (0);
}

int Tools::GetCookTime(PizzaType type) {
    if (type == PizzaType::Regina || type == PizzaType::Americana )
        return (2000);
    else if (type == PizzaType::Margarita)
        return (1000);
    return (4000);
}

Commande Tools::Unpack(std::string str) {
    std::vector<std::string> pars = Parser(str, ' ');
    Commande tmp;

    if (pars.size() != 2)
        return tmp;
    if (pars.at(0).compare("margarita") == 0)
        tmp.type = PizzaType::Margarita;
    if (pars.at(0).compare("regina") == 0)
        tmp.type = PizzaType::Regina;
    if (pars.at(0).compare("americana") == 0)
        tmp.type = PizzaType::Americana;
    if (pars.at(0).compare("fantasia") == 0)
        tmp.type = PizzaType::Fantasia;

    if (pars.at(1).compare("s") == 0)
        tmp.size = PizzaSize::S;
    if (pars.at(1).compare("m") == 0)
        tmp.size = PizzaSize::M;
    if (pars.at(1).compare("l") == 0)
        tmp.size = PizzaSize::L;
    if (pars.at(1).compare("xl") == 0)
        tmp.size = PizzaSize::XL;
    if (pars.at(1).compare("xxl") == 0)
        tmp.size = PizzaSize::XXL;
    return tmp;
}



std::string Tools::Pack(Commande commande) {
    std::string packMessage = "";

    if (commande.type == PizzaType::Regina)
        packMessage.append("regina ");
    if (commande.type == PizzaType::Margarita)
        packMessage.append("margarita ");
    if (commande.type == PizzaType::Americana)
        packMessage.append("americana ");
    if (commande.type == PizzaType::Fantasia)
        packMessage.append("fantasia ");        
    
    if (commande.size == PizzaSize::S)
        packMessage.append("s");
    if (commande.size == PizzaSize::M)
        packMessage.append("m");
    if (commande.size == PizzaSize::L)
        packMessage.append("l");
    if (commande.size == PizzaSize::XL)
        packMessage.append("xl");
    if (commande.size == PizzaSize::XXL)
        packMessage.append("xxl");
    return packMessage;
}