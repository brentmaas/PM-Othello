/**
 * Auteur: Brent Maas (s1826247)
 * Bestand: maasothello4.h
 * Functie: 
 * Getest op: Windows 10 + MSys2 (MinGW64) met g++ 8.2.0
 * Getest met: -std=c++17 -Wall -Wextra
 * Laatst bewerkt: 25/11/2018
 */

#ifndef MAASOTHELLO4_H
#define MAASOTHELLO4_H

const char kleur0 = '.', kleur1 = 'Z', kleur2 = 'W';

class BordVakje {
  public:
    char kleur;           //     7 0 1
    BordVakje* buren[8];  //     6   2
    BordVakje();          //     5 4 3
};

class OthelloBord {
  public:
	OthelloBord();
    OthelloBord(int m, int n);
    ~OthelloBord();
    OthelloBord kopieer();
    void bouwbord();
    void randomzet(char kl);
    void menszet(char kl, bool& gedaan, int i, int j);
    void drukaf();
    bool klaar();
    char winnaar();
    void doezet(int i, int j, char kl);
    bool magzet(int i, int j, char kl);
    BordVakje* get(int i, int j);
    int getHoogte();
    int getBreedte();
    char getBeurt();
    int getLaatsteBeurtI();
    int getLaatsteBeurtJ();
  private:
    BordVakje* ingang;
    int hoogte, breedte, zetten;
    char beurt;
    int laatsteBeurtI, laatsteBeurtJ;
    void rits (BordVakje* boven, BordVakje* onder);
    bool checkrichting(int i, int j, int richting, char kl);
    void vulrichting(int i, int j, int richting, char kl);
    BordVakje* maakrij (int aantal);
    void wisselbeurt();
};

#endif
