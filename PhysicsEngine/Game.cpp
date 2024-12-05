#include "Game.h"
#include <iostream>

Game::Game() : player1("images/Samurai/Samurai.png", true), player2("images/Samurai/Samurai.png", false),
window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Harikiri", sf::Style::Close)
{

	// Load texture for map
	if (!mapTexture.loadFromFile("images/Map/green.png")) {
		std::cerr << "Couldn't load background image!" << std::endl;
	}

	// Scale it to the window's size (width and height)
	mapTextureSize = mapTexture.getSize();
	windowSize = window.getSize();

	float scaleX = (float)windowSize.x / mapTextureSize.x;
	float scaleY = (float)windowSize.y / mapTextureSize.y;

	// Set that texture
	mapSprite.setTexture(mapTexture);
	mapSprite.setScale(scaleX, scaleY);
	deltaTime = 0.0f;
}

// Main loop
void Game::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		update();
		draw();
	}
}

// Keyboard inputs
void Game::handleInput(Player& player, sf::Keyboard::Key attackKey, sf::Keyboard::Key defendKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key moveLeftKey) {
	if (sf::Keyboard::isKeyPressed(attackKey)) player.attack();
	else if (sf::Keyboard::isKeyPressed(defendKey)) player.defend();
	else if (sf::Keyboard::isKeyPressed(jumpKey)) player.jump(deltaTime);
	else if (sf::Keyboard::isKeyPressed(moveRightKey) && player.getSprite().getPosition().x <= windowSize.x) player.move(true, deltaTime);
	else if (sf::Keyboard::isKeyPressed(moveLeftKey) && player.getSprite().getPosition().x >= 0) player.move(false, deltaTime);
}

// Display and Update
void Game::update() {
	deltaTime = clock.restart().asSeconds();
	handleInput(player1, sf::Keyboard::Space, sf::Keyboard::LShift, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::A);
	handleInput(player2, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Left);
	// Check sword collision
	if (CollisionManager::checkSwordCollision(player1, player2) && player1.getIsAttacking()) {
		player2.takeDamage(10);  
	}
	if (CollisionManager::checkSwordCollision(player2, player1) && player2.getIsAttacking()) {
		player1.takeDamage(10);  
	}
	player1.update(deltaTime);
	player2.update(deltaTime);
}

void Game::draw() {
	window.clear();
	window.draw(mapSprite);
	player1.draw(window);
	player2.draw(window);
	window.display();
}
 

