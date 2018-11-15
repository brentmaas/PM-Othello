#include <iostream>
#include "maasothello4.h"
using namespace std;

BordVakje::BordVakje():
	kleur('.'){
	for(int i = 0;i < 8;i++) buren[i] = nullptr;
}

OthelloBord::OthelloBord():
	hoogte(8), breedte(8){
	ingang = maakrij(breedte);
	BordVakje* vorige = ingang;
	for(int i = 1;i < hoogte;i++){
		BordVakje* nieuw = maakrij(breedte);
		rits(vorige, nieuw);
		vorige = nieuw;
	}
}

OthelloBord::~OthelloBord() {
	
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