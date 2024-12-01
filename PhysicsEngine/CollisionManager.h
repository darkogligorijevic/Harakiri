#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "Player.h"

class CollisionManager
{
private:
	Player& player1;
	Player& player2;
public:
	static bool checkSwordCollision(Player& attacker, Player& target);
};

#endif
