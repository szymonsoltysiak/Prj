#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObiektGeom.hh"
#include "Kolory.hh"
#include "Lazik.hh"
#include "Scena.hh"
#include "Probka.hh"

using namespace std;
void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota &rLacze);
void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom &rOb);
void PrzeliczDodaj(Lazik Ob1, Lazik Ob2, Lazik Ob3,
                   ProbkaRegolitu Pr1, ProbkaRegolitu Pr2, ProbkaRegolitu Pr3,
                   PzG::LaczeDoGNUPlota &Lacze);
void Menu(Scena Scena);
void Jazda(Scena Scena, PzG::LaczeDoGNUPlota &Lacze);
void Obrot(Scena Scena, PzG::LaczeDoGNUPlota &Lacze);

int main()
{
  PzG::LaczeDoGNUPlota Lacze;
  Inicjalizuj_Lacze(Lacze);
  if (!Inicjalizuj_PowierzchnieMarsa(Lacze))
    return 1;
  char wybor, numer;
  srand(time(NULL));

  LazikSFR Ob1("bryly_wzorcowe/szescian3.dat", "SFR", Kolor_JasnoNiebieski);
  shared_ptr<LazikSFR> ptr1 = make_shared<LazikSFR>(Ob1);
  Lazik Ob2("bryly_wzorcowe/szescian3.dat", "Perseverance", Kolor_Czerwony, 40, 40);
  shared_ptr<Lazik> ptr2 = make_shared<Lazik>(Ob2);
  Lazik Ob3("bryly_wzorcowe/szescian3.dat", "Curiosity", 10, -20, -40);
  shared_ptr<Lazik> ptr3 = make_shared<Lazik>(Ob3);
  ProbkaRegolitu Pr1("bryly_wzorcowe/szescian3.dat", "Regolit1", Kolor_JasnoNiebieski, rand() % 200 - 100, rand() % 200 - 100);
  shared_ptr<ProbkaRegolitu> Prob1 = make_shared<ProbkaRegolitu>(Pr1);
  ProbkaRegolitu Pr2("bryly_wzorcowe/szescian3.dat", "Regolit2", 10, rand() % 200 - 100, rand() % 200 - 100);
  shared_ptr<ProbkaRegolitu> Prob2 = make_shared<ProbkaRegolitu>(Pr2);
  ProbkaRegolitu Pr3("bryly_wzorcowe/szescian3.dat", "Regolit3", Kolor_Czerwony);
  shared_ptr<ProbkaRegolitu> Prob3 = make_shared<ProbkaRegolitu>(Pr3);

  PrzeliczDodaj(Ob1, Ob2, Ob3, Pr1, Pr2, Pr3, Lacze);
  cout << endl
       << "Start programu gnuplot" << endl
       << endl;
  Lacze.Rysuj();

  Scena Scena(ptr1);
  Scena.dodaj_do_listy(ptr2);
  Scena.dodaj_do_listy(ptr3);
  Scena.dodaj_do_listy(Prob1);
  Scena.dodaj_do_listy(Prob2);
  Scena.dodaj_do_listy(Prob3);

  std::cout << endl
            << "Start programu gnuplot" << endl
            << endl;
  Lacze.Rysuj();

  while (wybor != 'k')
  {
    Menu(Scena);
    if (Scena.getpointer().get_NazwaObiektu() == "SFR")
    {
      ptr1->WyswietlListe();
    }
    cin >> wybor;

    switch (wybor)
    {
    case 'j':
      Jazda(Scena, Lacze);
      break;
    case 'o':
      Obrot(Scena, Lacze);
      break;
    case 'w':
      cout << "1. FSR" << endl
           << "2. Curiosity" << endl
           << "3. Perseverance" << endl;
      cout << "Wpisz numer lazika" << endl;
      cin >> numer;
      switch (numer)
      {
      case '1':

        Scena.zamienLazik(ptr1);
        break;
      case '2':
        Scena.zamienLazik(ptr2);
        break;
      case '3':
        Scena.zamienLazik(ptr3);
        break;
      default:
        cout << "Nie ma takiego lazika" << endl
             << endl;
        break;
      }
      break;
    case 'p':
      if (Scena.getpointer().get_NazwaObiektu() == "SFR")
      {
        ptr1->Podnies(Prob1); Scena.usun(Prob1);
        ptr1->Podnies(Prob2); Scena.usun(Prob2);
        ptr1->Podnies(Prob3); Scena.usun(Prob3);
      }
      else
        cout << "To nie jest lazik SFR" << endl;
      break;
    case 'k':
      return 0;
    default:
      cout << "Bledna opcja" << endl
           << endl;
      break;
    }
  }
}

void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota &rLacze)
{
  rLacze.ZmienTrybRys(PzG::TR_3D);
  rLacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X / 2, ROMIAR_POWIERZCHNI_X / 2);
  rLacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y / 2, ROMIAR_POWIERZCHNI_Y / 2);
  rLacze.UstawZakresZ(-0, 90);
  rLacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok

  rLacze.Inicjalizuj(); // Tutaj startuje gnuplot.
}

void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom &rOb)
{
  PzG::InfoPlikuDoRysowania *wInfoPliku;

  wInfoPliku = &rLacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
  wInfoPliku->ZmienKolor(rOb.WezKolorID());
}

void PrzeliczDodaj(Lazik Ob1, Lazik Ob2, Lazik Ob3,
                   ProbkaRegolitu Pr1, ProbkaRegolitu Pr2, ProbkaRegolitu Pr3,
                   PzG::LaczeDoGNUPlota &Lacze)
{
  DodajDoListyRysowania(Lacze, Ob1);
  DodajDoListyRysowania(Lacze, Ob2);
  DodajDoListyRysowania(Lacze, Ob3);
  DodajDoListyRysowania(Lacze, Pr1);
  DodajDoListyRysowania(Lacze, Pr2);
  DodajDoListyRysowania(Lacze, Pr3);
  Ob1.Przelicz_i_Zapisz_Wierzcholki();
  Ob2.Przelicz_i_Zapisz_Wierzcholki();
  Ob3.Przelicz_i_Zapisz_Wierzcholki();
  Pr1.Przelicz_i_Zapisz_Wierzcholki();
  Pr2.Przelicz_i_Zapisz_Wierzcholki();
  Pr3.Przelicz_i_Zapisz_Wierzcholki();
}

void Menu(Scena Scena)
{

  cout << "======Menu====================================" << endl;
  cout << "Aktywny lazik:" << endl;
  cout << "         " << (Scena.getpointer()).get_NazwaObiektu() << endl;
  cout << "Polozenie x, y, z: " << endl
       << (Scena.getpointer()).get_Polozenie() << endl;
  cout << "Orientacja [st]: " << (Scena.getpointer()).get_Kat() << endl
       << endl;
  cout << "j - jazda na wprost" << endl
       << "o - zmien orientacje" << endl
       << "w - wybor lazika" << endl
       << "k - koniec dzialania programu" << endl
       << "p - podnies probke" << endl;
  cout << "==============================================" << endl;
}

void Jazda(Scena Scena, PzG::LaczeDoGNUPlota &Lacze)
{
  double Odl;
  cout << endl
       << "Podaj odleglosc:   ";
  cin >> Odl;
  Scena.przejazd(Odl, Lacze);
}

void Obrot(Scena Scena, PzG::LaczeDoGNUPlota &Lacze)
{
  double Kat;
  cout << endl
       << "Podaj kat [st]:   ";
  cin >> Kat;
  Scena.skret(Kat, Lacze);
}
