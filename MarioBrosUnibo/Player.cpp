#include "Player.h"
Player::Player(int x, int y, char symbol, int punti, int vite) : Entity(x, y, symbol) {
	this->punti = punti;
	this->vite = vite;
}

void Player::increaseX(int x) {
	Entity::increaseX(x);
}
void Player::decreaseX(int x) {
	Entity::decreaseX(x);
}
void Player::increaseY(int y) {
	Entity::increaseY(y);
}
void Player::decreaseY(int y) {
	Entity::decreaseY(y);
}
int Player::getPunti() {
	return punti;
}
int Player::getVite() {
	return vite;
}
void Player::setPunti(int pt) {
	punti = pt;
}
void Player::setVite(int vt) {
	vite = vt;
}
void Player::increasePunti(int pt) {
	if(pt > 0)
		punti += pt;
}
bool Player::decreaseVite(int vt) {
	if(vt > 0)
		vite -= vt;
	return vite > 0;
}
void Player::decreasePunti(int pt) {
	if (pt > 0)
		punti -= pt;
}
void Player::increaseVite(int vt) {
	if (vt > 0)
		vite += vt;
}