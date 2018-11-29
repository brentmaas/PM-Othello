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

//Vraag om een één-karakter optie
char vraagOptie(){
	char optie = std::cin.get();
	while(optie == '\n') optie = std::cin.get(); //Negeer enters
	return optie;
}

//Vraag aan of een speler een mens of een computer moet zijn
//en return true resp. false
bool vraagSpeler(int speler, std::string kleur){
	while(true){
		std::cout << "Speler " << speler << " (" << kleur 
			<< "): [M]ens of [C]omputer: ";
		char optie = vraagOptie();
		if(optie == 'm' || optie == 'M') return true; //Menslijke speler
		if(optie == 'c' || optie == 'C') return false; //Computerspeler
		std::cout << "Ongeldige keuze: '" << optie << "'!" << std::endl;
	}
}

//Vraag een dimensie op en return deze
int vraagDimensie(std::string dimensie){
	int i = 0;
	while(true){
		std::cout << dimensie << " (meer dan nul, veelvoud van twee): ";
		std::cin >> i;
		if(std::cin.fail()){ //Wanneer er iets anders dan een int wordt gegeven
			//clear en ignore nodig om cin goed te resetten
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Ongeldige invoer!" << std::endl;
			continue;
		}
		if(i % 2 == 0 && i >= 2) return i;//Even en meer dan of gelijk aan twee
		std::cout << "Ongeldige invoer!" << std::endl;
	}
}

//Print wat de laatste beurt was en door wie deze gezet is
void printbeurt(OthelloBord& bord){
	int laatsteI = bord.getLaatsteBeurtI(), laatsteJ = bord.getLaatsteBeurtJ();
	//laatsteI, laatsteJ == -1 betekent dat nog geen beurt is gezet
	if(laatsteI != -1 && laatsteJ != -1){
		//Zwart aan de beurt, dus wit had gezet
		if(bord.getBeurt() == kleur1) std::cout << "Wit";
		else std::cout << "Zwart";
		std::cout << " zette ";
		//Alleen voor breedte <= 26 bestaan karakterrepresentaties,
		//daarna worden het gewoon getallen
		if(bord.getBreedte() <= 26) std::cout << (char) ('A' + laatsteJ)
				<< (laatsteI + 1) << std::endl;
		else std::cout << (laatsteJ + 1) << "," << (laatsteI + 1) << std::endl;
	}
}

//Vraag één van de posities op tijdens het zetten
int vraagPositie(OthelloBord& bord, bool isBreedte){
	int uit = -1;
	while(true){
		std::cout << (isBreedte ? "Breedte" : "Hoogte") << "([1, "
				<< (isBreedte ? bord.getBreedte() : bord.getHoogte()) << "]";
		//Alleen bij de breedte en als deze <= 26 is worden karakters gebruikt
		if(isBreedte && bord.getBreedte() <= 26){
			std::cout << " of [A, " << char('A' + bord.getBreedte() - 1) <<"]";
		}
		std::cout << "): ";
		std::string in;
		std::cin >> in;
		//Bekijk hoofdletters bij breedte
		if(isBreedte && in.length() == 1 && bord.getBreedte() <= 26
				&& in[0] >= 'A' && in[0] <= 'A' + bord.getBreedte()){
			uit = in[0] - 'A';
		//Bekijk kleine letters bij breedte
		}else if(isBreedte && in.length() == 1 && bord.getBreedte() <= 26
				&& in[0] >= 'a' && in[0] <= 'a' + bord.getBreedte()){
			uit = in[0] - 'a';
		//Bekijk getallen in het algemeen
		}else if(in[0] >= '0' && in[0] <= '9'){
			uit = std::atoi(in.c_str()) - 1;
			//Meer dan de hoogte/breedte is niet toegestaan
			if(isBreedte && uit >= bord.getBreedte()) uit = -1;
			else if(!isBreedte && uit >= bord.getHoogte()) uit = -1;
		}
		//uit == -1 betekent dat er geen geldige invoer was
		if(uit != -1) break;
		std::cout << "Ongeldige invoer!" << std::endl;
	}
	return uit;
}

//Print en behandel het menu
void menu(OthelloBord& bord, Stapel& stapel){
	//Print beurt
	std::cout << (bord.getBeurt() == kleur1 ? "Zwart" : "Wit")
			<< " is aan de beurt" << std::endl;
	char optie;
	while(true){
		//Print en vraag opties
		std::cout << "Doe een [Z]et, bereken het aantal "
				"[V]ervolgpartijen of ga [T]erug" << std::endl;
		optie = vraagOptie();
		if(optie == 'Z' || optie == 'z'){ //Doe een zet
			bool gezet = false;
			while(!gezet){ //Zolang geen geldige zet is gedaan
				//Vraag posities
				int j = vraagPositie(bord, true), i = vraagPositie(bord,false);
				
				//Probeer zet
				bord.menszet(bord.getBeurt(), gezet, i, j);
				if(!gezet) std::cout << "Ongeldige zet!" << std::endl;
			}
			break; //Beëindig de beurt
		}else if(optie == 'V' || optie == 'v'){ //Bereken vervolgpartijen
			int v = stapel.vervolg();
			std::cout << "Er zijn " << v << " vervolgpartijen" << std::endl;
		}else if(optie == 'T' || optie == 't'){ //Ga een beurt terug
			//Twee beurten om langs de beurt van de tegenstander te gaan
			bord = stapel.gaTerug(2);
			bord.print(); //Situatie gewijzigd, print bord opnieuw
		}
	}
}

//Functie om het spel te spelen
void speelspel(bool speler1mens, bool speler2mens, int m, int n){
	OthelloBord bord(m, n);
	Stapel stapel(m, n);
	stapel.slaop(bord);
	
	//Zolang het spel niet afgelopen is
	while(!bord.klaar()){
		printbeurt(bord);		
		
		bord.print();
		
		//Wanneer een menselijke speler aan de beurt is
		if((speler1mens && bord.getBeurt() == kleur1)
				|| (speler2mens && bord.getBeurt() == kleur2)){
			menu(bord, stapel);
		}else{ //Computerspeler aan de beurt
			bord.computerzet(bord.getBeurt());
		}
		
		//Stuur het huidige bord naar de stapel
		stapel.slaop(bord);
	}
	
	//Print beurt en bord nogmaals als eindresultaat
	printbeurt(bord);
	
	bord.print();
	
	//Vraag winnaar en verschil op
	int verschil = 0;
	char winnaar = bord.winnaar(verschil);
	
	if(winnaar == kleur1) std::cout << "Zwart wint";
	else if(winnaar == kleur2) std::cout << "Wit wint";
	else std::cout << "Gelijk spel" << std::endl;
	if(winnaar == kleur1 || winnaar == kleur2){ //Geen gelijk spel
		//verschil == 0: Iemand kon niet zetten
		if(verschil == 0) std::cout << " (" << (winnaar == kleur1 ? "Wit" : "Zwart") << " kon niet meer zetten)";
		//Iemand won door een verschil in stenen
		else std::cout << " (" << verschil << " stenen meer dan " << (winnaar == kleur1 ? "Wit" : "Zwart") << ")" << std::endl;
	}
}

int main(){
	infoBlokje();
	
	//Vraag spelers en dimensies
	bool speler1mens = vraagSpeler(1, "zwart"), speler2mens = vraagSpeler(2, "wit");
	int m = vraagDimensie("Hoogte"), n = vraagDimensie("Breedte");
	
	speelspel(speler1mens, speler2mens, m, n);
	
	return 0;
}
