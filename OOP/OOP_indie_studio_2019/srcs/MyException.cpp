/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2019
** File description:
** Error.cpp
*/

#include "MyException.hpp"

MyException::MyException(std::string _err) : err(_err) {}

std::string MyException::what() { return err; }