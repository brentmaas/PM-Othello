#ifndef MAASOTHELLO_H
#define MAASOTHELLO_H

const char kleur0 = '.', kleur1 = 'W', kleur2 = 'Z';

class BordVakje {
  public:
    char kleur;           //     7 0 1
    BordVakje* buren[8];  //     6   2
    BordVakje();          //     5 4 3
};

class OthelloBord {
  public:
    OthelloBord();
    ~OthelloBord();
    void bouwbord();
    void randomzet(char kl, int& i, int& j);
    void menszet(char kl, bool& gedaan, int& i, int& j);
    void drukaf();
    bool klaar();
    int gewonnen(char& kl);
    void doezet(int i, int j, char kl);
    bool magzet(int i, int j, char kl);
    BordVakje* get(int i, int j);
  private:
    BordVakje* ingang;
    int hoogte, breedte;
    char beurt, speler1, speler2;
    void rits (BordVakje* boven, BordVakje* onder);
    bool checkrichting(int i, int j, int richting, char kl);
    void vulrichting(int i, int j, int richting, char kl);
    BordVakje* maakrij (int aantal);
};

#endif