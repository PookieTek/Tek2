/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** process.cpp
*/

#include "plazza.hpp"
#include <sstream>
#include <unistd.h>
#include <fstream>

Process::Process(int max, float cookTime, int refuelTime) {
    _nbkitchen = 0;
    _pid = 0;
    _max = max;
    _cookTime = cookTime;
    _refuelTime = refuelTime;
    std::ofstream log("plazza.log", std::ofstream::trunc);
    log.close();   
}

Process::Process(const std::map<std::string, Npipe> &to_kitchen, const std::map<std::string, Npipe> &to_reception, pid_t pid, int max, float cookTime, int refuelTime) {
    _nbkitchen = 1;
    _toReception = to_reception;
    _toKitchen = to_kitchen;
    _pid = pid;
    _max = max;
    _cookTime = cookTime;
    _refuelTime = refuelTime;
}

Process::~Process() {
    unlink(_toKitchen["commande"].GetName().c_str());
    unlink(_toKitchen["status"].GetName().c_str());
    unlink(_toKitchen["getnbr"].GetName().c_str());
    unlink(_toKitchen["close"].GetName().c_str());
    unlink(_toReception["commande"].GetName().c_str());
    unlink(_toReception["status"].GetName().c_str());
    unlink(_toReception["getnbr"].GetName().c_str());
    unlink(_toReception["close"].GetName().c_str());
}

void Process::CreateKitchen(int max, float cookTime, int refuelTime) {
    std::stringstream sstream1;
    std::stringstream sstream2;
    std::stringstream sstream3;
    std::stringstream sstream4;
    std::stringstream sstream5;
    std::stringstream sstream6;
    std::stringstream sstream7;
    std::stringstream sstream8;
    Kitchen *nextkitchen;

    sstream1 << "Kcommande" << _nbkitchen;
    sstream2 << "Rcommande" << _nbkitchen;

    sstream3 << "Kstatus" << _nbkitchen;
    sstream4 << "Rstatus" << _nbkitchen;
    
    sstream5 << "Kgetnbr" << _nbkitchen;
    sstream6<< "Rgetnbr" << _nbkitchen;
    
    sstream7 << "Kclose" << _nbkitchen;
    sstream8 << "Rclose" << _nbkitchen;
    
    _toKitchen = {{"commande", Npipe(sstream1.str())}, {"status", Npipe(sstream3.str())}, {"getnbr", Npipe(sstream5.str())}, {"close", Npipe(sstream7.str())}};
    _toReception = {{"commande", Npipe(sstream2.str())}, {"status", Npipe(sstream4.str())}, {"getnbr", Npipe(sstream6.str())}, {"close", Npipe(sstream8.str())}};
    _nbkitchen++;
    pid_t pid = fork();

    if (pid == 0) {
        nextkitchen = new Kitchen(_toKitchen, _toReception, max, cookTime, refuelTime);
        nextkitchen->Run();
        exit (1);
    } else
        _kitchens.push_back(Process(_toKitchen, _toReception, pid, max, cookTime, refuelTime));
}

void Process::AddPizza(Commande command) {
    int actualnbr = 0;
    int nbpizza = -1;
    int index = 0;

    if (_kitchens.size() == 0) {
        std::cout << "Create Kitchen" << std::endl;
        CreateKitchen(_max, _cookTime, _refuelTime);
    }
    for (int a = 0; a < _kitchens.size(); a++) {
        if ((actualnbr = _kitchens.at(a).GetPizzaNbr()) < nbpizza || nbpizza == -1) {
            index = a;
            nbpizza = actualnbr;
        }
    }
    if (nbpizza >= (_max * 2)) {
        std::cout << "Create Kitchen" << std::endl;
        CreateKitchen(_max, _cookTime, _refuelTime);
        index = _kitchens.size() - 1;
    }
    SendCommand(_kitchens.at(index), command);
}

int Process::GetPizzaNbr() {
    std::string message = "";
    int number = 0;

    _toKitchen["getnbr"] << "ask";
    while (message.size() == 0) {
        _toReception["getnbr"] >> message;
    }
    if (message.size() > 0) {
        number = std::stoi(message);
    } 
    return (number);
}

void Process::AskStatus() {
    for (int i = 0; i < _kitchens.size(); i++)
        _kitchens.at(i)._toKitchen["status"] << "ask";
}

void Process::SendCommand(Process kitchenWay, Commande command) {
    kitchenWay._toKitchen["commande"] << Tools::Pack(command);
}

std::string Process::GetData() {
    std::string message;
    std::string com;
    std::string status;
    std::string close;
    std::ofstream log("plazza.log", std::ofstream::out | std::ofstream::app);
    std::vector<std::string> statformat;

    int toerase = -1;

    for (int i = 0; i < _kitchens.size(); i++) {
        _kitchens.at(i)._toReception["commande"] >> com;
        _kitchens.at(i)._toReception["close"] >> close;
        _kitchens.at(i)._toReception["status"] >> status;
        if (com.size() > 0) {
            message.append("Pizza Cooked : " + com + "\n");
            log << "Pizza Cooked : " + com + "\n";
        }
        if (close.size() > 0) {
            message.append("Kitchen closed\n");
            toerase = i;
        }
        if (status.size() > 0) {
            statformat = Tools::Parser(status, '/');
            for (int j = 0; j < statformat.size(); j++)
                message.append(statformat.at(j)).append("\n");
        }
    }
    if (toerase != -1)
        _kitchens.erase(_kitchens.begin() + toerase);
    log.close();
    return message;
}