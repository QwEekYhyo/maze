#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <vector>
#include <utility>
#include <string>
#include <iostream>

class maze {
    public:
        maze(std::size_t size);
        void move(const std::pair<int, int>& position);
        std::pair<int, int> get_pos() const;
        friend std::ostream& operator<<(std::ostream& os, const maze& m);

    private:
        std::size_t m_size;
        std::vector<std::vector<int>> m_matrix;
        std::pair<int, int> m_pos;
        std::string m_message;

        void generate();
};

#endif
