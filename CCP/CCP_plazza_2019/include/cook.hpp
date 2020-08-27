/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include "tools.hpp"
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

class Cooks {
    public:
        Cooks(double, int);
        ~Cooks();

        bool addPizza(Commande &);
        void run();
        void CookIt(Commande request);
        std::queue<Commande> getDone();
        int getWork();

    private:
        double multiplier;
        int maxcook;
        int inwork;
        bool closing;
        std::condition_variable conditionQueue;
        std::vector<std::thread> threads;
        std::mutex mutex;
        std::queue<Commande> todo;
        std::queue<Commande> done;
};

#endif /* !COOK_HPP_ */
