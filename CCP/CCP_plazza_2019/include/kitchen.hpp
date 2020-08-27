
/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <vector>
#include <map>
#include "process.hpp"
#include "cook.hpp"
#include <queue>

class Kitchen {
    public:
        Kitchen(std::map<std::string, Npipe>, std::map<std::string, Npipe>, int, float, int);
        ~Kitchen();

        void Refuel();
        void Run();
        void RetrieveQueue(std::queue<Commande>);
        bool IsEnoughIngredients(Commande);
        void ConsumeIngredient(Commande);
        void ParseReceive(int);

    private:
        std::map<std::string, Npipe> _in;
        std::map<std::string, Npipe> _out;
        int maxCooks;
        float cookTime;
        int refuelTime;
        std::map<PizzaIngredient, int> Ingredients;
        std::queue<Commande> commandes;
        Timer lifeTime;
        Timer refuelTimer;
        int PizzaWait;
        

    protected:
        std::queue<Commande> PizzaDone;
};




#endif /* !KITCHEN_HPP_ */
