#include <maze.hpp>
#include <random>
#include <deque>

int rand_int(int a, int b) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a,b);

    return dist6(rng);
}

std::size_t coordinates::HashFunction::operator()(const coordinates& c) const noexcept {
    size_t xHash = std::hash<int>()(c.x);
    size_t yHash = std::hash<int>()(c.y) << 1;
    return xHash ^ yHash;
}

maze::maze(std::size_t size) {
    m_size = (2 * size) + 1;
    generate();
}

void maze::generate() {
    std::vector<coordinates> valid_ends;

    std::deque<coordinates> stack;
    coordinates current;
    coordinates next;
    coordinates wall;

    // initialising matrix of maze with 0s everywhere
    m_matrix = std::vector<std::vector<int>> (m_size, std::vector<int> (m_size, 0));

    // picking a random starting position on the top line
    int random = 2 * rand_int(0, m_size/2);
    m_pos = {random, 0};

    // #### algorithm ####
    // starts from starting position
    m_visited_cells.insert(m_pos);
    stack.push_back(m_pos);
    //while the stack is not empty
    while (! stack.empty()) {
        // takes last cell in stack as current cell
        current = stack.back();
        stack.pop_back();
        // if the current cell is a 0 then makes it a 1
        if (!at(current)) {
            at(current) = 1;
        }
        // if current cell has at least 1 unvisited neighbor
        if (has_neighbor(current)) {
            // pushes the current cell to the stack
            stack.push_back(current);
            // chooses a random neighbor
            next = random_neighbor(current);
            // gets rid of the wall between the current cell and the choosen one
            // (aka makes a path between the two)
            wall = next + current;
            wall = {wall.x / 2, wall.y / 2};
            at(wall) = 1;
            // then marks the choosen cell as visited and pushes it to the stack
            m_visited_cells.insert(next);
            stack.push_back(next);
        }
    }

    // putting all of the dead ends in a set
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            coordinates c = {j, i};
            if (at(c) && is_dead_end(c)) {
                m_ends.insert(c);
            }
        }
    }

    // marking all ends positioned 2 third of the size of the maze as valids
    for (coordinates c : m_ends) {
        if (c.y >= 2 * m_size / 3) {
            valid_ends.push_back(c);
        }
    }
    // picking a random valid end as THE end
    if (!valid_ends.empty()) {
        random = rand_int(0, valid_ends.size());
        m_end = valid_ends.at(random);
    }
}

bool maze::contains(const coordinates& c) {
    return (c.x < m_size && c.x >= 0 && c.y < m_size && c.y >= 0);
}

bool maze::is_dead_end(const coordinates& pos) {
    int count = 0;
    std::vector<coordinates> possible_moves = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    for (coordinates c : possible_moves) {
        c = c + pos;
        if (contains(c) && at(c)) {
            count++;
        }
    }

    return count == 1;
}

bool maze::has_neighbor(const coordinates& pos) {
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    coordinates temp;

    for (coordinates& c : possible_moves) {
        temp = c + pos;
        if (contains(temp) && ! m_visited_cells.contains(temp)) {
            return true;
        }
    }
    return false;
}

const coordinates maze::random_neighbor(const coordinates& pos) {
    int random;
    std::vector<coordinates> valid_neighbors;
    std::vector<coordinates> possible_moves = {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    for (coordinates c : possible_moves) {
        c = c + pos;
        if (contains(c) && ! m_visited_cells.contains(c)) {
            valid_neighbors.push_back(c);
        }
    }

    random = rand_int(0, valid_neighbors.size() - 1);
    return valid_neighbors.at(random);
}

const coordinates& maze::get_pos() const {
    return m_pos;
}

const std::size_t& maze::size() const {
    return m_size;
}

void maze::move(const coordinates& pos) {
    coordinates temp = pos + m_pos;
    if (contains(temp) && at(temp)) {
        m_pos = temp;
    }
    else {
        m_message = "Couldn't move\n";
    }
    update();
}

int& maze::at(coordinates pos) {
    return m_matrix.at(pos.y).at(pos.x);
}

const int& maze::at(coordinates pos) const {
    return m_matrix.at(pos.y).at(pos.x);
}

int& maze::operator[](coordinates pos) {
    return at(pos);
}

void maze::update() {
    if (m_pos == m_end) {
        m_message = "You have reached the end !!";
        // call a win method ?
    }
    std::cout << (*this) << std::endl;
    m_message = '\n';
}

void maze::mark_cell() {
    m_marked_cells.insert(m_pos);
}

bool operator==(const coordinates& a, const coordinates& b) {
    return a.x == b.x && a.y == b.y;
}

coordinates operator+(const coordinates& a, const coordinates& b) {
    return {a.x + b.x, a.y + b.y};
}

void maze::draw_on_window(sf::RenderWindow& window) {
    float cell_size = static_cast<float>(window.getSize().y)/static_cast<float>(m_size);
    unsigned int offset = (window.getSize().x - m_size) / 4;
    std::vector<sf::RectangleShape> cells;
    std::size_t cell_count = 0;
    float x;
    float y;

    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            coordinates c = {j, i};
            if (at(c)) {
                x = (j * cell_size) + offset;
                y = i * cell_size;
                cells.push_back(sf::RectangleShape(sf::Vector2f(cell_size, cell_size)));
                if (get_pos() == c) {
                    cells.at(cell_count).setFillColor(sf::Color::Green);
                } else if (c == m_end) {
                    cells.at(cell_count).setFillColor(sf::Color::Red);
                } else if (m_marked_cells.contains(c)) {
                    cells.at(cell_count).setFillColor(sf::Color::Magenta);
                } else {
                    cells.at(cell_count).setFillColor(sf::Color::Blue);
                }
                cells.at(cell_count).setPosition(sf::Vector2f(x, y));
                window.draw(cells.at(cell_count));
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const maze& m) {
    for (int i = 0; i < m.m_size; i++) {
        for (int j = 0; j < m.m_size; j++) {
            coordinates c = {j, i};
            if (m.get_pos() == c) {
                os << '*';
            } else {
                os << m.at(c);
            }
            os << ' ';
        }
        os << '\n';
    }
    os << m.m_message;
    return os;
}
