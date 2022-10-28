#ifndef MAZE_GRAPH_HPP
#define MAZE_GRAPH_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

template<typename T>
class graph {
    public:
        graph() {}
        std::vector<T>& get_neighbor(const T& thing) {
            return map.at(thing);
        }
        std::unordered_map<T, std::vector<T>> map;
};

#endif
