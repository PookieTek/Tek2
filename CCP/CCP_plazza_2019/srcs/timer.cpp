/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** timer
*/

#include "timer.hpp"
#include <iostream>

Timer::Timer() { 
    timer = clock();
}
Timer::~Timer() {};

void Timer::Restart() {
    timer = clock();
}

bool Timer::IsLapsedTime(int ms) {
    return (((1000.0 * (clock() - timer)) / CLOCKS_PER_SEC) >= ms);
}