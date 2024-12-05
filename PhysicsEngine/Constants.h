#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

// WINDOW SIZE
const float WINDOW_WIDTH = 1920;
const float WINDOW_HEIGHT = 1080;

// PHYSICS
const float GRAVITY = 1800.0f;
const float JUMP_SPEED = 800.0f;
const float MOVE_SPEED = 800.0f;

// POSITION
const sf::Vector2f PLAYER1_START_POS(100, 725);
const sf::Vector2f PLAYER2_START_POS(1700, 725);

// HITBOX SIZE FOR SWORD
const sf::Vector2f SWORD_HB_SIZE(85, 150);

#endif