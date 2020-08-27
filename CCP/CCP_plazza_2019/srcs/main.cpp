/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#include "plazza.hpp"
#include <cstring>

int main(int ac, char **av) {
    Plazza Reception;
    
    if (ac == 2 && strcmp(av[1], "-h") == 0)
        std::cout << USAGE << std::endl;
    else if (ac != 4) {
        std::cerr << ERR_INPUT << std::endl;
        return 84;
    } else
        return Reception.Start(av);
    return 0;
}