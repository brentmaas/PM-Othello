/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasstapel4.h
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 25/11/2018
 */

#ifndef MAASSTAPEL4_H
#define MAASSTAPEL4_H

#include "maasothello4.h"

class Stapel {
public:
	Stapel(int m, int n);
	~Stapel();
	OthelloBord& gaTerug(int beurten);
	void slaop(OthelloBord& bord);
private:
	OthelloBord* stapel;
	int lengte;
};

#endif