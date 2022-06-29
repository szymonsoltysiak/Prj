#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include <memory>
#include "SWektor.hh"
#include "SMacierz.hh"

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA "pliki_do_rysowania"

class ObiektGeom
{

  std::string _NazwaPliku_BrylaWzorcowa;
  std::string _NazwaPliku_BrylaRysowana;
  std::string _NazwaObiektu;
  int _KolorID;
  Wektor3D _Polozenie;
  Wektor3D _Skala;
  MacRot _MacRotacji;
  Wektor2D _Obrys[2];

public:
  void set_Obrys (int i, int j, double n) {_Obrys[i][j]=n;}
  void set_Skala(int i, double n) { _Skala[i] = n; }
  void set_Polozenie(int i, double n) { _Polozenie[i] = n; }
  void set_MacRotacji(int i, int j, double n) { _MacRotacji[i][j] = n; }
  void set_Kolor(int Kolor) { _KolorID = Kolor; }
  void set_Polozenie(Wektor3D Wektor)
  {
    for (int i = 0; i < 3; ++i)
    {
      _Polozenie[i] = Wektor[i];
    }
  }

  void set_Skala(Wektor3D Wektor)
  {
    for (int i = 0; i < 3; ++i)
    {
      _Skala[i] = Wektor[i];
    }
  }

  double get_Obrys(int i, int j) {return _Obrys[i][j];}
  double get_Skala(int i) const { return _Skala[i]; }
  double get_Polozenie(int i) const { return _Polozenie[i]; }
  double get_MacRotacji(int i, int j) const { return _MacRotacji[i][j]; }
  std::string get_NazwaObiektu() { return _NazwaObiektu; }
  MacRot get_MacRotacji() { return _MacRotacji; }
  Wektor3D get_Polozenie() { return _Polozenie; }
  Wektor3D get_Skala() { return _Skala; }
  Wektor2D get_Obrys(int i) {return _Obrys[i];}

  ObiektGeom(const char *sNazwaPliku_BrylaWzorcowa, const char *sNazwaObiektu, int KolorID);

  int WezKolorID() const { return _KolorID; }

  const std::string &WezNazweObiektu() const { return _NazwaObiektu; }

  const std::string &WezNazwePliku_BrylaRysowana() const
  {
    return _NazwaPliku_BrylaRysowana;
  }

  bool Przelicz_i_Zapisz_Wierzcholki();

  void Rotacja(double KatS);
  void Translacja(double Odlegosc, double KatS);
  virtual int get_Typ() {return 0;}
  int Czy_Kolizja(std::shared_ptr<ObiektGeom> Obiekt); 
};

#endif
