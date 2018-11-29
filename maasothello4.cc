/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasothello4.cc
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 29/11/2018
 */

#include <iostream>
#include <ctime>
#include "maasothello4.h"
using namespace std;

BordVakje::BordVakje():
	kleur(kleur0){
	for(int i = 0;i < 8;i++) buren[i] = nullptr;
}

OthelloBord::OthelloBord(): ingang(nullptr), hoogte(8), breedte(8), zetten(0), beurt(kleur1), laatsteBeurtI(-1), laatsteBeurtJ(-1){
	srand(time(0));
	bouwbord();
}

//Officieel begint zwart
OthelloBord::OthelloBord(int m, int n): hoogte(m), breedte(n), zetten(0), beurt(kleur1), laatsteBeurtI(-1), laatsteBeurtJ(-1){
	srand(time(0));
	bouwbord();
}

OthelloBord::~OthelloBord() {
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			delete get(hoogte - i - 1, breedte - j - 1);
		}
	}
}

OthelloBord::OthelloBord(const OthelloBord& bord): hoogte(bord.hoogte), breedte(bord.breedte),
	zetten(bord.zetten), beurt(bord.beurt), laatsteBeurtI(bord.laatsteBeurtI), laatsteBeurtJ(bord.laatsteBeurtJ){
	bouwbord();
	for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
		get(i, j)->kleur = bord.get(i, j)->kleur;
	}
}

OthelloBord& OthelloBord::operator=(const OthelloBord& bord){
	for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
		if(get(i, j) != nullptr && bord.get(i, j) != nullptr){
			get(i, j)->kleur = bord.get(i, j)->kleur;
		}
	}
	hoogte = bord.hoogte;
	breedte = bord.breedte;
	zetten = bord.zetten;
	beurt = bord.beurt;
	laatsteBeurtI = bord.laatsteBeurtI;
	laatsteBeurtJ = bord.laatsteBeurtJ;
	return *this;
}

OthelloBord OthelloBord::kopieer(){
	OthelloBord kopie(hoogte, breedte);
	for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
		kopie.get(i, j)->kleur = get(i, j)->kleur;
	}
	kopie.zetten = zetten;
	kopie.beurt = beurt;
	kopie.laatsteBeurtI = laatsteBeurtI;
	kopie.laatsteBeurtJ = laatsteBeurtJ;
	
	return kopie;
}

void OthelloBord::bouwbord(){
	ingang = maakrij(breedte);
	BordVakje* vorige = ingang;
	for(int i = 1;i < hoogte;i++){
		BordVakje* nieuw = maakrij(breedte);
		rits(vorige, nieuw);
		vorige = nieuw;
	}
	
	get(hoogte / 2 - 1, breedte / 2 - 1)->kleur = kleur2;
	get(hoogte / 2 - 1, breedte / 2)->kleur = kleur1;
	get(hoogte / 2, breedte / 2 - 1)->kleur = kleur1;
	get(hoogte / 2, breedte / 2)->kleur = kleur2;
}

void OthelloBord::computerzet(char kl){
	//Als een hoek gezet kan worden, doe dat
	if(magzet(0, 0, kl)) doezet(0, 0, kl);
	else if(magzet(0, breedte - 1, kl)) doezet(0, breedte - 1, kl);
	else if(magzet(hoogte - 1, 0, kl)) doezet(hoogte - 1, 0, kl);
	else if(magzet(hoogte - 1, breedte - 1, kl)) doezet(hoogte - 1, breedte - 1, kl);
	else{ //Anders neem een willekeurige mogelijke zet
		int i = rand() % hoogte;
		int j = rand() % breedte;
		while(!magzet(i, j, kl)){
			i = rand() % hoogte;
			j = rand() % breedte;
		}
		doezet(i, j, kl);
	}
}

void OthelloBord::menszet(char kl, bool& gedaan, int i, int j){
	gedaan = magzet(i, j, kl);
	if(gedaan) doezet(i, j, kl);
}

void OthelloBord::print(){
	std::cout << "-";
	for(int i = 0;i < breedte;i++) std::cout << "--";
	std::cout << "--" << std::endl;
	BordVakje* vakje = ingang;
	for(int y = 0;y < hoogte;y++){
		std::cout << "|";
		BordVakje* vakje2 = vakje;
		for(int x = 0;x < breedte;x++){
			std::cout << " " << vakje2->kleur;
			vakje2 = vakje2->buren[2];
		}
		std::cout << " |" << std::endl;
		vakje = vakje->buren[4];
	}
	std::cout << "-";
	for(int i = 0;i < breedte;i++) std::cout << "--";
	std::cout << "--" << std::endl;
}

bool OthelloBord::klaar(){
	if(zetten == hoogte * breedte) return true;
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			if(magzet(i, j, beurt)) return false;
		}
	}
	return true;
}

//Aangenomen dat het spel is afgelopen
char OthelloBord::winnaar(int& verschil){
	//hoogte * breedte - 4 zetten mogelijk
	if(zetten == hoogte * breedte - 4){ //Alle zetten zijn gedaan; tel kleuren
		int zwart = 0, wit = 0;
		for(int i = 0;i < hoogte;i++) for(int j = 0;j < breedte;j++){
			//Er kan aangenomen worden dat er geen lege vakjes zijn
			if(get(i, j)->kleur == kleur1) zwart++;
			else wit++;
		}
		if(zwart > wit){
			verschil = zwart - wit;
			return kleur1;
		}
		else if(wit > zwart){
			verschil = wit - zwart;
			return kleur2;
		}
		return kleur0; //Gelijk spel
	}else{ //Een beurt kon dus niet gezet worden, dus de huidige beurt verliest
		verschil = 0;
		if(beurt == kleur1) return kleur2;
		return kleur1;
	}
}

void OthelloBord::doezet(int i, int j, char kl){
	get(i, j)->kleur = kl;
	if(checkrichting(i, j, 0, kl)) vulrichting(i, j, 0, kl);
	if(checkrichting(i, j, 1, kl)) vulrichting(i, j, 1, kl);
	if(checkrichting(i, j, 2, kl)) vulrichting(i, j, 2, kl);
	if(checkrichting(i, j, 3, kl)) vulrichting(i, j, 3, kl);
	if(checkrichting(i, j, 4, kl)) vulrichting(i, j, 4, kl);
	if(checkrichting(i, j, 5, kl)) vulrichting(i, j, 5, kl);
	if(checkrichting(i, j, 6, kl)) vulrichting(i, j, 6, kl);
	if(checkrichting(i, j, 7, kl)) vulrichting(i, j, 7, kl);
	zetten++;
	laatsteBeurtI = i;
	laatsteBeurtJ = j;
	wisselbeurt();
}

bool OthelloBord::magzet(int i, int j, char kl){
	if(get(i, j)->kleur != kleur0) return false;
	bool boven = checkrichting(i, j, 0, kl);
	bool rechtsboven = checkrichting(i, j, 1, kl);
	bool rechts = checkrichting(i, j, 2, kl);
	bool rechtsonder = checkrichting(i, j, 3, kl);
	bool onder = checkrichting(i, j, 4, kl);
	bool linksonder = checkrichting(i, j, 5, kl);
	bool links = checkrichting(i, j, 6, kl);
	bool linksboven = checkrichting(i, j, 7, kl);
	return boven || rechtsboven || rechts || rechtsonder || onder || linksonder || links || linksboven;
}

BordVakje* OthelloBord::get(int i, int j){
	if(i < 0 || i >= hoogte || j < 0 || j >= breedte) return nullptr;
	BordVakje* vakje = ingang;
	for(int k = 0;k < i;k++) vakje = vakje->buren[4];
	for(int k = 0;k < j;k++) vakje = vakje->buren[2];
	return vakje;
}

BordVakje* OthelloBord::get(int i, int j) const{
	if(i < 0 || i >= hoogte || j < 0 || j >= breedte) return nullptr;
	BordVakje* vakje = ingang;
	for(int k = 0;k < i;k++) vakje = vakje->buren[4];
	for(int k = 0;k < j;k++) vakje = vakje->buren[2];
	return vakje;
}

int OthelloBord::getBreedte(){
	return breedte;
}

int OthelloBord::getHoogte(){
	return hoogte;
}

char OthelloBord::getBeurt(){
	return beurt;
}

int OthelloBord::getLaatsteBeurtI(){
	return laatsteBeurtI;
}

int OthelloBord::getLaatsteBeurtJ(){
	return laatsteBeurtJ;
}

void OthelloBord::rits(BordVakje* boven, BordVakje* onder){
	BordVakje* b = boven;
	BordVakje* o = onder;
	for(int i = 0;i < breedte;i++){
		b->buren[3] = o->buren[2];
		b->buren[4] = o;
		b->buren[5] = o->buren[6];
		o->buren[7] = b->buren[6];
		o->buren[0] = b;
		o->buren[1] = b->buren[2];
		b = b->buren[2];
		o = o->buren[2];
	}
}

bool OthelloBord::checkrichting(int i, int j, int richting, char kl){
	char anderekleur = kleur1;
	if(kl == kleur1) anderekleur = kleur2;
	BordVakje* vakje = get(i, j)->buren[richting];
	if(vakje == nullptr || vakje->kleur != anderekleur) return false;
	vakje = vakje->buren[richting];
	while(vakje != nullptr){
		if(vakje->kleur == kl) return true;
		else if(vakje->kleur == kleur0) return false;
		vakje = vakje->buren[richting];
	}
	return false;
}

//Aangenomen dat het kan
void OthelloBord::vulrichting(int i, int j, int richting, char kl){
	BordVakje* vakje = get(i, j)->buren[richting];
	while(vakje->kleur != kl){
		vakje->kleur = kl;
		vakje = vakje->buren[richting];
	}
}

BordVakje* OthelloBord::maakrij(int aantal){
	BordVakje* start = new BordVakje;
	BordVakje* vorige = start;
	for(int i = 1;i < aantal;i++){
		BordVakje* nieuw = new BordVakje;
		vorige->buren[2] = nieuw;
		nieuw->buren[6] = vorige;
		vorige = nieuw;
	}
	return start;
}

void OthelloBord::wisselbeurt(){
	if(beurt == kleur1) beurt = kleur2;
	else beurt = kleur1;
}
