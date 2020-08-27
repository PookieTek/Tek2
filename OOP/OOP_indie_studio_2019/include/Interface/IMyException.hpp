/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** IError.hpp
*/

#ifndef _IMYEXCEPTION_HPP_
#define _IMYEXCEPTION_HPP_

#include <iostream>
#ifdef _WIN32
#include <string>
#endif
class IMyException {
    public:
        virtual ~IMyException() {};

        virtual std::string what() = 0;
};

#endif