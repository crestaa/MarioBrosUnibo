#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "Entity.h"
#include "Funzioni.h"
#include "Player.h"
#include "Screen.h"

using namespace std;
#define SPACE 32
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

void Cursore(bool visible)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO infoCursore;
	GetConsoleCursorInfo(output, &infoCursore);
	infoCursore.bVisible = visible;
	SetConsoleCursorInfo(output, &infoCursore);
}

//gestisce il movimento del player
void Movement(int width, int height, bool* gameOver, Player& p, Screen &schermo) {		//passo p per riferimento in modo da poterla modificare
	if (_kbhit())
	{
		p_platforms plat = schermo.getPlatforms();

		//salvo il tasto che è stato premuto
		char tastoPremuto = _getch();
		switch (tastoPremuto)
		{
		//movimento a sx
		case 'a':
		case 'A':
		case ARROW_LEFT:
			if (p.getX() == 0) {
				p.decreaseX(1);
			}
			else {
				while (plat != NULL) {
					if (plat->p.getX() == p.getX() - 1 && plat->p.getY() == p.getY())
					{
						p.decreaseX(1);
						break;
					}
					plat = plat->next;
				}
			}
			break;
		//movimento a dx
		case 'd':
		case 'D':
		case ARROW_RIGHT:
			if (p.getX() == width - 1)
				p.increaseX(1);
			else {
				while (plat != NULL) {
					if (plat->p.getX() == p.getX() + 1 && plat->p.getY() == p.getY())
					{
						p.increaseX(1);
						break;
					}
					plat = plat->next;
				}
			}
			break;
		//movimento in su
		case ARROW_UP:
		case SPACE:
		case 'w':
		case 'W':
			while (plat != NULL) {
				if (plat->p.getX() == p.getX() && plat->p.getY() == p.getY() - 1)
				{
					p.decreaseY(1);
					break;
				}
				plat = plat->next;
			}
			break;
		//movimento in giù
		case ARROW_DOWN:
		case 's':
		case 'S':
			while (plat != NULL) {
				if (plat->p.getX() == p.getX() && plat->p.getY() == p.getY() + 1)
				{
					p.increaseY(1);
					break;
				}
				plat = plat->next;
			}
			break;
		//tasto X per terminare il programma
		case 'x':
		case 'X':
			*gameOver = true;
			break;
		default:
			break;
		}
	}
}

//gestisce le interazioni del player con l'ambiente di gioco
void Handler(int width, int height, bool* gameOver, Player& p, Screen& schermo) {
	//gestione movimento orizzontale tra schermate
	if (p.getX() >= width) {
		schermo.nextLevel();
		p.setX(0);
		p.setY(height - 1);
	}
	else if (p.getX() < 0) {
		bool esistePrec = schermo.prevLevel();
		if (esistePrec) {
			p.setX(width - 1);
			p.setY(height - 1);
		}
		else
			p.setX(0);
	}
	//gestione collisione con enemies e bonus (e relativi decrementi e incrementi su vite e punti)
	int coll = schermo.detectCollision(p);
	if (coll == 1)
		p.increasePunti(1);
	else if (coll == 2)
		p.increaseVite(1);
	else if (coll == -1)
		p.decreaseVite(1);
	else if (coll == -2)
		p.decreasePunti(3);
	//gestione movimento verticale fuori dai bordi
	if (p.getY() >= height)
		p.setY(height - 1);
	if (p.getY() < 0)
		p.setY(0);
	//gestione condizione di esaurimento vite rimaste
	if (p.getVite() <= 0)
		*gameOver = true;
}

void Clear() {
	system("cls");
}

void WaitScreen() {
	while (!_kbhit()) {
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\tPremi un tasto per iniziare";
		for (int i = 0; i < 3 && !_kbhit(); i++)
		{
			cout << ".";
			Sleep(300);
		}
		Clear();
	}
}

void PrintAt(int x, int y, char what) {
	MoveCursor(x, y);
	//\x1B[92m	 testo   \033[0m
	switch (what) {
	case '@':
		cout << "\x1B[96m@\033[0m";
		break;
	case '$':
		cout << "\x1B[32m$\033[0m";
		break;
	case '*':
		cout << "\x1B[92m*\033[0m";
		break;
	case '&':
		cout << "\x1B[31m&\033[0m";
		break;
	case 'ç':
		cout << "\x1B[91mç\033[0m";
		break;
	case (char)(186) :
		cout << "\x1B[93m" << (char)186 << "\033[0m";
		break;
	default:
		cout << what;
		break;
	}
	
}
void MoveCursor(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
void PrintInfo(int width, int height, Player p, Screen schermo) {  //funzione per stampare casella con informazioni di base sulla partita
	MoveCursor(width + 5, 1);
	cout << "Vite: " << p.getVite();
	MoveCursor(width + 5, 2);
	cout << "Punti: " << p.getPunti();
	MoveCursor(width + 5, 3);
	cout << "Livello: " << schermo.getDifficolta();
	MoveCursor(width + 5, 5);
	cout << "Legenda:";
	MoveCursor(width + 5, 6);
	cout << "\x1B[96m@\033[0m : Player";
	MoveCursor(width + 5, 7);
	cout << "\x1B[32m$\033[0m : bonus (+1 punto)";
	MoveCursor(width + 5, 8);
	cout << "\x1B[31m&\033[0m : nemico (-1 vita)";
	MoveCursor(width + 5, 9);
	cout << "\x1B[92m*\033[0m : 1up (+1 vita)";
	MoveCursor(width + 5, 10);
	cout << "\x1B[91mç\033[0m : ladro (-3 punti)";
	//\x1B[92m		\033[0m
	
}
