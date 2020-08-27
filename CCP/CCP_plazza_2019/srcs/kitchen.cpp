/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** kitchen
*/

#include "plazza.hpp"
#include <stdio.h>
#include <unistd.h>

Kitchen::Kitchen(std::map<std::string, Npipe> in, std::map<std::string, Npipe> out, int _max, float _cookTime, int _refuelTime) : _in(in), _out(out), maxCooks(_max), cookTime(_cookTime), refuelTime(_refuelTime) {
    for (int ing = PizzaIngredient::Doe; ing <= PizzaIngredient::ChiefLove; ing++)
            Ingredients[static_cast<PizzaIngredient>(ing)] = 5;
}


Kitchen::~Kitchen() {
    close(_in["commande"].getFd());
    close(_out["commande"].getFd());
    close(_in["status"].getFd());
    close(_out["status"].getFd());
    close(_in["getnbr"].getFd());
    close(_out["getnbr"].getFd());
    close(_in["close"].getFd());
    close(_out["close"].getFd());
};

void Kitchen::Refuel() {
    if (refuelTimer.IsLapsedTime(refuelTime)) {
        for (int ing = PizzaIngredient::Doe; ing <= PizzaIngredient::ChiefLove; ing++) {
            Ingredients[static_cast<PizzaIngredient>(ing)]++;
        }
        refuelTimer.Restart();
    }
}

void Kitchen::RetrieveQueue(std::queue<Commande> tmp) {
    while (!tmp.empty()) {
        PizzaDone.push(tmp.front());
        tmp.pop();
    }
}

bool Kitchen::IsEnoughIngredients(Commande pizza) {
    Pizza info;
    std::vector<PizzaStruct_t> list = info.GetPizzaList();

    for (int i = 0; i < list.size(); i++) {
        if (list.at(i).type = pizza.type) {
            for (int j = 0; j < list.at(i).ingredient.size(); j++) {
                if (Ingredients[list.at(i).ingredient.at(j)] < 1)
                    return false;
            }
        }
    }
    return true;
}

void Kitchen::ConsumeIngredient(Commande pizza) {
     Pizza info;
    std::vector<PizzaStruct_t> list = info.GetPizzaList();

    for (int i = 0; i < list.size(); i++)
        if (list.at(i).type = pizza.type) {
            for (int j = 0; j < list.at(i).ingredient.size(); j++) {
                Ingredients[list.at(i).ingredient.at(j)]--;
            }
            break;
        }
}

void Kitchen::ParseReceive(int work) {
    std::string com;
    std::string num;
    std::string stat;
    std::string format;

    _in["commande"] >> com;
    _in["getnbr"] >> num;
    _in["status"] >> stat;
    if (com.size() > 0) {
        commandes.push(Tools::Unpack(com));
    }
    if (num.compare("ask") == 0)
        _out["getnbr"] << (std::to_string(PizzaWait + commandes.size()));
    if (stat.compare("ask") == 0) {
        format = "Cooks working : " + std::to_string(work) + "/";
        for (int ing = PizzaIngredient::Doe; ing <= PizzaIngredient::ChiefLove; ing++) {
            format.append(Tools::GetIngName(static_cast<PizzaIngredient>(ing))).append(" : ").append(std::to_string(Ingredients[static_cast<PizzaIngredient>(ing)])).append("/");
        }
        _out["status"] << format;
    }
}

void Kitchen::Run() {
    Cooks pool(cookTime, maxCooks);
    std::string Message;
    Commande tmp;

    while (!lifeTime.IsLapsedTime(5000)) {
        if (!commandes.empty() || PizzaWait > 0)
            lifeTime.Restart();
        if (PizzaWait > 0)
            RetrieveQueue(pool.getDone());
        while (!PizzaDone.empty()) {
            Message = "";
            Message.append(Tools::Pack(PizzaDone.front()));
            _out["commande"] << Message;
            Message.clear();
            PizzaDone.pop();
            PizzaWait--;
        }
        ParseReceive(pool.getWork());
        Refuel();
        if (!commandes.empty() && IsEnoughIngredients(commandes.front())) {
            pool.addPizza(commandes.front());
            ConsumeIngredient(commandes.front());
            commandes.pop();
            PizzaWait++;
        }
    }
    _out["close"] << "close";
}