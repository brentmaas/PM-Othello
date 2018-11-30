/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasothello4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 *            Ubuntu 16.04 LTS met g++ 5.4.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 30/11/2018
 */

#include <iostream>
#include <ctime>
#include "maasothello4.h"

//Constructor
BordVakje::BordVakje(): kleur(kleur0){
	//Zet de buren naar nullptr om later aan te vullen
	for(int i = 0;i < 8;i++) buren[i] = nullptr;
}

//Standaard constructor
//Maakt gebruik van een "initialiser list" dat variabelen initialiseert voordat
//de constructor wordt aangeroepen
OthelloBord::OthelloBord(): hoogte(8), breedte(8), zetten(0), beurt(kleur1),
		laatsteBeurtI(-1), laatsteBeurtJ(-1){
	bouwbord(); //Construeer pointerstructuur
}

//Constructor
//Officieel begint zwart
OthelloBord::OthelloBord(int m, int n): hoogte(m), breedte(n), zetten(0),
		beurt(kleur1), laatsteBeurtI(-1), laatsteBeurtJ(-1){
	bouwbord(); //Construeer pointerstructuur
}

//Destructor
OthelloBord::~OthelloBord() {
	//Verwijder de vakjes in omgekeerde volgorde zodat het resultaat van de
	//get functie altijd geldig blijft
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			delete get(hoogte - i - 1, breedte - j - 1);
		}
	}
}

//Kopieer constructor; kan worden aangeroepen om een kopie van een gegeven bord
//te maken
OthelloBord::OthelloBord(const OthelloBord& bord): hoogte(bord.hoogte),
		breedte(bord.breedte), zetten(bord.zetten), beurt(bord.beurt),
		laatsteBeurtI(bord.laatsteBeurtI), laatsteBeurtJ(bord.laatsteBeurtJ){
	bouwbord(); //Construeer pointerstructuur
	//Kopieer de inhoud van de vakjes
	for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
		BordVakje* vakje = get(i, j), * bordvakje = bord.get(i, j);
		//Veiligheidscheck
		if(vakje != nullptr && bordvakje != nullptr)
			vakje->kleur = bordvakje->kleur;
	}
}

//Assignment operator; wordt aangeroepen wanneer 'bord1 = bord2' wordt gedaan
//om de inhoud van bord1 gelijk te maken aan bord2
OthelloBord& OthelloBord::operator=(const OthelloBord& bord){
	//Kopieer de inhoud van de vakjes
	for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
		if(get(i, j) != nullptr && bord.get(i, j) != nullptr){
			get(i, j)->kleur = bord.get(i, j)->kleur;
		}
	}
	//Kopieer parameters
	hoogte = bord.hoogte;
	breedte = bord.breedte;
	zetten = bord.zetten;
	beurt = bord.beurt;
	laatsteBeurtI = bord.laatsteBeurtI;
	laatsteBeurtJ = bord.laatsteBeurtJ;
	//Geef deze class terug (nadat bord2 gekopieerd is willen we dat bord1
	//gelijk is aan deze kopie)
	return *this;
}

//Functie om de pointerstructuur op te zetten
void OthelloBord::bouwbord(){
	//Begin met een rij op de oorsprong
	ingang = maakrij(breedte);
	BordVakje* vorige = ingang;
	for(int i = 1;i < hoogte;i++){
		//Maak een nieuwe rij
		BordVakje* nieuw = maakrij(breedte);
		//En rits deze aan de vorige rij
		rits(vorige, nieuw);
		vorige = nieuw;
	}
	
	//Zet de beginpositie
	get(hoogte / 2 - 1, breedte / 2 - 1)->kleur = kleur2;
	get(hoogte / 2 - 1, breedte / 2)->kleur = kleur1;
	get(hoogte / 2, breedte / 2 - 1)->kleur = kleur1;
	get(hoogte / 2, breedte / 2)->kleur = kleur2;
}

//Functie om de computerzet te doen
void OthelloBord::computerzet(char kl){
	//Als een hoek gezet kan worden, doe dat
	if(magzet(0, 0, kl)) doezet(0, 0, kl);
	else if(magzet(0, breedte - 1, kl)) doezet(0, breedte - 1, kl);
	else if(magzet(hoogte - 1, 0, kl)) doezet(hoogte - 1, 0, kl);
	else if(magzet(hoogte - 1, breedte - 1, kl)) doezet(hoogte - 1, breedte - 1, kl);
	else{ //Anders neem een willekeurige mogelijke zet
		int i = rand() % hoogte;
		int j = rand() % breedte;
		//(Dit wordt geen oneindige loop aangezien er voordat deze functie
		//wordt aangeroepen gecontroleerd wordt of er een mogelijk zet is)
		while(!magzet(i, j, kl)){
			i = rand() % hoogte;
			j = rand() % breedte;
		}
		//Voer de gevonden zet uit
		doezet(i, j, kl);
	}
}

//Functie om de menselijke zet te verwerken
void OthelloBord::menszet(char kl, bool& gedaan, int i, int j){
	//Kijk of de zet mag
	gedaan = magzet(i, j, kl);
	//Zo ja, voer hem uit
	if(gedaan) doezet(i, j, kl);
}

//Functie om het bord af te drukken
void OthelloBord::print(){
	//Print de bovenste lijn van het kader
	std::cout << "-";
	for(int i = 0;i < breedte;i++) std::cout << "--";
	std::cout << "--" << std::endl;
	BordVakje* vakje = ingang; //Begin van de huidige rij
	for(int y = 0;y < hoogte;y++){
		std::cout << "|"; //Print het linker lijndeeltje van het kader
		BordVakje* vakje2 = vakje; //Neem het begin van de huidige rij
		//Print de kleur en schuif op tot het einde van de rij
		for(int x = 0;x < breedte;x++){
			std::cout << " " << vakje2->kleur;
			vakje2 = vakje2->buren[2];
		}
		//Print het rechter lijndeeltje van het kader
		std::cout << " |" << std::endl;
		vakje = vakje->buren[4]; //Ga een rij naar beneden
	}
	//Print de onderste lijn van het kader
	std::cout << "-";
	for(int i = 0;i < breedte;i++) std::cout << "--";
	std::cout << "--" << std::endl;
}

//Functie om te kijken of het spel is afgelopen
bool OthelloBord::klaar(){
	//Als het aantal zetten gelijk is aan het oppervlakte van het bord(min de
	//vier beginposities) is het spel afgelopen
	if(zetten >= hoogte * breedte - 4) return true;
	//Anders kijk of er mogelijke zetten zijn
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			//Als een zet mag is het spel niet afgelopen
			if(magzet(i, j, beurt)) return false;
		}
	}
	//Geen zetten mogelijk; het spel is afgelopen
	return true;
}

//Functie om de winnaar te bepalen. Aangenomen dat het spel is afgelopen
char OthelloBord::winnaar(int& verschil){
	if(zetten == hoogte * breedte - 4){ //Alle zetten zijn gedaan; tel kleuren
		int zwart = 0, wit = 0; //Tellers voor score
		for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
			if(get(i, j)->kleur == kleur1) zwart++;
			else wit++; //Geen lege vakjes, dus een niet-zwart vakje is wit
		}
		//Meer zwarte dan witte: zwart wint
		if(zwart > wit){
			verschil = zwart - wit;
			return kleur1;
		}
		//Meer witte dan zwarte: wit wint
		else if(wit > zwart){
			verschil = wit - zwart;
			return kleur2;
		}
		//Gelijk aantal witte en zwarte: gelijk spel
		return kleur0;
	}else{ //Een beurt kon dus niet gezet worden, dus de huidige beurt verliest
		verschil = 0; //Verschil niet belangrijk
		if(beurt == kleur1) return kleur2;
		return kleur1;
	}
}

//Functie om een zet uit te voeren
void OthelloBord::doezet(int i, int j, char kl){
	get(i, j)->kleur = kl; //Zet de kleur van de positie
	//Controleer elke richting hij mag en voer hem uit
	if(checkrichting(i, j, 0, kl)) vulrichting(i, j, 0, kl);
	if(checkrichting(i, j, 1, kl)) vulrichting(i, j, 1, kl);
	if(checkrichting(i, j, 2, kl)) vulrichting(i, j, 2, kl);
	if(checkrichting(i, j, 3, kl)) vulrichting(i, j, 3, kl);
	if(checkrichting(i, j, 4, kl)) vulrichting(i, j, 4, kl);
	if(checkrichting(i, j, 5, kl)) vulrichting(i, j, 5, kl);
	if(checkrichting(i, j, 6, kl)) vulrichting(i, j, 6, kl);
	if(checkrichting(i, j, 7, kl)) vulrichting(i, j, 7, kl);
	zetten++; //Er is een zet gedaan
	//Nieuwe laatste beurt-positie
	laatsteBeurtI = i;
	laatsteBeurtJ = j;
	wisselbeurt(); //Wissel de beurt af
}

//Functie om te kijken of een zet mag
bool OthelloBord::magzet(int i, int j, char kl){
	//Als het vakje niet leeg is mag het sowieso niet
	if(get(i, j)->kleur != kleur0) return false;
	//Bekijk elke richting
	bool boven = checkrichting(i, j, 0, kl);
	bool rechtsboven = checkrichting(i, j, 1, kl);
	bool rechts = checkrichting(i, j, 2, kl);
	bool rechtsonder = checkrichting(i, j, 3, kl);
	bool onder = checkrichting(i, j, 4, kl);
	bool linksonder = checkrichting(i, j, 5, kl);
	bool links = checkrichting(i, j, 6, kl);
	bool linksboven = checkrichting(i, j, 7, kl);
	//Als minimaal één richting mag, mag de zet
	return boven || rechtsboven || rechts || rechtsonder || onder || linksonder
			|| links || linksboven;
}

//Functie om de pointer naar een vakje op [i,j] te krijgen
BordVakje* OthelloBord::get(int i, int j){
	//Vakjes buiten het bord bestaan sowieso niet
	if(i < 0 || i >= hoogte || j < 0 || j >= breedte) return nullptr;
	BordVakje* vakje = ingang; //Beginpositie
	//Ga i stappen naar beneden
	for(int k = 0;k < i;k++){
		//Veiligheidscheck
		if(vakje == nullptr) return nullptr;
		vakje = vakje->buren[4]; //Schuif één stapje naar beneden op
	}
	//Ga j stappen naar rechts
	for(int k = 0;k < j;k++){
		//Veiligheidscheck
		if(vakje == nullptr) return nullptr;
		vakje = vakje->buren[2]; //Schuif één stapje naar rechts op
	}
	return vakje;
}

//Functie om de pointer naar een vakje op [i,j] te krijgen, const variant voor
//de assignment operator
BordVakje* OthelloBord::get(int i, int j) const{
	//Vakjes buiten het bord bestaan sowieso niet
	if(i < 0 || i >= hoogte || j < 0 || j >= breedte) return nullptr;
	BordVakje* vakje = ingang; //Beginpositie
	//Ga i stappen naar beneden
	for(int k = 0;k < i;k++){
		//Veiligheidscheck
		if(vakje == nullptr) return nullptr;
		vakje = vakje->buren[4]; //Schuif één stapje naar beneden op
	}
	//Ga j stappen naar rechts
	for(int k = 0;k < j;k++){
		//Veiligheidscheck
		if(vakje == nullptr) return nullptr;
		vakje = vakje->buren[2]; //Schuif één stapje naar rechts op
	}
	return vakje;
}

//Getter voor de breedte
int OthelloBord::getBreedte(){
	return breedte;
}

//Getter voor de hoogte
int OthelloBord::getHoogte(){
	return hoogte;
}

//Getter voor de huidige beurt
char OthelloBord::getBeurt(){
	return beurt;
}

//Getter voor de hoogte van de laatste beurt
int OthelloBord::getLaatsteBeurtI(){
	return laatsteBeurtI;
}

//Getter voor de breedte van de laatste beurt
int OthelloBord::getLaatsteBeurtJ(){
	return laatsteBeurtJ;
}

//Functie om twee pointerrijen te verbinden
void OthelloBord::rits(BordVakje* boven, BordVakje* onder){
	//Beginposities van de onderste en bovenste rij
	BordVakje* b = boven;
	BordVakje* o = onder;
	for(int i = 0;i < breedte;i++){
		//Verbind het bovenste vakje aan de onderste rij
		b->buren[3] = o->buren[2];
		b->buren[4] = o;
		b->buren[5] = o->buren[6];
		//Verbind het onderste vakje aan de bovenste rij
		o->buren[7] = b->buren[6];
		o->buren[0] = b;
		o->buren[1] = b->buren[2];
		//Schuif beide vakjes op naar rechts
		b = b->buren[2];
		o = o->buren[2];
	}
}

//Functie om een pointerrij te maken
BordVakje* OthelloBord::maakrij(int aantal){
	//Maak een nieuw vakje als beginpunt
	BordVakje* start = new BordVakje;
	BordVakje* vorige = start;
	for(int i = 1;i < aantal;i++){
		//Maak een nieuw vakje
		BordVakje* nieuw = new BordVakje;
		//Verbind het vorige en het nieuwe vakje met elkaar
		vorige->buren[2] = nieuw;
		nieuw->buren[6] = vorige;
		//Schuif op
		vorige = nieuw;
	}
	return start;
}

//Functie om te kijken of een bepaalde richting een zet valide maakt
bool OthelloBord::checkrichting(int i, int j, int richting, char kl){
	//Vindt de kleur van de tegenstander
	char anderekleur = kleur1;
	if(kl == kleur1) anderekleur = kleur2;
	//Neem alvast één stap in de richting
	BordVakje* vakje = get(i, j)->buren[richting];
	//Als dat vakje niet bestaat of niet van de tegenstander is maakt de
	//richting de zet niet valide
	if(vakje == nullptr || vakje->kleur != anderekleur) return false;
	vakje = vakje->buren[richting]; //Nog een stap
	while(vakje != nullptr){ //Zolang de zijkant van het bord niet bereikt is
		//Zelfde kleur als degene die de zet maakt: zet is valide
		if(vakje->kleur == kl) return true;
		//Vakje is leeg: richting maakt zet niet valide
		else if(vakje->kleur == kleur0) return false;
		//Vakje was van de tegenstander: neem een stap verder
		vakje = vakje->buren[richting];
	}
	//Zijkant van het bord bereikt zonder dat de stap mocht; richting maakt zet
	//niet valide
	return false;
}

//Functie om een richting van een zet uit te voeren (op dit punt is de richting
//al gecontroleerd door checkrichting)
void OthelloBord::vulrichting(int i, int j, int richting, char kl){
	//Begin één stapje in de richting
	BordVakje* vakje = get(i, j)->buren[richting];
	//Zolang de kleur van de zetter niet bereikt is moet er gevuld worden
	while(vakje->kleur != kl){
		vakje->kleur = kl; //Zet kleur
		vakje = vakje->buren[richting]; //Stapje verder
	}
}

//Functie om de beurt te wisselen
void OthelloBord::wisselbeurt(){
	if(beurt == kleur1) beurt = kleur2;
	else beurt = kleur1;
}
