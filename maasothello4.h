#ifndef MAASOTHELLO_H
#define MAASOTHELLO_H

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
    void randomzet(char kl, int & i, int & j);
    void menszet(char kl, bool & gedaan, int & i, int & j);
    void drukaf();
    bool klaar();
    int gewonnen(char & kl);
    void doezet(int i, int j, char kl);
    void magzet(int i, int j, char kl);
    // TODO
  private:
    BordVakje* ingang;
    int hoogte, breedte;
    void rits (BordVakje* boven, BordVakje* onder);
    BordVakje* maakrij (int aantal);
    // TODO
};

#endif