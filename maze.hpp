#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <vector>
#include <utility>

class maze {
    public:
        maze();
        void print() const;
        void move(const std::pair<int, int>& position);

    private:
        std::size_t m_size;
        std::vector<std::vector<int>> m_matrix;
        std::pair<int, int> m_pos;

        void generate();
        std::pair<int, int> get_pos() const;
}

#endif
