/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasstapel4.h
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 29/11/2018
 */

#ifndef MAASSTAPEL4_H
#define MAASSTAPEL4_H

#include "maasothello4.h"

class Stapel {
public:
	Stapel(int m, int n);
	~Stapel();
	Stapel(const Stapel& s); //Copy constructor
	Stapel& operator=(const Stapel& s); //Assignment operator
	OthelloBord& gaTerug(int beurten);
	void slaop(OthelloBord& bord);
	int vervolg();
private:
	OthelloBord* stapel;
	int lengte, hoogte, breedte;
};

#endif