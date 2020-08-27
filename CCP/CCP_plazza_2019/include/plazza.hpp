/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** plazza
*/

#ifndef PLAZZA_HPP_
#define PLAZZA_HPP_

#include "wording.hpp"
#include <iostream>
#include "kitchen.hpp"
#include <map>
#include <vector>

class Plazza {
    public:
        Plazza();
        ~Plazza();

        int Start(char **av);
        bool Init(char **av);
        int Run();
        int GetType(std::string);
        int GetSize(std::string);
        int GetNbrPizza(std::string);
        void ParseInput(std::string);
        bool AddCommand(std::vector<std::string>);
        void ReceiveData();

    private:
        double multiplier;
        int cooks;
        int restock;
        int running;
        std::vector<Commande> commands;
        std::vector<PizzaStruct_t> pizzalist;
        void *_kitchenWay;
};

#endif /* !PLAZZA_HPP_ */
