/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** cook
*/

#include "plazza.hpp"

Cooks::Cooks(double mult, int max) : multiplier(mult), maxcook(max) {
    closing = false;
    for (int i = 0; i < max; i++) {
        threads.push_back(std::thread(&Cooks::run, this));
    }
    inwork = 0;
};

Cooks::~Cooks() {
    closing = true;
    conditionQueue.notify_all();
    for (auto &thread : threads) {
        if (thread.joinable())
            thread.join();
    }
};

bool Cooks::addPizza(Commande &command) {
    std::lock_guard<std::mutex> lock(mutex);

    todo.push(command);
    conditionQueue.notify_one();
    return true;
}

std::queue<Commande> Cooks::getDone() {
    std::queue<Commande> tmp;

    while (!done.empty()) {
        tmp.push(done.front());
        done.pop();
    }
    return tmp;
}

int Cooks::getWork() { return inwork; }

void Cooks::run() {
    while (!closing) {
        Commande request;
        {
            std::unique_lock<std::mutex> lock(mutex);
            conditionQueue.wait(lock, [&]{
                return !todo.empty() || closing;
            });
            request = todo.front();
            todo.pop();
        }
        CookIt(request);
    }
}

void Cooks::CookIt(Commande request) {
    int timeToSleep = Tools::GetCookTime(request.type) * multiplier;
    
    inwork++;
    std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));
    if (Tools::Pack(request).size() > 0)
        done.push(request);
    inwork--;
}