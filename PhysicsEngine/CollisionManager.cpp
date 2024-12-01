#include "CollisionManager.h"

bool CollisionManager::checkSwordCollision(Player& attacker, Player& target) {
	return attacker.getSwordHitBox().getGlobalBounds().intersects(target.getSprite().getGlobalBounds());
}