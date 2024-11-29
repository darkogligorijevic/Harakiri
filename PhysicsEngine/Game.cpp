#include "Game.h"
#include <iostream>

Game::Game() : player1("images/Samurai/Samurai.png", true), player2("images/Samurai/Samurai.png", false) {

}

void Game::checkCollision() {
	// Player1 hitting player2
	sf::FloatRect swordBounds1 = player1.getSwordHitBox().getGlobalBounds();
	sf::FloatRect player2Bounds = player2.getSprite().getGlobalBounds();

	// Player2 hittin player1
	sf::FloatRect swordBounds2 = player2.getSwordHitBox().getGlobalBounds();
	sf::FloatRect player1Bounds = player1.getSprite().getGlobalBounds();

	if (swordBounds1.intersects(player2Bounds) && player1.getIsAttacking()) {
		if (!player2.getIsDamaged()) {
			player2.takeDamage(10);
			player2.setIsDamaged(true);
		}
	}

	if (swordBounds2.intersects(player1Bounds) && player2.getIsAttacking()) {
		if (!player1.getIsDamaged()) {
			player1.takeDamage(10);
			player1.setIsDamaged(true);
		}
	}
}

void Game::keyboardEvents(sf::RenderWindow& window) {
	// Player1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		player1.attack();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		player1.defend();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player1.jump();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player1.getSprite().getPosition().x <= window.getSize().x) {
		player1.move(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player1.getSprite().getPosition().x >= 0) {
		player1.move(false);
	}

	// Player2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		player2.attack();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		player2.defend();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player2.jump();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player2.getSprite().getPosition().x <= window.getSize().x)
		player2.move(true);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player2.getSprite().getPosition().x >= 0)
		player2.move(false);
}

void Game::update(sf::RenderWindow& window) {
	keyboardEvents(window);
	checkCollision();
	player1.update();
	player2.update();
}

void Game::draw(sf::RenderWindow& window) {
	player1.draw(window);
	player2.draw(window);
}
 

