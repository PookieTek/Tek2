/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** process.hpp
*/


#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <sys/types.h>
#include <vector>
#include <map>
#include <fstream>
#include "npipe.hpp"
#include "timer.hpp"
#include "tools.hpp"

class Process {
    public:
        Process(int, float, int);
        Process(const std::map<std::string, Npipe> &, const std::map<std::string, Npipe> &, pid_t, int, float, int);
        ~Process();
        int GetPizzaNbr();
        void AddPizza(Commande);
        void SendCommand(Process, Commande);
        void CreateKitchen(int, float, int);
        std::string GetData();
        void AskStatus();

    private:

        std::vector<Process> _kitchens;
        pid_t _pid;
        int _nbkitchen;
        int _max;
        int _refuelTime;
        float _cookTime;
        std::map<std::string, Npipe> _toKitchen;
        std::map<std::string, Npipe> _toReception;
};

#endif