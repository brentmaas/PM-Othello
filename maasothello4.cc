#include <iostream>
#include "maasothello4.h"
using namespace std;

BordVakje::BordVakje():
	kleur(kleur0){
	for(int i = 0;i < 8;i++) buren[i] = nullptr;
}

OthelloBord::OthelloBord():
	hoogte(8), breedte(8){
	bouwbord();
}

OthelloBord::~OthelloBord() {
	
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
	
}

void OthelloBord::menszet(char kl, bool& gedaan, int& i, int& j){
	
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
	bool klaar = true;
	for(int i = 0;i < hoogte;i++){
		for(int j = 0;j < breedte;j++){
			klaar = klaar || magzet(i, j, kleur1);
			klaar = klaar || magzet(i, j, kleur2);
		}
	}
	return klaar;
}

int OthelloBord::gewonnen(char& kl){
	
	
	return 0;
}

void OthelloBord::doezet(int i, int j, char kl){
	get(i, j)->kleur = kl;
}

bool OthelloBord::magzet(int i, int j, char kl){
	
	
	return false;
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