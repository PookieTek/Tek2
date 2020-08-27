/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <chrono>

class Timer {
    public:
        Timer();
        ~Timer();

        void Restart();
        int GetTimeLapsed();
        void Pause();
        void Resume();
        bool IsBreak();

    protected:
    private:
        std::chrono::system_clock::time_point clock;
        int save;
        bool isPause;
};

#endif /* !TIMER_HPP_ */
