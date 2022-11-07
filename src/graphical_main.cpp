#include <maze.hpp>
#include <SFML/Graphics.hpp>

int main(void) {
    maze m(24);
    std::size_t width = 1920;
    std::size_t height = 1080;

    sf::RenderWindow window(sf::VideoMode(width, height), "Maze");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        m.draw_on_window(window);
        window.display();
    }

    return 0;
}
