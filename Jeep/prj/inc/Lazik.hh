#ifndef LAZIK_HH
#define LAZIK_HH

#include "ObiektGeom.hh"
#include "Probka.hh"
#include "lacze_do_gnuplota.hh"
#include <memory>
#include <list>
using namespace std;

class Lazik : public ObiektGeom
{
  double _KatOrientacji;
  double _OdlDoPrzejechania;
  double _Szybkosc;
  list<shared_ptr<ProbkaRegolitu>> _ListaProbek;

public:
  Lazik(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID) : ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
  {
    (*this).set_Skala(0, 15);
    (*this).set_Skala(1, 20);
    (*this).set_Skala(2, 10);
  }

  Lazik(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID, double WspX, double WspY) : ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
  {
    (*this).set_Skala(0, 15);
    (*this).set_Skala(1, 20);
    (*this).set_Skala(2, 10);
    (*this).set_Polozenie(0, WspX);
    (*this).set_Polozenie(1, WspY);
    (*this).set_Kat(0);
  }

  void Przejazd(double Odl, PzG::LaczeDoGNUPlota Lacze);
  void Skret(double Kat, PzG::LaczeDoGNUPlota Lacze);
  void set_Odl(double Odl) { this->_OdlDoPrzejechania = Odl; }
  void set_Kat(double Kat) { this->_KatOrientacji = Kat; }
  double get_Kat() { return _KatOrientacji; }
  double get_Odl() {return _OdlDoPrzejechania;}
  void Kolko(PzG::LaczeDoGNUPlota Lacze);
  // void Rotacja(double Kat) {this->ObiektGeom::Rotacja(Kat); this->set_Kat(this->_KatOrientacji+Kat);}
  int get_Typ() override { return 1; }
};

class LazikSFR : public Lazik
{
  std::list<std::shared_ptr<ProbkaRegolitu>> _ListaProbek;

public:
  LazikSFR(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID) : Lazik(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
  {
  }
  void Podnies(shared_ptr<ProbkaRegolitu> Probka);
  void WyswietlListe()
  {
    if (_ListaProbek.empty())
      return;
    std::list<std::shared_ptr<ProbkaRegolitu>>::iterator Iter = _ListaProbek.begin();
    std::cout << "Lista probek: " << endl;
    for (; Iter != _ListaProbek.end(); ++Iter)
      std::cout << (*Iter)->get_NazwaObiektu() << endl;
  }
  std::list<std::shared_ptr<ProbkaRegolitu>> get_Lista() { return _ListaProbek; }
};

#endif