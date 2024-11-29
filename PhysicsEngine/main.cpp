#include <SFML/Graphics.hpp> 
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "2D Samurai Combat", sf::Style::Close);

    Game game;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        game.update(window);
        window.clear(sf::Color(200, 200, 200));
        game.draw(window);
        window.display();
    }

    return 0;
}
 