#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <SFML/Graphics.hpp>

struct coordinates {
    int x, y;
    friend bool operator==(const coordinates& a, const coordinates& b);
    friend coordinates operator+(const coordinates& a, const coordinates& b);
    struct HashFunction {
        std::size_t operator()(const coordinates& c) const noexcept;
    };
};

class maze {
    public:
        explicit maze(std::size_t size);
        void move(const coordinates& position);
        const coordinates& get_pos() const;
        const std::size_t& size() const;
        void update();

        int& at(coordinates c);
        const int& at(coordinates c) const;
        int& operator[](coordinates c);

        void draw_on_window(sf::RenderWindow& window);

        friend std::ostream& operator<<(std::ostream& os, const maze& m);

    private:
        std::size_t m_size;
        std::vector<std::vector<int>> m_matrix;
        coordinates m_pos;
        std::string m_message;
        std::unordered_set<coordinates, coordinates::HashFunction> m_visited_cells;

        void generate();
        bool contains(const coordinates& c);
        bool has_neighbor(const coordinates& c);
        const coordinates random_neighbor(const coordinates& c);
};

#endif
