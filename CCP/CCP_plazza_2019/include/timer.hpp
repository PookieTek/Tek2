/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>

class Timer {
    public:
        Timer();
        ~Timer();

        void Restart();
        bool IsLapsedTime(int);
    private:
        int timer;

};

#endif /* !TIMER_HPP_ */
