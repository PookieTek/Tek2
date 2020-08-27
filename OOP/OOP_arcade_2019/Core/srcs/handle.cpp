/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** handle
*/

#include "core.hpp"

HandleLib::HandleLib() {};
HandleLib::~HandleLib() {};

IGraphicalLib *HandleLib::GetGraph(std::string lib) {
    void *handle;
    IGraphicalLib *(*func)();

    try {
        if ((handle = dlopen(lib.c_str(), RTLD_LAZY)) == NULL || (*(void **)(&func) = dlsym(handle, "creatorGraph")) == NULL)
            throw std::string(dlerror());
    }
    catch (std::string const &error) {
        std::cerr << error << std::endl;
        return NULL;
    }
    return func();
}

IGameLib *HandleLib::GetGame(std::string lib) {
    void *handle;
    IGameLib *(*func)();    

    try {
        if ((handle = dlopen(lib.c_str(), RTLD_LAZY)) == NULL || (*(void **)(&func) = dlsym(handle, "creatorGame")) == NULL)
            throw std::string(dlerror());
    }
    catch (std::string const &error) {
        std::cerr << error << std::endl;
        return NULL;
    }
    return func();
}

HandleTime::HandleTime() {timer = clock();}

HandleTime::~HandleTime() {}

void HandleTime::Restart() {timer = clock();}

bool HandleTime::TimeLapsed(int comparator) { return (clock() - timer >= comparator);}