/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** main.cpp
*/

#include "groundhog.hpp"
#include <string.h>
#include <stdlib.h>

int DisplayUsage(char *str)
{
    std::cout << "SYNOPSIS\n\t./groundhog period\n\nDESCRIPTION\n\tperiod\t\tthe number of days defining a period" << std::endl;
    if (str != NULL)
        return (0);
    return (84);
}

int main(int ac, char **av) {
    int arg = 0;

    if (ac != 2 || strcmp(av[1], "-h") == 0)
        return (DisplayUsage(av[1]));
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (!isdigit(av[1][i]))
            arg = -1;
    }
    if (arg != -1)
        arg = atoi(av[1]);
    if (arg <= 0) {
        std::cerr << "Invalid Input" << std::endl;
        return 84;
    }
    Weather ground(arg);
    ground.RunProgram();
    return 0;
}
