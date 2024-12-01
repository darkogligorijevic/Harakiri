#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CollisionManager.h"
#include "Constants.h"

class Game {
private:
	// Window
	sf::RenderWindow window;

	// Player
	Player player1;
	Player player2;

	// Map
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	sf::Vector2u mapTextureSize;
	sf::Vector2u windowSize;

	// Clock
	sf::Clock clock;
	float deltaTime;
public:
	Game();
	void update();
	void draw();
	void handleInput(Player& player, sf::Keyboard::Key attackKey, sf::Keyboard::Key defendKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key moveLeftKey);
	void run();
};

#endif
