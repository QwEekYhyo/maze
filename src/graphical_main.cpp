#include <maze.hpp>

int main(void) {
    maze m(24);
    std::size_t width = 1920;
    std::size_t height = 1080;
    std::size_t frame = 0;

    sf::RenderWindow window(sf::VideoMode(width, height), "Maze");

    while (window.isOpen())
    {
        frame++;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        m.draw_on_window(window);
        window.display();
        if (frame % 20 == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                m.move({0, -1});
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                m.move({0, 1});
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                m.move({-1, 0});
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                m.move({1, 0});
            } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
    }

    return 0;
}
