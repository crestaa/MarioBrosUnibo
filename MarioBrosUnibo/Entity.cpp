#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "Entity.h"
#include "Funzioni.h"
#include "Screen.h"
using namespace std;

Entity::Entity(int x, int y, char symbol) {
	defaultX = x;
	defaultY = y;
	this->x = x;
	this->y = y;
	this->symbol = symbol;
}
int Entity::getX() {
	return x;
}
int Entity::getY() {
	return y;
}
void Entity::setY(int y) {
	this->y = y;
}
void Entity::setX(int x) {
	this->x = x;
}
void Entity::moveTo(int x, int y) {
	this->x = x;
	this->y = y;
}
void Entity::increaseX(int x) {
	if (x > 0)
		this->x += x;
}void Entity::increaseY(int y) {
	if (y > 0)
		this->y += y;
}
void Entity::decreaseX(int x) {
	if (x > 0)
		this->x -= x;
}
void Entity::decreaseY(int y) {
	if (y > 0)
		this->y -= y;
}
void Entity::print() {		
	PrintAt(x+1, y+1, symbol);	//stampa a +1 perchè considera che la riga 0 e la colonna 0 sono usate per stampare i bordi di gioco
}