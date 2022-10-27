#include "maze.hpp"
#include <cstdio>

int main(void) {
    maze m(0);
    FILE* flux = stdin;
    char ch = ' ';

    m.update();
    while (true) {
        ch = getc(flux);
        if (ch == EOF) {
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
