/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** groundhog
*/

#include "groundhog.hpp"
#include <cmath>
#include <iomanip>

Weather::Weather(int _period) : Period(_period)
{
    Day = 1;
}

Weather::~Weather()
{
    Temp.clear();
}

void Weather::GetIncrease() {
    float calc;
    float last;

    if (Period >= Day) {
        std::cout << "nan";
        return;
    }
    last = Temp.at(Day - Period - 1);
    for (int i = 0; i < Period; i++) {
        calc += (last < Temp.at(Day - Period + i)) ? Temp.at(Day - Period + i) - last : 0;
        last = Temp.at(Day - Period + i);
    }
    calc /= Period;
    std::cout << std::fixed << std::setprecision(2) << calc;
}

void Weather::GetEvolution() {
    float result = 0.00;

    if (Period >= Day) {
        std::cout << "nan";
        return;
    }
    result = Temp.at(Temp.size() - 1) / Temp.at(Temp.size() - 1 - Period);
    if (result < 1)
        std::cout << "-";
    if (IsPos == -1) {
        if (result < 1)
            IsPos = 0;
        else
            IsPos = 1;
    }
    if (result < 1 && IsPos == 1)
        alert = true;
    else if (result > 1 && IsPos == 0)
        alert = true;
    IsPos = (result < 1) ? 0 : 1;
    result = (result < 1) ? (1 - result) * 100 : (result - 1) * 100;
    std::cout << std::fixed << std::setprecision(0) << result;
}


void Weather::GetDeviation() {
    float result = 0.0;
    float moy = 0.0;

    if (Period > Day) {
        std::cout << "nan";
        return;
    }
    for (int i = 0; i < Period; i++)
        moy += Temp.at(Day - Period + i);
    moy /= Period;
    for (int i = 0; i < Period; i++)
        result += std::pow(Temp.at(Day - Period + i) - moy, 2);
    result /= Period;
    std::cout << std::fixed << std::setprecision(2) << sqrt(result);
}


bool Weather::IsSwitch() {
    if (alert) {
        alert = false;
        Switch.push_back(Day);
        return true;
    }
    return false;
}

void Weather::DisplayWeirdValue() {
    std::vector<float> weird;

    std::cout << Switch.size() << " weirdest values are [";
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < Switch.size(); i++)
        weird.push_back(Temp.at(Switch.at(i) - 1));
    std::sort(weird.begin(), weird.end());
    for (int i = 0; i < weird.size(); i++) {
        std::cout << weird.at(i);
        if (i < weird.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}