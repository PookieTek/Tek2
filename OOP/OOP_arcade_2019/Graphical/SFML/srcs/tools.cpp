/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** tools
*/

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include "sfml.hpp"

struct ScoresReg {
    std::string name;
    std::string game;
    int score;
};

std::string parseLib(std::string str) {
    std::string delim1 = "_";
    std::string ret = "- ";
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delim1)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delim1.length());
    }
    str.erase(str.size() - 3, str.size());
    ret.append(str);
    return ret;
}

std::vector<std::string> ReadScores() {
    std::vector<std::string> tmpScores;
    std::vector<std::string> Scores;
    std::vector<ScoresReg> data;
    std::ifstream file("./games/.scores");
    std::string line;
    std::string sub;
    int lastScore = -1;
    int index = 0;

    while (std::getline(file, line)) {
        std::istringstream tok(line);
        while (std::getline(tok, sub, ';'))
            tmpScores.push_back(sub);
        ScoresReg tmp = {tmpScores.at(1), tmpScores.at(0), atoi(tmpScores.at(2).c_str())};
        data.push_back(tmp);
        tmpScores.clear();
    }
    while (data.size() > 0) {
        for (int i = 0; i < data.size(); i++) {
            if (data.at(i).score > lastScore) {
                lastScore = data.at(i).score;
                index = i;
            }
        }
        Scores.push_back(data.at(index).game + " : " + data.at(index).name + " " + std::to_string(data.at(index).score));
        data.erase(data.begin() + index);
        lastScore = -1;
    }
    return Scores;
}