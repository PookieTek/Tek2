/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** npipe.cpp
*/

#include "plazza.hpp"

Npipe::Npipe(const std::string &name) {
    _name = name;
    mkfifo(name.c_str(), S_IRWXU);
    _fd = open(_name.c_str(), O_RDWR | O_CREAT | O_NONBLOCK);
}

Npipe::~Npipe() {}

std::string Npipe::Receive() {
    char buff[2];
    std::string msg = "";
    int size;
   
    while ((size = read(_fd, buff, 1)) > 0) {
        if (buff[0] == '\n')
            return msg;
        msg += buff[0];
    }
    return msg;
}

void Npipe::Send(const std::string &msg) {
    write (_fd, msg.c_str(), msg.size());
    write (_fd, "\n", 1);
}

Npipe& Npipe::operator<<(const std::string &msg) {
    Send (msg);
    return (*this);
}

Npipe& Npipe::operator>>(std::string &msg) {
    msg = Receive();
    return (*this);
}