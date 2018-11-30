/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasothello4.h
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 *            Ubuntu 16.04 LTS met g++ 5.4.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 30/11/2018
 */

//Include guard, beschermt tegen meervoudige includen
#ifndef MAASOTHELLO4_H
#define MAASOTHELLO4_H

//De 'kleur' voor leeg, zwart, en wit vakje
const char kleur0 = '.', kleur1 = 'Z', kleur2 = 'W';

//Class met de pointerstructuur voor een vakje
class BordVakje {
  public:
	//Kleur van het vakje           Richting van elke index van buren
    char kleur; //                  7 0 1
    BordVakje* buren[8]; //         6   2
    BordVakje(); //Constructor      5 4 3
};

//Class voor het opslaan van het Othello bord en het omgaan met zetten
class OthelloBord {
  public:
	OthelloBord(); //Standaard constructor
    OthelloBord(int m, int n); //Constructor
    ~OthelloBord(); //Destructor
    OthelloBord(const OthelloBord& bord); //Kopieer constructor
    OthelloBord& operator=(const OthelloBord& bord); //Assignment operator
    void bouwbord(); //Functie om de pointerstructuur op te zetten
    void computerzet(char kl); //Functie om de computerzet te doen
    //Functie om de menselijke zet te verwerken
    void menszet(char kl, bool& gedaan, int i, int j);
    void print(); //Functie om het bord af te drukken
    bool klaar(); //Functie om te kijken of het spel is afgelopen
    char winnaar(int& verschil); //Functie om de winnaar te bepalen
    void doezet(int i, int j, char kl); //Functie om een zet uit te voeren
    bool magzet(int i, int j, char kl); //Functie om te kijken of een zet mag
    //Functie om de pointer naar een vakje op [i,j] te krijgen
    BordVakje* get(int i, int j);
    //Functie om de pointer naar een vakje op [i,j] te krijgen,
    //const variant voor de assignment operator
    BordVakje* get(int i, int j) const;
    //Getters voor breedte, hoogte, beurt, en positie van laatste beurt
    int getBreedte();
    int getHoogte();
    char getBeurt();
    int getLaatsteBeurtI();
    int getLaatsteBeurtJ();
  private:
    //Eerste vakje op [0,0]
    BordVakje* ingang;
    //Hoogte en breedte van het bord, aantal zetten dat is gedaan
    int hoogte, breedte, zetten;
    char beurt; //Huidige beurt
    int laatsteBeurtI, laatsteBeurtJ; //Positie van laatste zet
    //Functie om twee pointerrijen te verbinden
    void rits (BordVakje* boven, BordVakje* onder);
    //Functie om een pointerrij te maken
    BordVakje* maakrij (int aantal);
    //Functie om te kijken of een bepaalde richting een zet valide maakt
    bool checkrichting(int i, int j, int richting, char kl);
    //Functie om een richting van een zet uit te voeren
    void vulrichting(int i, int j, int richting, char kl);
    void wisselbeurt(); //Functie om de beurt te wisselen
};

#endif
