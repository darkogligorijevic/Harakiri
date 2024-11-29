#include "Player.h"
#include <iostream>

// Constructor
Player::Player(std::string texturePath, bool isSamurai)
	: isAttacking(false), isAlive(true), firstAttackFrame(0, 384, 128, 128), idleFrame(0, 128, 128, 128), isDefending(false),
	defendFrame(0, 512, 128, 128), isJumping(false), jumpFrame(0, 0, 128, 128), deathFrame(0, 256, 128, 128), health(100000),
	secondAttackFrame(0, 768, 128, 128), thirdAttackFrame(0, 896, 128, 128), moveFrame(0, 640, 128, 128), isMoving(false), isDamaged(false)
{
	
	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "Image loading failed!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setOrigin(64.0f, 0.0f);
	if (isSamurai) {
		sprite.setPosition(100, 400);
		sprite.setScale(2.0f, 2.0f);
	}
	else {
		sprite.setPosition(1700, 400);
		sprite.setScale(-2.0f, 2.0f);
	}

	if (isSamurai)
		isFacingRight = true;
	else
		isFacingRight = false;

	swordHitBox.setFillColor(sf::Color::Transparent);
	swordHitBox.setSize(sf::Vector2f(85.0f, 150.0f));
	
	sprite.setTextureRect(idleFrame);
	clock.restart();
}


// Actions
void Player::attack() {
	if (isAlive && !isAttacking) {
		resetState();
		isAttacking = true;
	}
}

void Player::defend() {
	if (isAlive) {
		resetState();
		isDefending = true;
	}
}

void Player::jump() {
	if (isAlive) {
		resetState();
		isJumping = true;
	}
}

void Player::die() {
	isAlive = false;
}

void Player::move(bool isRight) {
	float deltaTime = clock.getElapsedTime().asSeconds();
	float moveSpeed = 800.0f;

	if (isAlive) {

		if (isRight) {
			sprite.setScale(2.0f, 2.0f);
			sprite.move(moveSpeed * deltaTime, 0);
			isMoving = true;
			isFacingRight = true;
		}
		else if (!isRight) {
			sprite.setScale(-2.0f, 2.0f);
			sprite.move(-moveSpeed * deltaTime, 0);
			isMoving = true;
			isFacingRight = false;
		}
		else {
			isMoving = false;
			moveElapsed = 0.0f;
		}

		if (moveElapsed >= 0.1f) {
			if (moveFrame.left == 896) {
				moveFrame.left = 0;
			}
			else {
				moveFrame.left += 128;
			}
			sprite.setTextureRect(moveFrame);
			moveElapsed = 0.0f;
		}
	}
}

void Player::takeDamage(int damage) {
	if (isAlive && !isDamaged) { 
		isDamaged = true; // Aktiviraj imunost
		health -= damage;
		std::cout << "Player took damage! Current health: " << health << std::endl;

		
		if (health <= 0) {
			die();
		}
	}
}

 

// Animations
void Player::animateFirstAttack(float frameSpeed) {
	attackElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isAttacking) {
		if (attackElapsed > frameSpeed) {
			if (firstAttackFrame.left == 640) {
				firstAttackFrame.left = 0;
				isAttacking = false;
			}
			else {
				firstAttackFrame.left += 128;
			}
			sprite.setTextureRect(firstAttackFrame);
			attackElapsed = 0.0f;
		}
	}
}

void Player::animateSecondAttack(float frameSpeed) {
	attackElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isAttacking) {
		if (attackElapsed > frameSpeed) {
			if (secondAttackFrame.left == 384) {
				secondAttackFrame.left = 0;
				isAttacking = false;
			}
			else {
				secondAttackFrame.left += 128;
			}
			sprite.setTextureRect(secondAttackFrame);
			attackElapsed = 0.0f;
		}
	}
}

void Player::animateThirdAttack(float frameSpeed) {
	attackElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isAttacking) {
		if (attackElapsed > frameSpeed) {
			if (thirdAttackFrame.left == 256) {
				thirdAttackFrame.left = 0;
				isAttacking = false;
			}
			else {
				thirdAttackFrame.left += 128;
			}
			sprite.setTextureRect(thirdAttackFrame);
			attackElapsed = 0;
		}
	}
}

void Player::animateDefend(float frameSpeed) {
	defendElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isDefending && !isMoving) {
		if (defendElapsed > frameSpeed) {
			if (defendFrame.left != 128) {
				defendFrame.left = 0;
				isDefending = false;
			}
			else {
				defendFrame.left += 128;
			}
			sprite.setTextureRect(defendFrame);
			defendElapsed = 0.0f;
		}
	}
}

void Player::animateJump(float frameSpeed) {
	jumpElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isJumping) {
		if (jumpElapsed > frameSpeed) {
			if (jumpFrame.left == 1408) {
				jumpFrame.left = 0;
				isJumping = false;
			}
			else {
				jumpFrame.left += 128;
			}
			sprite.setTextureRect(jumpFrame);
			jumpElapsed = 0.0f;
		}
	}
}

void Player::animateMove(float frameSpeed) {
	moveElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && isMoving) {
		if (moveElapsed > frameSpeed) {
			if (moveFrame.left == 896) {
				moveFrame.left = 0;
				isMoving = false;
			}
			else {
				moveFrame.left += 128;
			}
			sprite.setTextureRect(moveFrame);
			moveElapsed = 0.0f;
		}
	}
}

void Player::animateDeath(float frameSpeed) {
	deathElapsed += clock.getElapsedTime().asSeconds();
	if (!isAlive) {
		if (deathElapsed > frameSpeed) {
			if (deathFrame.left != 256) 
				deathFrame.left += 128;
			sprite.setTextureRect(deathFrame);
			deathElapsed = 0.0f;
		}
	}
}

void Player::animateIdle(float frameSpeed) {
	idleElapsed += clock.getElapsedTime().asSeconds();
	if (isAlive && !isAttacking && !isDefending && !isJumping && !isMoving) {
		if (idleElapsed > frameSpeed) {
			if (idleFrame.left == 640) {
				idleFrame.left = 0;
			}
			else {
				idleFrame.left += 128;
			}
			sprite.setTextureRect(idleFrame);
			idleElapsed = 0.0f;
		}
	}
}

int attackCounter = 0; // for debuging

// Display
void Player::update() {
	float deltaTime = clock.restart().asSeconds();
	moveElapsed += deltaTime;
	attackElapsed += deltaTime;
	defendElapsed += deltaTime;
	jumpElapsed += deltaTime;
	idleElapsed += deltaTime;
	deathElapsed += deltaTime;

	if (isAlive) {
		if (isAttacking) {
			if (attackCounter == 0) {
				animateFirstAttack(0.05f);
				if (!isAttacking) attackCounter = 1;
			}
			else if (attackCounter == 1) {
				animateSecondAttack(0.05f);
				if (!isAttacking) attackCounter = 2;
			}
			else if (attackCounter == 2) {
				animateThirdAttack(0.05f);
				if (!isAttacking) attackCounter = 0;
			}
		}

		if (isDamaged) {
			damageTimer += deltaTime;
			if (damageTimer >= damageCooldown) {
				isDamaged = false;
				damageTimer = 0.0f;
			}
		}

		if (isMoving) {
			animateMove(0.025f);  
		} else if (isDefending) {
			animateDefend(0.1f);
		}
		else if (isJumping) {
			animateJump(0.05f);
		}
		else {
			animateIdle(0.1f);
		}
		updateSwordHitBox();
	}
	else {
		animateDeath(1.0f);
	}
}


void Player::resetState() {
	isAttacking = false;
	isDefending = false;
	isJumping = false;
	isMoving = false;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(swordHitBox);
}

void Player::updateSwordHitBox() {
	if (isFacingRight) {
		swordHitBox.setPosition(sf::Vector2f(sprite.getPosition().x + 30.0f, sprite.getPosition().y + 100.0f));
	}
	else {
		swordHitBox.setPosition(sf::Vector2f(sprite.getPosition().x - 130.0f, sprite.getPosition().y + 100.0f));
	}
}

sf::RectangleShape Player::getSwordHitBox() {
	return swordHitBox;
}

sf::Sprite Player::getSprite() {
	return sprite;
}

bool Player::getIsDamaged() {
	return isDamaged;
}

int Player::getHealth() {
	return health;
}

bool Player::getIsAttacking() {
	return isAttacking;
}

void Player::setIsDamaged(bool state) {
	isDamaged = false;
	if (state)
		damageTimer = 0.0f;
}

void Player::setIsAttacking(bool state) {
	isAttacking = state;
}
