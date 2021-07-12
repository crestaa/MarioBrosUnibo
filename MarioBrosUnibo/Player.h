#pragma once
#include "Entity.h"
class Player : public Entity
{
protected:
	int punti, vite;
public:
	Player(int x, int y, char symbol = '@', int punti = 0, int vite = 10);
	void increaseX(int x);
	void increaseY(int y);
	void decreaseX(int x);
	void decreaseY(int y);
	int getPunti();
	void setPunti(int pt);
	int getVite();
	void setVite(int vt);
	void increasePunti(int pt);
	bool decreaseVite(int vt);		//true se le vite sono > 0, false se è morto
	void decreasePunti(int pt);
	void increaseVite(int vt);
};

