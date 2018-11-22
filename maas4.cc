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

int main(){
	infoBlokje();
	
	bool speler1mens, speler2mens;
	
	while(true){
		std::cout << "Speler 1 (wit): [M]ens of [C]omputer: ";
		char optie = std::cin.get();
		while(optie == '\n') optie = std::cin.get();
		if(optie == 'm' || optie == 'M'){
			speler1mens = true;
			break;
		}
		if(optie == 'c' || optie == 'C'){
			speler1mens = false;
			break;
		}
		std::cout << "Ongeldige keuze: '" << optie << "'!" << std::endl;
	}
	
	while(true){
		std::cout << "Speler 2 (zwart): [M]ens of [C]omputer: ";
		char optie = std::cin.get();
		while(optie == '\n') optie = std::cin.get();
		if(optie == 'm' || optie == 'M'){
			speler2mens = true;
			break;
		}
		if(optie == 'c' || optie == 'C'){
			speler2mens = false;
			break;
		}
		std::cout << "Ongeldige keuze: '" << optie << "'!" << std::endl;
	}
	
	OthelloBord bord;
	bord.drukaf();
	
	return 0;
}