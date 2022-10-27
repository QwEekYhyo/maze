#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <vector>
#include <string>
#include <iostream>

struct coordinates {
    std::size_t x, y;
    friend bool operator==(const coordinates& a, const coordinates& b);
};

class maze {
    public:
        explicit maze(std::size_t size);
        void move(const coordinates& position);
        const coordinates& get_pos() const;
        int& at(coordinates c);
        const int& at(coordinates c) const;
        int& operator[](coordinates c);
        friend std::ostream& operator<<(std::ostream& os, const maze& m);

    private:
        std::size_t m_size;
        std::vector<std::vector<int>> m_matrix;
        coordinates m_pos;
        std::string m_message;

        void generate();
};

#endif
