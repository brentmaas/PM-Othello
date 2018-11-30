/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasstapel4.h
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 *            Ubuntu 16.04 LTS met g++ 5.4.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 30/11/2018
 */

//Include guard, beschermt tegen meervoudige includen
#ifndef MAASSTAPEL4_H
#define MAASSTAPEL4_H

#include "maasothello4.h"

//Class voor de stapel van Othello borden
class Stapel {
public:
	Stapel(int m, int n); //Constructor
	~Stapel(); //Destructor
	//Functie om een aantal beurten terug te gaan en het nieuwe huidige bord
	//terug te geven
	OthelloBord& gaTerug(int beurten);
	void slaop(OthelloBord& bord); //Functie om een bord op te slaan
	//Recursieve functie om het aantal vervolgpartijen te berekenen
	int vervolg();
private:
	OthelloBord* stapel; //Array naar alle borden
	//Lengte van de stapel, hoogte en breedte van de borden
	int lengte, hoogte, breedte;
};

#endif