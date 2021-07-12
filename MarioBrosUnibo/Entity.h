#pragma once
class Entity
{
protected:
	int defaultX, defaultY;	//variabili per riportare allo stato di default le coordinate (es. quando il player si sposta tra gli schermi potrebbe essere utile rimetterlo alla posizione di default)
	int x, y;
	
public:
	char symbol;
	//costruttore
	Entity(int x = 0, int y = 0, char symbol='E');

	//funzioni per ottenere / settare i valori di X e Y e ottenere il simbolo
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void moveTo(int x, int y);
	//le x e le y passate come parametri devono essere sempre >0, altrimenti non fa nulla
	void increaseX(int x);
	void increaseY(int y);
	void decreaseX(int x);
	void decreaseY(int y);
	//funzione che sposta il cursore nel punto preciso in cui bisogna stampare e scrive un carattere
	void print();
};