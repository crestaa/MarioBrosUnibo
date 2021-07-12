#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "Funzioni.h"
#include "Player.h"
#include "Entity.h"
#include "Screen.h"
using namespace std;


//variabili globali
int width = 35, height = 10;
Player p = Player(0, height-1, '@', 0, 3);
Screen schermo = Screen(width, height);
bool gameOver = false;

int sleepcounter = 0;

int main()
{
    Cursore(false);     //toglie la visibilità del cursore
    WaitScreen();       //schermata di attesa

    while (!gameOver) {
        if (_kbhit()) {
            Clear();
            //gestore movimento e input
            Movement(width, height, &gameOver, p, schermo);
            Handler(width, height, &gameOver, p, schermo);

            //stampa
            PrintInfo(width, height, p, schermo);
            schermo.print();
            p.print();
        }
        if (sleepcounter >= 3000) {     //ogni 3000 cicli sposta i nemici, fatto per evitare flickering o ritardi nell'input (usando lo Sleep())
            Clear();
            schermo.moveEnemies();
            sleepcounter = 0;
            //stampa
            PrintInfo(width, height, p, schermo);
            schermo.print();
            p.print();
        }
        sleepcounter++;
        
    }

    Clear();

    cout << "GAME OVER";
    
}

