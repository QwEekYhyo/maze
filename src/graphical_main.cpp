#include <maze.hpp>

int main(void) {
    maze m(30);
    std::size_t width = 1920;
    std::size_t height = 1080;
    std::size_t index = 0;
    std::size_t trigger = 30;

    sf::RenderWindow window(sf::VideoMode(width, height), "Maze");

    while (window.isOpen())
    {
        index++;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        m.draw_on_window(window);
        window.display();
        if (index >= trigger) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                m.move({0, -1});
                index = 0;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                m.move({0, 1});
                index = 0;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                m.move({-1, 0});
                index = 0;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                m.move({1, 0});
                index = 0;
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                m.mark_cell();
            }
        }
    }

    return 0;
}
