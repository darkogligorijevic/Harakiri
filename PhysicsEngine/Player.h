#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Player {
private:
	sf::Vector2f velocity;
	sf::RectangleShape swordHitBox;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect firstAttackFrame, secondAttackFrame, thirdAttackFrame, idleFrame, defendFrame, jumpFrame, deathFrame, moveFrame;
	sf::RectangleShape healthHUD;
	bool isAttacking;
	bool isAlive;
	bool isDefending;
	bool isJumping;
	bool isMoving;
	bool isFacingRight;
	bool isDamaged;
	int health;
	sf::Clock clock;
	float moveElapsed = 0.0f, attackElapsed = 0.0f, defendElapsed = 0.0f, jumpElapsed = 0.0f, idleElapsed = 0.0f, deathElapsed = 0.0f;
	float damageCooldown = 0.2f;
	float damageTimer = 0.0f;
public:

	// Constructor
	Player(std::string texturePath, bool isSamurai);

	// Actions
	void attack();
	void defend();
	void jump(float deltaTime);
	void die();
	void move(bool isRight, float deltaTime);
	void takeDamage(int damage);

	// Animations
	void animateFirstAttack(float frameSpeed);
	void animateSecondAttack(float frameSpeed);
	void animateThirdAttack(float frameSpeed);
	void animateIdle(float frameSpeed);
	void animateDefend(float frameSpeed);
	void animateJump(float frameSpeed);
	void animateDeath(float frameSpeed);
	void animateMove(float frameSpeed);
	
	// Display and Updates
	void resetState();
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	void updateSwordHitBox();
	void updateHealthHUD();

	// Getters
	sf::RectangleShape getSwordHitBox();
	sf::Sprite getSprite();
	bool getIsDamaged();
	int getHealth();
	bool getIsAttacking();
	sf::Vector2f getVelocity();

	// Setters
	void setIsDamaged(bool state);
	void setIsAttacking(bool state);
	void setVelocity(sf::Vector2f value);
};

#endif