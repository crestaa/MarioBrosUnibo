#include "Enemy.h"
Enemy::Enemy(int x, int y, char symbol) {
	defaultX = x;
	defaultY = y;
	this->x = x;
	this->y = y;
	this->symbol = symbol;
}