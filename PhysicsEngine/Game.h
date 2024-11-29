#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
private:
	Player player1;
	Player player2;
public:

	Game();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void checkCollision();
	void keyboardEvents(sf::RenderWindow& window);

};

#endif
