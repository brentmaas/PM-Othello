/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maas4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 29/11/2018
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

char vraagOptie(){
	char optie = std::cin.get();
	while(optie == '\n') optie = std::cin.get();
	return optie;
}

//Vraag aan of een speler een mens of een computer moet zijn en return true resp. false
bool vraagSpeler(int speler, std::string kleur){
	while(true){
		std::cout << "Speler " << speler << " (" << kleur << "): [M]ens of [C]omputer: ";
		char optie = vraagOptie();
		if(optie == 'm' || optie == 'M') return true;
		if(optie == 'c' || optie == 'C') return false;
		std::cout << "Ongeldige keuze: '" << optie << "'!" << std::endl;
	}
}

//Vraag een dimensie op en return deze
int vraagDimensie(std::string dimensie){
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
		if(i % 2 == 0 && i >= 2) return i;
		std::cout << "Ongeldige invoer!" << std::endl;
	}
}

void printbeurt(OthelloBord& bord){
	int laatsteI = bord.getLaatsteBeurtI(), laatsteJ = bord.getLaatsteBeurtJ();
	if(laatsteI != -1 && laatsteJ != -1){
		if(bord.getBeurt() == kleur1) std::cout << "Wit";
		else std::cout << "Zwart";
		std::cout << " zette ";
		if(bord.getBreedte() <= 26) std::cout << (char) ('A' + laatsteJ) << (laatsteI + 1) << std::endl;
		else std::cout << (laatsteJ + 1) << "," << (laatsteI + 1) << std::endl;
	}
}

int vraagPositie(OthelloBord& bord, bool isBreedte){
	int uit = -1;
	while(true){
		std::cout << (isBreedte ? "Breedte" : "Hoogte") << "([1, " << (isBreedte ? bord.getBreedte() : bord.getHoogte()) << "]";
		if(isBreedte && bord.getBreedte() <= 26){
			std::cout << " of [A, " << char('A' + bord.getBreedte() - 1) << "]";
		}
		std::cout << "): ";
		std::string in;
		std::cin >> in;
		if(isBreedte && in.length() == 1 && bord.getBreedte() <= 26 && in[0] >= 'A' && in[0] <= 'A' + bord.getBreedte()){
			uit = in[0] - 'A';
		}else if(isBreedte && in.length() == 1 && bord.getBreedte() <= 26 && in[0] >= 'a' && in[0] <= 'a' + bord.getBreedte()){
			uit = in[0] - 'a';
		}else if(in[0] >= '0' && in[0] <= '9'){
			uit = std::atoi(in.c_str()) - 1;
			if(uit >= bord.getBreedte()) uit = -1;
		}
		if(uit != -1) break;
		std::cout << "Ongeldige invoer!" << std::endl;
	}
	return uit;
}

void menu(OthelloBord& bord, Stapel& stapel){
	std::cout << (bord.getBeurt() == kleur1 ? "Zwart" : "Wit") << " is aan de beurt" << std::endl;
	char optie;
	while(true){
		std::cout << "Doe een [Z]et of bereken het aantal [V]ervolgpartijen" << std::endl;
		optie = vraagOptie();
		if(optie == 'Z' || optie == 'z'){
			bool gezet = false;
			while(!gezet){
				int j = vraagPositie(bord, true), i = vraagPositie(bord, false);
				
				bord.menszet(bord.getBeurt(), gezet, i, j);
				if(!gezet) std::cout << "Ongeldige zet!" << std::endl;
			}
			break;
		}else if(optie == 'V' || optie == 'v'){
			int v = stapel.vervolg();
			std::cout << "Er zijn " << v << " vervolgpartijen" << std::endl;
		}
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
			menu(bord, stapel);
		}else{
			bord.computerzet(bord.getBeurt());
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
	
	bool speler1mens = vraagSpeler(1, "zwart"), speler2mens = vraagSpeler(2, "wit");
	int m = vraagDimensie("Hoogte"), n = vraagDimensie("Breedte");
	
	speelspel(speler1mens, speler2mens, m, n);
	
	return 0;
}
