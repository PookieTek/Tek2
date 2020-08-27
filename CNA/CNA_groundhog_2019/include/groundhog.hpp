/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** groundhog
*/

#ifndef GROUNDHOG_HPP_
#define GROUNDHOG_HPP_

#include <iostream>
#include <vector>
#include <algorithm>

class Weather
{
    public:
        Weather(int);
        ~Weather();
    
        void RunProgram();
        void DisplayData();
        void GetIncrease();
        void GetEvolution();
        void GetDeviation();
        bool IsSwitch();
        void DisplayWeirdValue();
    
    private:
        int Period;
        std::vector<float> Temp;
        int Day;
        std::vector<int> Switch;
        int IsPos;
        bool alert;
};


#endif /* !GROUNDHOG_HPP_ */
