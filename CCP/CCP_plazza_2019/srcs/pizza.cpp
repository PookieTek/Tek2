/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** pizza.cpp
*/

#include "pizza.hpp"

Pizza::Pizza() {
    pizza.push_back({PizzaType::Regina, "REGINA", {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Ham, PizzaIngredient::Mushroom}, 2000});
    pizza.push_back({PizzaType::Margarita, "MARGARITA", {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere}, 1000});
    pizza.push_back({PizzaType::Americana, "AMERICANA", {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Steak}, 2000});
    pizza.push_back({PizzaType::Fantasia, "FANTASIA", {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Eggplant, PizzaIngredient::GoatCheese, PizzaIngredient::ChiefLove}, 4000});
}

Pizza::~Pizza() {}

std::vector<PizzaStruct_t> Pizza::GetPizzaList() { return pizza; }

void Pizza::SetTimeMultiplier(float multiplier) {
    for (int a = 0; a < 4; a++)
        pizza.at(a).time = pizza.at(a).time * multiplier;
}
