#pragma once
#include "Entity.h"
#include "Platform.h"
#include "Enemy.h"
#include "Player.h"
#include "Bonus.h"
struct platforms {
	platforms* next;
	Platform p;
};
typedef platforms* p_platforms;
struct enemies {
	enemies* next;
	Enemy e;
};
typedef enemies* p_enemies;
struct bonus {
	bonus* next;
	Bonus b;
};
typedef bonus* p_bonus;

struct livello{
	livello *next;
	livello *prev;
	p_platforms piattaforme;
	p_enemies nemici;
	p_bonus bonus;
};
typedef livello *p_livello;

class Screen
{
protected:
	p_livello level;
	int width, height;
	int difficolta;
	double prob_enemy, prob_bonus; //rappresentano le percentuali di probabilità di spawn (enemy va da 5% a 15% incrementando di 1/10 ogni volta, bonus fa il contrario)
	void removeBonus(int index);
	void removeEnemy(int index);
	p_platforms generatePlatforms();		//restituisce una lista di piattaforme
	p_enemies generateEnemies(p_platforms piatt);	//restituisce una lista di nemici a partire da una lista di piattaforme in input
	p_bonus generateBonus(p_platforms piatt);
	bool checkPlatform(p_platforms ptr, int x, int y);
public:
	Screen(int width, int height, int difficolta=1);
	void nextLevel();
	bool prevLevel();	//true se esiste un livello precedente, false se non esiste (1° livello)
	p_livello generateLevel(int difficolta);		//genera un livello e lo restituisce
	p_platforms getPlatforms();
	void print();
	int getDifficolta();
	void setDifficolta(int diff);
	void moveEnemies();
	int detectCollision(Player& p);		//restituisco 0 se non c'è stata collisione, -1 se ha colpito un nemico (vite--), +1 se ha preso un bonus (punti++), -2 se ha colpito un ladro (punti-=3), +2 se ha preso un 1up (vite++)	
	
};


