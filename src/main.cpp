#include <maze.hpp>

int main(void) {
    maze m(24);
    char ch;
    std::string s;

    m.update();
    while (true) {
        std::getline(std::cin, s);
        if (!s.empty()) {
            ch = s[0];
        }

        if (ch == 'k' || ch == EOF) {
            return 0;
        } else if (ch == 'z'){
            m.move({0, -1});
        } else if (ch == 's'){
            m.move({0, 1});
        } else if (ch == 'q'){
            m.move({-1, 0});
        } else if (ch == 'd'){
            m.move({1, 0});
        }
        ch = ' ';
    }
}
