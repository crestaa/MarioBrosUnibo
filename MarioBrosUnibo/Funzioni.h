#pragma once
#include "Entity.h"
#include "Player.h"
#include "Screen.h"


void Cursore(bool visible);		//setta la visibilità del cursore
void Movement(int width, int height, bool* gameOver, Player& p, Screen &schermo);	//gestione degli input e del movimento del player
void Handler(int width, int height, bool* gameOver, Player& p, Screen& schermo);	//gestore interazione tra player e ambiente di gioco
void PrintInfo(int width, int height, Player p, Screen schermo);	//stampa casella con informazioni di base sulla partita
void Clear();		//pulizia dello schermo
void WaitScreen();	//schermata di attesa prima di iniziare
void PrintAt(int x, int y, char what);
void MoveCursor(int x, int y);

