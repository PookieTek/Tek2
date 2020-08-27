/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Tools
*/

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <vector>
#include <memory>
#include <filesystem>

namespace Tools {
    template<typename T, typename U>
    std::vector<std::shared_ptr<T>> ExtractList(std::vector<std::shared_ptr<U>> list) {
        std::vector<std::shared_ptr<T>> tmp;
        for (int i = 0; i < list.size(); i++)
            tmp.push_back(std::static_pointer_cast<T>(list.at(i)));
        return tmp;
    }
};

#endif /* !TOOLS_HPP_ */
