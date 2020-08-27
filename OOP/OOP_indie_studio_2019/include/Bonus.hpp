/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Bonus
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "Interface/IBonus.hpp"
#include <random>

class Bonus : public IBonus {
    public:
        Bonus(Types::BonusType, std::pair<int, int>);
        ~Bonus();

        std::pair<float, float> GetPosition();
        Types::Entity GetType();
        std::pair<int, int> GetPositionRelative();
        Types::BonusType GetBonusType();
        
        static int RandomBonus() {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_int_distribution<> distrib(0, 10);

            int result = distrib(gen);
            if (result >  10 - (CHANCE_BONUS / 10))
                return -1;
            return result;
        };

    protected:
    private:
        std::pair<int, int> position;
        Types::BonusType type;
};

#endif /* !BONUS_HPP_ */
