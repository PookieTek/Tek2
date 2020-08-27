/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <vector>
#include <iostream>

enum PizzaIngredient {
    Doe = 1,
    Tomato = 2,
    Gruyere = 3,
    Ham = 4,
    Mushroom = 5,
    Steak = 6,
    Eggplant = 7,
    GoatCheese = 8,
    ChiefLove = 9
};

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

typedef struct PizzaStruct_s
{
    PizzaType type;
    std::string name;
    std::vector<PizzaIngredient> ingredient;
    int time;
} PizzaStruct_t;

class Pizza {
    public:
        Pizza();
        ~Pizza();
        std::vector<PizzaStruct_t> GetPizzaList();
        void SetTimeMultiplier(float);
    private:
        std::vector<PizzaStruct_t> pizza;
};

#endif /* !PIZZA_HPP_ */