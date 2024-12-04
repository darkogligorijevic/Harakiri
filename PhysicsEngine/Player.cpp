#include "Player.h"
#include <iostream>

// Constructor
Player::Player(std::string texturePath, bool isSamurai)
	: isAttacking(false), isAlive(true), firstAttackFrame(0, 384, 128, 128), idleFrame(0, 128, 128, 128), isDefending(false),
	defendFrame(0, 512, 128, 128), isJumping(false), jumpFrame(0, 0, 128, 128), deathFrame(0, 256, 128, 128), health(100),
	secondAttackFrame(0, 768, 128, 128), thirdAttackFrame(0, 896, 128, 128), moveFrame(0, 640, 128, 128), isMoving(false), isDamaged(false),
	velocity(0.0f, 0.0f)
{
	
	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "Image loading failed!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setOrigin(64.0f, 0.0f);
	
	sprite.setPosition(isSamurai ? PLAYER1_START_POS : PLAYER2_START_POS);
	sprite.setScale(2.0f, 2.0f);
	isSamurai ? isFacingRight = true : isFacingRight = false;

	swordHitBox.setFillColor(sf::Color::Transparent);
	swordHitBox.setSize(SWORD_HB_SIZE);

	// HUD
	healthHUD.setFillColor(sf::Color::Red);
	healthHUD.setSize(sf::Vector2f(health, 20.0f));

	
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

void Player::jump(float deltaTime) {
	if (isAlive && !isJumping && sprite.getPosition().y == 725) {
		resetState();
		velocity.y = -JUMP_SPEED;  // Početna vertikalna brzina
		isJumping = true;
	}

	if (isJumping) {
		velocity.y += GRAVITY * deltaTime;  // Ažuriraj gravitaciju
		sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);  // Pomeri sprite po X i Y osi
	}

	// Provera za povratak na zemlju
	if (sprite.getPosition().y >= 725) {
		sprite.setPosition(sprite.getPosition().x, 725);  // Resetuj Y poziciju
		velocity.y = 0.0f;  // Zaustavi vertikalnu brzinu
		velocity.x = 0.0f;  // Zaustavi horizontalnu brzinu
		isJumping = false;  // Skok je završen
	}
}




void Player::die() {
	isAlive = false;
}

void Player::move(bool isRight, float deltaTime) {
	//float deltaTime = clock.getElapsedTime().asSeconds();

	if (isAlive) {

		if (isRight) {
			sprite.setScale(2.0f, 2.0f);
			sprite.move(MOVE_SPEED * deltaTime, 0);
			isMoving = true;
			isFacingRight = true;
		}
		else if (!isRight) {
			sprite.setScale(-2.0f, 2.0f);
			sprite.move(-MOVE_SPEED * deltaTime, 0);
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
		isDamaged = true; 
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
	if (isAlive && isJumping) {
		jumpElapsed += clock.getElapsedTime().asSeconds();
		if (jumpElapsed > frameSpeed) {
			if (jumpFrame.left == 1408) {  // Kraj animacije
				jumpFrame.left = 0;
			}
			else {
				jumpFrame.left += 128;  // Pomeri na sledeći frame
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
void Player::update(float deltaTime) {
	float deltaTimeAnimations = clock.restart().asSeconds();
	moveElapsed += deltaTimeAnimations;
	attackElapsed += deltaTimeAnimations;
	defendElapsed += deltaTimeAnimations;
	jumpElapsed += deltaTimeAnimations;
	idleElapsed += deltaTimeAnimations;
	deathElapsed += deltaTimeAnimations;

	if (isAlive) {
		if (isAttacking) {
			// Animacija napada
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

		if (isJumping) {
			jump(deltaTime);  // Ažuriraj fiziku skoka
			animateJump(0.08f);  // Animiraj skok
		}
		else if (isMoving) {
			animateMove(0.025f);  // Animacija kretanja
		}
		else if (isDefending) {
			animateDefend(0.1f);
		}
		else {
			animateIdle(0.5f);
		}

		updateSwordHitBox();  // Ažuriraj hitbox mača
	}
	else {
		animateDeath(1.0f);  // Animacija smrti
	}

	updateHealthHUD();  // Ažuriraj HUD
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
	window.draw(healthHUD);
}

void Player::updateSwordHitBox() {
	if (isFacingRight) {
		swordHitBox.setPosition(sf::Vector2f(sprite.getPosition().x - 35, sprite.getPosition().y + 100.0f));
	}
	else {
		swordHitBox.setPosition(sf::Vector2f(sprite.getPosition().x - 35, sprite.getPosition().y + 100.0f));
	}
}

void Player::updateHealthHUD() {
	healthHUD.setPosition(sprite.getPosition().x - 50.0f, sprite.getPosition().y + 50.0f);
	healthHUD.setSize(sf::Vector2f(health, 10.0f));
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

sf::Vector2f Player::getVelocity() {
	return velocity;
}

void Player::setVelocity(sf::Vector2f value) {
	velocity = value;
}