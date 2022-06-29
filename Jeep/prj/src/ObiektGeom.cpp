#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <memory>
#include "ObiektGeom.hh"

using namespace std;

ObiektGeom::ObiektGeom(const char *sNazwaPliku_BrylaWzorcowa,
                       const char *sNazwaObiektu,
                       int KolorID) : _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  (*this).Rotacja(0);
  this->Przelicz_i_Zapisz_Wierzcholki();
}


bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
  ifstream StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open()))
  {
    cerr << endl
         << "Nie mozna otworzyc jednego z plikow:" << endl
         << "    " << _NazwaPliku_BrylaWzorcowa << endl
         << "    " << _NazwaPliku_BrylaRysowana << endl
         << endl;
    return false;
  }

  Wektor3D Wsp;
  int Indeks_Wiersza = 0;
  int Linijka = 0;

  StrmWe >> Wsp;

  if (StrmWe.fail())
    return false;

  do
  {
    for (int i = 0; i < 3; ++i)
    {
      Wsp[i] = Wsp[i] * (*this)._Skala[i];
    }

    Wsp = (*this).get_MacRotacji() * Wsp;
    Wsp = Wsp + (*this)._Polozenie;

    if(Linijka==0)
    {
      this->set_Obrys(0,0,Wsp[0]);
      this->set_Obrys(0,1,Wsp[1]);
      this->set_Obrys(1,0,Wsp[0]);
      this->set_Obrys(1,1,Wsp[1]);
    }
    else
    {
      if(Wsp[0]>this->get_Obrys(0,0)) this->set_Obrys(0,0,Wsp[0]);
      if(Wsp[1]>this->get_Obrys(0,1)) this->set_Obrys(0,1,Wsp[1]);
      if(Wsp[0]<this->get_Obrys(1,0)) this->set_Obrys(1,0,Wsp[0]);
      if(Wsp[1]<this->get_Obrys(1,1)) this->set_Obrys(1,1,Wsp[1]);
    }

    StrmWy << Wsp << endl;
    ++Indeks_Wiersza;

    if (Indeks_Wiersza >= 4)
    {
      StrmWy << endl;
      Indeks_Wiersza = 0;
    }

    StrmWe >> Wsp;
    ++Linijka;

  } while (!StrmWe.fail());

  if (!StrmWe.eof())
    return false;

  return Indeks_Wiersza == 0 && !StrmWy.fail();
}

void ObiektGeom::Rotacja(double KatS)
{
  double Kat = (KatS * 3.14) / 180;
  (*this).set_MacRotacji(0, 0, cos(Kat));
  (*this).set_MacRotacji(0, 1, (-1 * sin(Kat)));
  (*this).set_MacRotacji(0, 2, 0);

  (*this).set_MacRotacji(1, 0, sin(Kat));
  (*this).set_MacRotacji(1, 1, cos(Kat));
  (*this).set_MacRotacji(1, 2, 0);

  (*this).set_MacRotacji(2, 0, 0);
  (*this).set_MacRotacji(2, 1, 0);
  (*this).set_MacRotacji(2, 2, 1);
}

void ObiektGeom::Translacja(double Odleglosc, double KatS)
{
  double Kat = (KatS * 3.14) / 180;
  (*this).set_Polozenie(0, (*this).get_Polozenie(0) + Odleglosc * sin(Kat));
  (*this).set_Polozenie(1, (*this).get_Polozenie(1) + Odleglosc * cos(Kat));
}

int ObiektGeom::Czy_Kolizja(std::shared_ptr<ObiektGeom> Obiekt)
{
    if( (
      (this->get_Obrys(0,0)<=Obiekt->get_Obrys(0,0) && this->get_Obrys(0,0)>=Obiekt->get_Obrys(1,0) ) ||
      (this->get_Obrys(1,0)<=Obiekt->get_Obrys(0,0) && this->get_Obrys(1,0)>=Obiekt->get_Obrys(1,0)) ||
      (this->get_Obrys(0,0)>=Obiekt->get_Obrys(0,0) && this->get_Obrys(1,0)<=Obiekt->get_Obrys(0,0)) ||
      (this->get_Obrys(0,0)>=Obiekt->get_Obrys(1,0) && this->get_Obrys(1,0)<=Obiekt->get_Obrys(1,0)) )
      && 
    ((this->get_Obrys(0,1)<=Obiekt->get_Obrys(0,1) && this->get_Obrys(0,1)>=Obiekt->get_Obrys(1,1)) ||
     (this->get_Obrys(1,1)<=Obiekt->get_Obrys(0,1) && this->get_Obrys(1,1)>=Obiekt->get_Obrys(1,1)) || 
     (this->get_Obrys(0,1)>=Obiekt->get_Obrys(0,1) && this->get_Obrys(1,1)<=Obiekt->get_Obrys(0,1)) ||
     (this->get_Obrys(0,1)>=Obiekt->get_Obrys(1,1) && this->get_Obrys(1,1)<=Obiekt->get_Obrys(1,1)) ) )
    {
      if(Obiekt->get_Typ()==1) return 1;
      if(Obiekt->get_Typ()==2) return 2;
    }
    return 0;
}