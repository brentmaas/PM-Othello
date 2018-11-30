/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasstapel4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 *            Ubuntu 16.04 LTS met g++ 5.4.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 30/11/2018
 */

#include "maasstapel4.h"

//Constructor
Stapel::Stapel(int m, int n): lengte(0), hoogte(m), breedte(n){
	//Hoogte * breedte - 4 zetten, plus één beginpositie
	stapel = new OthelloBord[m * n - 3];
}

//Destructor
Stapel::~Stapel(){
	//Deze variant van delete verwijder ook de onderliggende borden
	delete [] stapel;
}

//Functie om een aantal beurten terug te gaan en het nieuwe huidige bord terug
//te geven
OthelloBord& Stapel::gaTerug(int beurten){
	//Niet te ver terug gaan
	if(lengte - beurten < 1){
		lengte = 1;
		return stapel[0];
	}
	//Kleinere stapel nu
	lengte -= beurten;
	//Geef nieuwe huidige bord terug
	return stapel[lengte - 1];
}

//Functie om een bord op te slaan
void Stapel::slaop(OthelloBord& bord){
	//Kopieer het bord en stop het in de stapel
	OthelloBord nieuwbord(bord);
	stapel[lengte] = nieuwbord;
	lengte++; //Stapel wordt groter
}

//Recursieve functie om het aantal vervolgpartijen te berekenen
int Stapel::vervolg(){
	int v = 0; //Aantal vervolgpartijen in deze iteratie
	//Kopieer het huidige bord
	OthelloBord bord(stapel[lengte - 1]);
	//Als dit bord een afgelopen spel is, geef 1 terug (maar één partij
	//mogelijk geweest)
	if(bord.klaar()) return 1;
	//Probeer alle mogelijke zetten
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			//Probeer zet
			if(bord.magzet(i, j, bord.getBeurt())){
				bord.doezet(i, j, bord.getBeurt());
				//Sla het bord op
				slaop(bord);
				//Ga een niveau dieper in de recursie
				v += vervolg();
				//Gooi het bord weer weg
				gaTerug(1);
			}
		}
	}
	return v;
}