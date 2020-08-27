/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Timer
*/

#include <iostream>
#include <thread>

#include "Timer.hpp"

Timer::Timer()
{
    clock = std::chrono::system_clock::now();
    isPause = false;
    save = 0;
}

Timer::~Timer() {}

int Timer::GetTimeLapsed() {
    if (isPause)
        return save;
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    return (std::chrono::duration_cast<std::chrono::milliseconds>(now - clock).count() + save);
}

void Timer::Restart() {
    isPause = false;
    clock = std::chrono::system_clock::now();
    save = 0;
}

void Timer::Pause() {
    if (isPause)
        return;
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    isPause = true;
    save += (std::chrono::duration_cast<std::chrono::milliseconds>(now - clock).count());
}

void Timer::Resume() {
    clock = std::chrono::system_clock::now();
    isPause = false;
}

bool Timer::IsBreak() { return isPause; }