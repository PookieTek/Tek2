/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#include "core.hpp"

int Usage()
{
    std::cout << "USAGE:\n\t./arcade lib_arcade_$libraryname.so\n\tUsing Libraries in ./lib folder." << std::endl;
    return 84;
}

int main(int ac, char **av)
{
    Core core;

    if (ac != 2)
        return Usage();
    return core.StartArcade(av[1]);
}