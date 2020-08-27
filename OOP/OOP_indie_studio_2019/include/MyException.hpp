/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Error.hpp
*/

#ifndef _MYEXCEPTION_HPP_
#define _MYEXCEPTION_HPP_

#include "Interface/IMyException.hpp"

class MyException : public IMyException {
    public:
        MyException(std::string);
        ~MyException() {};

        std::string what();

    private:
        std::string err;
};

#endif