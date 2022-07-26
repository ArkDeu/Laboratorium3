#include <iostream>
#define LICZBA_ELEMENTOW 10

using namespace std;

class element {
  protected:
    double prad;
    double napiecie;
    double moc;
    double czestotliwosc;
    std::string nazwa;
  public:
    virtual ~element(){};
    element() {nazwa = "element"; czestotliwosc = 1.0; napiecie = prad = moc = 0.0;}
    element(const std::string arg) {nazwa = arg; napiecie = czestotliwosc = 1.0; prad = moc = 0.0;}
    virtual void wymuszenieU(double) = 0;
    friend int obwod(element*, element*);
};

int obwod(element *e1, element *e2) {
  bool pradMatch = false;
  bool napiecieMatch = false;
  if (e1->prad == e2->prad) {
    pradMatch = true;
    return 1;
  }
  if (e1->napiecie == e2->napiecie) {
    napiecieMatch = true;
    return 2;
  }
  if ((pradMatch && !napiecieMatch) || (!pradMatch && napiecieMatch)) {
    //std::string matchType = (pradMatch)?"prad":"napiecie";
    std::string matchType;
    if (pradMatch) {
      matchType = "prad";
    } else {
      matchType = "napiecie";
    } return 3;

    cout << "elementy: " << e1->nazwa.c_str() << " oraz: " << e2->nazwa.c_str() << " maja taki sam: " << matchType.c_str() << endl;
  } else {
    if (pradMatch && napiecieMatch) {
      cout << "elementy: " << e1->nazwa.c_str() << " oraz: " << e2->nazwa.c_str() << " sa nieokreslone." << endl;
    } else {
      cout << "elementy: " << e1->nazwa.c_str() << " oraz: " << e2->nazwa.c_str() << " sa nie polaczone." << endl;
    }
  }
  return 0;
}

class cewka : public element {
    string name;
  protected:
    std::string nazwa; 
    double prad;
    double napiecie;
    double moc;
    double czestotliwosc;
    double L;
//indukcyjność
  public:
   string getName(){
        return name;
    }
   void setName(string newName){
        name = newName;
    }
    cewka() {nazwa = "cewka"; L = 1.0;}
    cewka(const std::string arg) {nazwa = arg; L = 1.0;}
    cewka(const std::string arg, double argL) {nazwa = arg; L = argL;}
    void wymuszenieU(double);
};

void cewka::wymuszenieU(double u) {
  napiecie = u;
  if (czestotliwosc > 0.0) {
    prad = u/(6.28*czestotliwosc*L);
  }
}

class rezystor : public element {
    string name;
protected:
    double R;
//rezystancja
    std::string nazwa;
    double prad;
    double napiecie;
    double moc;
    double czestotliwosc;

private:
public:
    string getName(){
        return name;
    }
    void setName(string newName){
        name = newName;
   }
    rezystor() {nazwa = "rezystor"; R = 2.0;}
    rezystor(const std::string arg) {nazwa = arg; R = 2.0;}
    rezystor(const std::string arg, double argR) {nazwa = arg; R = argR;}
    void wymuszenieU(double);
};

void rezystor::wymuszenieU(double u) {
  napiecie = u;
  if (czestotliwosc > 0.0) {
    prad = u/(6.28*czestotliwosc*R);
  }
}


class kondensator : public element {
string name;
protected:
    double C;
//pojemność
    std::string nazwa;
    double prad;
    double napiecie;
    double moc;
    double czestotliwosc;
    
private:
public:
    string getName(){
        return name;
    }
    void setName(string newName){
        name = newName;
    }
    kondensator() {nazwa = "kondensator"; C = 3.0;}
    kondensator(const std::string arg) {nazwa = arg; C = 3.0;}
    kondensator(const std::string arg, double argC) {nazwa = arg; C = argC;}
    void wymuszenieU(double);
};

void kondensator::wymuszenieU(double u) {
  napiecie = u;
  if (czestotliwosc > 0.0) {
    prad = u/(6.28*czestotliwosc*C);
  }
}



int main() {
    kondensator k1;
    k1.setName("kondensator");
    cout << k1.getName() << endl; 

    rezystor r1;
    r1.setName("rezystor");
    cout << r1.getName() << endl;

   cewka c1;
    c1.setName("cewka");
    cout << c1.getName() << endl;
    

  element* tab[LICZBA_ELEMENTOW];
  for (int i=0; i<(LICZBA_ELEMENTOW); i++) {
    tab[0] = new cewka("cewka1");
  }
  tab[0] = new cewka("cewka1");
  tab[1] = new cewka("rezystor", 3.0);
  tab[2] = new cewka("cewka3");
  tab[3] = new cewka("cewka4", 3.0);
  tab[4] = new cewka("cewka5");
  tab[5] = new cewka("kondensator", 3.0);
  tab[6] = new cewka("cewka7");
  tab[7] = new cewka("cewka8", 3.0);
  tab[8] = new cewka("kondensator9");
  tab[9] = new cewka("cewka10", 3.0);
  tab[0]->wymuszenieU(10);
  tab[1]->wymuszenieU(10);
  for (int i=0; i<(LICZBA_ELEMENTOW-1); i++) {
    for (int j=i+1; j<LICZBA_ELEMENTOW; j++) {
      obwod(tab[i], tab[j]);
    }
  }
  for (int i=0; i<LICZBA_ELEMENTOW; i++) {
    delete tab[i];
  }
  return 0;
}