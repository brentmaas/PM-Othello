#include <iostream>
#include <cstdlib>
#include <ctime>
#include "maasothello4.h"
using namespace std;

BordVakje::BordVakje():
	kleur(kleur0){
	for(int i = 0;i < 8;i++) buren[i] = nullptr;
}

//Officieel begint zwart
OthelloBord::OthelloBord(): hoogte(8), breedte(8), beurt(kleur2), speler1(kleur1), speler2(kleur2){
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

void OthelloBord::bouwbord(){
	ingang = maakrij(breedte);
	BordVakje* vorige = ingang;
	for(int i = 1;i < hoogte;i++){
		BordVakje* nieuw = maakrij(breedte);
		rits(vorige, nieuw);
		vorige = nieuw;
	}
	
	get(breedte / 2 - 1, hoogte / 2 - 1)->kleur = kleur1;
	get(breedte / 2 - 1, hoogte / 2)->kleur = kleur2;
	get(breedte / 2, hoogte / 2 - 1)->kleur = kleur2;
	get(breedte / 2, hoogte / 2)->kleur = kleur1;
}

void OthelloBord::randomzet(char kl, int& i, int& j){
	i = rand() % hoogte;
	j = rand() % breedte;
	while(!magzet(i, j, kl)){
		i = rand() % hoogte;
		j = rand() % breedte;
	}
	doezet(i, j, kl);
}

void OthelloBord::menszet(char kl, bool& gedaan, int& i, int& j){
	gedaan = magzet(i, j, kl);
	if(gedaan) doezet(i, j, kl);
}

void OthelloBord::drukaf(){
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
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			if(magzet(i, j, beurt)) return false;
		}
	}
	return true;
}

int OthelloBord::gewonnen(char& kl){
	
	
	return 0;
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
}

bool OthelloBord::magzet(int i, int j, char kl){
	//Deze is fout btw
	/*BordVakje* vakje = get(i, j);
	if(vakje->kleur != kleur0) return false;
	BordVakje* boven = vakje->buren[0];
	BordVakje* rechtsboven = vakje->buren[1];
	BordVakje* rechts = vakje->buren[2];
	BordVakje* rechtsonder = vakje->buren[3];
	BordVakje* onder = vakje->buren[4];
	BordVakje* linksonder = vakje->buren[5];
	BordVakje* links = vakje->buren[6];
	BordVakje* linksboven = vakje->buren[7];
	char anderekleur = kleur1;
	if(kl == kleur1) anderekleur = kleur2;
	bool b = boven->kleur == anderekleur;
	bool rb = rechtsboven->kleur == anderekleur;
	bool r = rechts->kleur == anderekleur;
	bool ro = rechtsonder->kleur == anderekleur;
	bool o = onder->kleur == anderekleur;
	bool lo = linksonder->kleur == anderekleur;
	bool l = links->kleur == anderekleur;
	bool lb = linksboven->kleur == anderekleur;
	boven = boven->buren[0];
	rechtsboven = rechtsboven->buren[1];
	rechts = rechts->buren[2];
	rechtsonder = rechtsonder->buren[3];
	onder = onder->buren[4];
	linksonder = linksonder->buren[5];
	links = links->buren[6];
	linksboven = linksboven->buren[7];
	while(b || rb || r || ro || o || lo || l || lb){
		if(b && boven != nullptr && boven->kleur == kleur0) return true;
		else if(boven == nullptr || boven->kleur == kl) b = false;
		if(rb && rechtsboven != nullptr && rechtsboven->kleur == kleur0) return true;
		else if(rechtsboven == nullptr || rechtsboven->kleur == kl) rb = false;
		if(r && rechts != nullptr && rechts->kleur == kleur0) return true;
		else if(rechts == nullptr || rechts->kleur == kl) r = false;
		if(ro && rechtsonder != nullptr && rechtsonder->kleur == kleur0) return true;
		else if(rechtsonder == nullptr || rechtsonder->kleur == kl) ro = false;
		if(o && onder != nullptr && onder->kleur == kleur0) return true;
		else if(onder == nullptr || onder->kleur == kl) o = false;
		if(lo && linksonder != nullptr && linksonder->kleur == kleur0) return true;
		else if(linksonder == nullptr || linksonder->kleur == kl) lo = false;
		if(l && links != nullptr && links->kleur == kleur0) return true;
		else if(links == nullptr || links->kleur == kl) l = false;
		if(lb && linksboven != nullptr && linksboven->kleur == kleur0) return true;
		else if(linksboven == nullptr || linksboven->kleur == kl) lb = false;
	}*/
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
	if(i < 0 || i > hoogte || j < 0 || j > breedte) return nullptr;
	BordVakje* vakje = ingang;
	for(int k = 0;k < i;k++) vakje = vakje->buren[4];
	for(int k = 0;k < j;k++) vakje = vakje->buren[2];
	return vakje;
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