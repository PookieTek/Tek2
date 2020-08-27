/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** npipe.hpp
*/

#ifndef _NPIPE_HPP_
#define _NPIPE_HPP_

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


class Npipe {
    public:
        Npipe() {};
        Npipe(const std::string &);
        ~Npipe();

        int getFd() {return _fd;};
        std::string GetName() {return _name;}
        void Send(const std::string &);
        std::string Receive();

        Npipe &operator<<(const std::string &);
        Npipe &operator>>(std::string &);
    private:
        int _fd;
        std::string _name;
};

#endif