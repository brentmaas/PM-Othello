/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maas4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 15/11/2018
 */

#include <iostream>
#include "maasothello4.h"

//Voert het infoblok uit naar de standaarduitvoer
void infoBlokje(){
	std::cout << "/////////////////// INFOBLOK ///////////////////\n"
	"Naam: Brent Maas (s1826247)\n"
	"Jaar van aankomst: 2016\n"
	"Studierichting: Natuur- & Sterrenkunde + minor Data Science\n"
	"Studentnummer: s1826247\n"
	"Opgave: Othello\n"
	"\n"
	"\n"
	"Laatst bewerkt: 15/11/2018\n"
	"////////////////////////////////////////////////\n" << std::endl;
}

//Vraag aan of een speler een mens of een computer moet zijn en return true resp. false
bool vraagSpeler(int speler, const char* kleur){
	while(true){
		std::cout << "Speler " << speler << " (" << kleur << "): [M]ens of [C]omputer: ";
		char optie = std::cin.get();
		while(optie == '\n') optie = std::cin.get();
		if(optie == 'm' || optie == 'M') return true;
		if(optie == 'c' || optie == 'C') return false;
		std::cout << "Ongeldige keuze: '" << optie << "'!" << std::endl;
	}
}

//Vraag een dimensie op en return deze
int vraagDimensie(const char* dimensie){
	int i = 0;
	while(true){
		std::cout << dimensie << " (meer dan twee, veelvoud van twee): ";
		std::cin >> i;
		if(std::cin.fail()){ //Wanneer er iets anders dan een int wordt gegeven.
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Ongeldige invoer!" << std::endl;
			continue;
		}
		if(i % 2 == 0 && i > 2) return i;
		std::cout << "Ongeldige invoer!" << std::endl;
	}
}

int main(){
	infoBlokje();
	
	//const char* apart ipv gewoon de string doorgeven ivm waarschuwing over ISO C++
	const char* zwart = "zwart", * wit = "wit";
	bool speler1mens = vraagSpeler(1, zwart), speler2mens = vraagSpeler(2, wit);
	const char* hoogte = "Hoogte", * breedte = "Breedte";
	int m = vraagDimensie(hoogte), n = vraagDimensie(breedte);
	
	OthelloBord bord(m, n);
	bord.drukaf();
	
	return 0;
}
