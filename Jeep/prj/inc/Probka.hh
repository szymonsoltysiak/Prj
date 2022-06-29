#ifndef PROBKA_HH
#define PROBKA_HH

#include "ObiektGeom.hh"
#include "lacze_do_gnuplota.hh"
#include <stdlib.h>  
#include <time.h>
//using namespace std;

class ProbkaRegolitu : public ObiektGeom
{

public:
  ProbkaRegolitu(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID) : ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
  {
    srand (time(NULL));
    (*this).set_Skala(0, 4);
    (*this).set_Skala(1, 4);
    (*this).set_Skala(2, 4);
    this->set_Polozenie(0, rand()%200-100);
    this->set_Polozenie(1, rand()%200-100);
  }

  ProbkaRegolitu(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID, double WspX, double WspY) : ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
  {
    (*this).set_Skala(0, 4);
    (*this).set_Skala(1, 4);
    (*this).set_Skala(2, 4);
    (*this).set_Polozenie(0, WspX);
    (*this).set_Polozenie(1, WspY);
  }
  int get_Typ() override {return 2;}
};





#endif