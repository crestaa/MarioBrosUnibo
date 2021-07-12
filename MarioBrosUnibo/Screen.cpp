#include "Screen.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "Entity.h"
#include "Player.h"
#include "Funzioni.h"
#include "Platform.h"

using namespace std;


Screen::Screen(int width, int height, int difficolta) {
	this->width = width;
	this->height = height;
	this->difficolta = difficolta-1;	// -1 perchè quando genera il livello incrementa la difficoltà di 1
	prob_enemy = 5;
	prob_bonus = 15;
	level = generateLevel(difficolta);
	srand(time(NULL));
}
void Screen::nextLevel() {
	if (level->next != NULL) {	//va al livello successivo
		level = level->next;
	}
	else {		//crea un nuovo livello e lo accoda alla lista
		p_livello tmp = generateLevel(difficolta);
		tmp->prev = level;
		level->next = tmp;
		level = level->next;
	}
}
bool Screen::prevLevel() {
	if (level->prev != NULL) {
		level = level->prev;
		return true;
	}
	else {		//arriva al primo livello generato, più indietro di così non si va
		return false;
	}
}
p_livello Screen::generateLevel(int difficolta) {
	//aggiornamento delle percentuali di spawn di bonus e nemici
	if(prob_bonus > 5)
		prob_bonus -= (prob_bonus * 0.1);
	if(prob_enemy < 15)
		prob_enemy += (prob_enemy * 0.1);


	//generazione del livello
	p_livello ret = new livello;
	ret->next = NULL;
	ret->prev = NULL;

	ret->piattaforme = generatePlatforms();
	ret->nemici = generateEnemies(ret->piattaforme);
	ret->bonus = generateBonus(ret->piattaforme);

	this->difficolta++;
	return ret;
}

p_platforms Screen::generatePlatforms() {
	p_platforms plat = NULL;
	p_platforms head = NULL;		//puntatore che tiene conto della testa della lista
	for (int i = 0; i < width; i++) {	//riga base
		p_platforms tmp = new platforms;
		tmp->p = Platform(i, height - 1);
		tmp->next = plat;
		plat = tmp;
		if (i == 0)
		{
			head = plat;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 1; j < height; j++) {
			int chance = rand() % 100;
			if (chance < 50) {		//50% di spawnare una piattaforma verso l'alto
				int x = i;
				do {
					p_platforms tmp = new platforms;
					tmp->p = Platform(x, height - 1 - j);
					tmp->next = plat;
					plat = tmp;

					x++;
					chance = rand() % 100;
				} while (chance < 60 && x < width);		//60% di spawnare una piattaforma a destra
			}
			else {
				break;
			}
		}
	}	
	return plat;
}
bool Screen::checkPlatform(p_platforms ptr, int x, int y) {	//controlla se esiste una piattaforma a determinate coordinate x e y. Costo O(n)
	if (ptr == NULL)
		return false;
	else if (ptr->p.getX() == x && ptr->p.getY() == y)
		return true;
	else
		return checkPlatform(ptr->next, x, y);
}
void Screen::moveEnemies() {
	p_enemies head_n = level->nemici;
	p_platforms head_p = level->piattaforme;
	while (head_n != NULL) {
		int chance = rand() % 3;		//0=sinistra, 1=fermo, 2=destra
		switch (chance) {
		case 0:
			if (checkPlatform(head_p, head_n->e.getX() - 1, head_n->e.getY())) {
				head_n->e.decreaseX(1);
			}
			head_p = level->piattaforme;
			break;
		case 2:
			if (checkPlatform(head_p, head_n->e.getX() + 1, head_n->e.getY())) {
				head_n->e.increaseX(1);
			}
			head_p = level->piattaforme;
			break;
		default:;		//comprende anche l'1 quindi sta fermo e non fa nulla
		}
		head_n = head_n->next;
	}
}
p_enemies Screen::generateEnemies(p_platforms piatt) {
	p_enemies en = NULL;
	p_platforms head = piatt;
	while (head != NULL) {
		int chance = rand() % 100;
		if (chance <= prob_enemy && head->p.getY() != height - 1) {
			p_enemies tmp = new enemies;
			if(rand()%4 == 1)	// 1/4 di probabilità di spawnare un enemy ladro (-3 punti al contatto)
				tmp->e = Enemy(head->p.getX(), head->p.getY(), 'ç');
			else	//spawn di un enemy generico altrimenti
				tmp->e = Enemy(head->p.getX(), head->p.getY());
			tmp->next = en;
			en = tmp;
		}
		head = head->next;
	}
	return en;
}
p_bonus Screen::generateBonus(p_platforms piatt) {
	p_bonus b = NULL;
	p_platforms head = piatt;
	while (head != NULL) {
		int chance = rand() % 100;		
		if (chance <= prob_bonus && head->p.getY()!=height-1) {
			p_bonus tmp = new bonus;
			if(rand()%4 == 1)	// 1/4 di probabilità di spawnare un bonus 1up (+1 vita)
				tmp->b = Bonus(head->p.getX(), head->p.getY(), '*');
			else	//spawn di un bonus generico altrimenti
				tmp->b = Bonus(head->p.getX(), head->p.getY());
			tmp->next = b;
			b = tmp;
		}
		head = head->next;
	}
	return b;
}
p_platforms Screen::getPlatforms() {
	return level->piattaforme;
}
void Screen::print() {
	MoveCursor(0, 0);
	//stampa bordi dello schermo
	cout << "\x1B[93m" << (char)201 << "\033[0m";
	for (int i = 0; i < width; i++)
		cout << "\x1B[93m" << (char)205 << "\033[0m";
	cout << "\x1B[93m" << (char)187 << "\033[0m" << endl;
	for (int i = 0; i < height; i++) {
		PrintAt(0, i+1, (char)186);
		PrintAt(width+1, i + 1, (char)186);
	}
	cout << endl << "\x1B[93m" << (char)200 << "\033[0m";
	for (int i = 0; i < width; i++)
		cout << "\x1B[93m" << (char)205 << "\033[0m";
	cout << "\x1B[93m" << (char)188 << "\033[0m";

	//stampa piattaforme
	p_platforms head_p = level->piattaforme;
	while (level->piattaforme != NULL) {
		level->piattaforme->p.print();
		level->piattaforme = level->piattaforme->next;
	}
	level->piattaforme = head_p;
	//stampa bonus
	p_bonus head_b = level->bonus;
	while (level->bonus!= NULL) {
		level->bonus->b.print();
		level->bonus = level->bonus->next;
	}
	level->bonus = head_b;
	//stampa nemici
	p_enemies head_n = level->nemici;
	while (level->nemici != NULL) {
		level->nemici->e.print();
		level->nemici = level->nemici->next;
	}
	level->nemici = head_n;
	
	
}
int Screen::getDifficolta() {
	return difficolta;
}
void Screen::setDifficolta(int diff) {
	difficolta = diff;
}
int Screen::detectCollision(Player& p) {
	//restituisco 0 se non c'è stata collisione, -1 se ha colpito un nemico (vite--), +1 se ha preso un bonus (punti++), -2 se ha colpito un ladro (punti-=3), +2 se ha preso un 1up (vite++)	
	int x = p.getX(), y = p.getY();
	p_bonus tmp_b = level->bonus;
	p_enemies tmp_e = level->nemici;
	int contatore = 0;
	//se collisione con bonus
	while (tmp_b != NULL) {
		if (tmp_b->b.getX() == x && tmp_b->b.getY() == y) {
			int ret = 1;
			if (tmp_b->b.symbol == '*')	//1up
				ret = 2;
			//rimuovere il bonus dall'elenco
			removeBonus(contatore);

			return ret;
		}
		else {
			tmp_b = tmp_b->next;
			contatore++;
		}
	}
	contatore = 0;
	//altrimenti se collisione con nemici
	while (tmp_e != NULL) {
		if (tmp_e->e.getX() == x && tmp_e->e.getY() == y) {
			int ret = -1;
			if (tmp_e->e.symbol == 'ç')	//ladro
				ret = -2;
			//rimuovere il nemico dall'elenco
			removeEnemy(contatore);
			
			return ret;
		}
		else {
			tmp_e = tmp_e->next;
			contatore++;
		}
	}
	return 0;
}
void Screen::removeBonus(int index) {
	p_bonus iter = level->bonus, prev = NULL;
	int i = 0;

	if (iter == NULL) {	//caso lista vuota
		return;		//esco direttamente dalla funzione perchè non ho nulla da eliminare
	}
	else if (iter->next == NULL) {		//caso lista da un elemento
		if (index == 0) {	//se l'indice da eliminare è 0 elimino l'elemento
			level->bonus = NULL;
		}
		else return;		//altrimenti esco dalla funzione
	}
	else {	//caso lista con + di un elemento
		if (index == 0) {	//se l'indice da eliminare è 0 elimino l'elemento
			prev = level->bonus;
			level->bonus = level->bonus->next;
			delete prev;
			prev = NULL;
		}
		else {		//altrimenti cerco l'elemento e lo elimino
			prev = iter;
			iter = iter->next;
			i++;
			while (iter != NULL && i <= index) {
				if (i == index) {
					iter = prev;
					prev = prev->next;
					iter->next = iter->next->next;
					delete prev;
					prev = NULL;
					return;		//appena lo elimino esco dalla funzione		
				}
				prev = iter;
				iter = iter->next;
				i++;
			}
		}
	}
}
void Screen::removeEnemy(int index) {
	p_enemies iter = level->nemici, prev = NULL;
	int i = 0;

	if (iter == NULL) {	//caso lista vuota
		return;		//esco direttamente dalla funzione perchè non ho nulla da eliminare
	}
	else if (iter->next == NULL) {		//caso lista da un elemento
		if (index == 0) {	//se l'indice da eliminare è 0 elimino l'elemento
			level->nemici = NULL;
		}
		else return;		//altrimenti esco dalla funzione
	}
	else {	//caso lista con + di un elemento
		if (index == 0) {	//se l'indice da eliminare è 0 elimino l'elemento
			prev = level->nemici;
			level->nemici = level->nemici->next;
			delete prev;
			prev = NULL;
		}
		else {		//altrimenti cerco l'elemento e lo elimino
			prev = iter;
			iter = iter->next;
			i++;
			while (iter != NULL && i <= index) {		
				if (i == index) {
					iter = prev;
					prev = prev->next;
					iter->next = iter->next->next;
					delete prev;
					prev = NULL;
					return;		//appena lo elimino esco dalla funzione
				}
				prev = iter;
				iter = iter->next;
				i++;
			}
		}
	}
}

