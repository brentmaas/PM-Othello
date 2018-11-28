/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maas4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 25/11/2018
 */

#include <iostream>
#include "maasstapel4.h"
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
		std::cout << dimensie << " (meer dan nul, veelvoud van twee): ";
		std::cin >> i;
		if(std::cin.fail()){ //Wanneer er iets anders dan een int wordt gegeven.
			//clear, ignore nodig om cin goed te resetten
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Ongeldige invoer!" << std::endl;
			continue;
		}
		if(i % 2 == 0 && i > 0) return i;
		std::cout << "Ongeldige invoer!" << std::endl;
	}
}

void printbeurt(OthelloBord& bord){
	int laatsteI = bord.getLaatsteBeurtI(), laatsteJ = bord.getLaatsteBeurtJ();
	if(laatsteI != -1 && laatsteJ != -1){
		if(bord.getBeurt() == kleur1) std::cout << "Wit";
		else std::cout << "Zwart";
		std::cout << " zette ";
		if(bord.getBreedte() <= 26){
			std::cout << (char) ('A' + laatsteJ) << (laatsteI + 1) << std::endl;
		}else std::cout << (laatsteJ + 1) << "," << (laatsteI + 1) << std::endl;
	}
}

void speelspel(bool speler1mens, bool speler2mens, int m, int n){
	OthelloBord bord(m, n);
	Stapel stapel(m, n);
	stapel.slaop(bord);
	
	while(!bord.klaar()){
		printbeurt(bord);
		
		bord.print();
		
		if((speler1mens && bord.getBeurt() == kleur1) || (speler2mens && bord.getBeurt() == kleur2)){
			bool gezet = false;
			while(!gezet){
				std::cout << (bord.getBeurt() == kleur1 ? "Zwart" : "Wit") << " is aan de beurt" << std::endl;
				std::cout << "Hoogte ([1, " << bord.getBreedte() << "]";
				if(bord.getBreedte() <= 26){
					std::cout << " of [A, " << char('A' + bord.getBreedte() - 1) << "]";
				}
				std::cout << ": ";
				char in = std::cin.get();
				int i;
				if(in >= 'A' || in <= 'Z'){
					i = in - 'A';
				}else if(in >= '1' || in <= '9'){
					
				}
			}
		}else{
			bord.randomzet(bord.getBeurt());
		}
		
		stapel.slaop(bord);
	}
	
	printbeurt(bord);
	
	bord.print();
	
	char winnaar = bord.winnaar();
	
	if(winnaar == kleur1) std::cout << "Zwart wint" << std::endl;
	else if(winnaar == kleur2) std::cout << "Wit wint" << std::endl;
	else std::cout << "Gelijk spel" << std::endl;
}

int main(){
	infoBlokje();
	
	//const char* apart ipv gewoon de string doorgeven ivm waarschuwing over ISO C++
	const char* zwart = "zwart", * wit = "wit";
	bool speler1mens = vraagSpeler(1, zwart), speler2mens = vraagSpeler(2, wit);
	const char* hoogte = "Hoogte", * breedte = "Breedte";
	int m = vraagDimensie(hoogte), n = vraagDimensie(breedte);
	
	speelspel(speler1mens, speler2mens, m, n);
	
	return 0;
}
