/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** reception
*/

#include "plazza.hpp"
#include <exception>

Plazza::Plazza() {
    running = 0;
    Pizza pizza;
    pizzalist = pizza.GetPizzaList();
}

Plazza::~Plazza() {}

bool Plazza::Init(char **args) {
    try {
        multiplier = atof(args[1]);
        cooks = atoi(args[2]);
        restock = atoi(args[3]);
        if (multiplier <= 0 || cooks <= 0 || restock <= 0)
            throw std::exception();
    }
    catch (...) {
        std::cerr << ERR_INPUT << std::endl;
        return false;
    }
    return true;
}

int Plazza::GetType(std::string type) {
    for (int a = 0; a < pizzalist.size(); a++) {
        if (Tools::CmpCase(type, pizzalist.at(a).name) == 0)
            return (pizzalist.at(a).type);
    }
    return (0);
}

int Plazza::GetSize(std::string size) {
    if (Tools::CmpCase(size, "S") == 0)
        return (1);
    if (Tools::CmpCase(size, "M") == 0)
        return (2);
    if (Tools::CmpCase(size, "L") == 0)
        return (4);
    if (Tools::CmpCase(size, "XL") == 0)
        return (8);
    if (Tools::CmpCase(size, "XXL") == 0)
        return (16);
    return (0);
}

int Plazza::GetNbrPizza(std::string nb)
{
    if (nb.size() <= 1 || (nb[0] != 'X' && nb[0] != 'x'))
        return (0);
    nb.erase(0, 1);
    for (int a = 0; a < nb.size(); a++) {
        if (nb[a] < '0' || nb[a] > '9')
            return (0);
    }
    return (std::stoi(nb));
}

bool Plazza::AddCommand(std::vector<std::string> command)
{
    int type = GetType(command.at(0));
    int size = GetSize(command.at(1));
    int nb = GetNbrPizza(command.at(2));

    if (type == 0 || size == 0 || nb == 0)
        return (false);
    for (int a = 0; a < nb; a++)
        commands.push_back({static_cast<PizzaType>(type), static_cast<PizzaSize>(size)});
    return true;
}

void Plazza::ParseInput(std::string input) {
    std::vector<std::string> line = Tools::Parser(input, ';');
    std::vector<std::string> command;

    if (input.compare("end") == 0) {
            running = 1;
            return;
    }
    for (int a = 0; a < line.size(); a++) {
        command = Tools::Parser(line.at(a), ' ');
        if ((command.size() != 3 || AddCommand(command) == false) && input.compare("status") != 0)
            std::cerr << ERR_SHINPUT << std::endl;
        command.clear();
    }
}

void Plazza::ReceiveData() {
    std::string message = static_cast<Process *>(_kitchenWay)->GetData();
    if (message.size() > 0)
        std::cout << message;
}

int Plazza::Run() {

    std::string input;

    while (running == 0) {
        input = Tools::GetInput();
        ParseInput(input);
        if (input.compare("status") == 0)
            static_cast<Process *>(_kitchenWay)->AskStatus();
        input.clear();
        while (commands.size() > 0) {
            static_cast<Process *>(_kitchenWay)->AddPizza(commands.at(0));
            commands.erase(commands.begin());
        }
        ReceiveData();
    }
    if (running == -1) {
        std::cerr << ERR_SHINPUT << std::endl;
        return 84;
    }
    return 0;
}

int Plazza::Start(char **args) {
    if (!Init(args))
        return 84;
    _kitchenWay = new Process(cooks, multiplier, restock);
    return Run();
}