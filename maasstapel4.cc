/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasstapel4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 25/11/2018
 */

#include "maasstapel4.h"

Stapel::Stapel(int m, int n):
	lengte(0){
	stapel = new OthelloBord[m * n + 1];
}

Stapel::~Stapel(){
	for(int i = 0;i < lengte;i++){
		stapel[i].~OthelloBord();
	}
	delete stapel;
}

OthelloBord& Stapel::gaTerug(int beurten){
	if(lengte - beurten - 1 < 0){
		lengte = 1;
		return stapel[0];
	}
	lengte -= beurten;
	return stapel[lengte - 1];
}

void Stapel::slaop(OthelloBord& bord){
	stapel[lengte] = bord.kopieer();
	lengte++;
}