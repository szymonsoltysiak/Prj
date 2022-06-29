#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory>
#include "Lazik.hh"
#include "ObiektGeom.hh"
//#include "lacze_do_gnuplota.hh"
using namespace std;


class Scena
{
    shared_ptr<Lazik> _AktywnyLazik;
    list<shared_ptr<ObiektGeom>> _ObiektySceny;

public:
    Scena(shared_ptr<Lazik> ref);
    Lazik &getpointer();
    void zamienLazik(shared_ptr<Lazik> ref);
    void dodaj_do_listy(shared_ptr<ObiektGeom> Obiekt);
    void usun(shared_ptr<ObiektGeom> Obiekt) { _ObiektySceny.remove(Obiekt);} 
    void przejazd(double Odl, PzG::LaczeDoGNUPlota Lacze);
    void skret(double Kat, PzG::LaczeDoGNUPlota Lacze);
    // void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota &rLacze);
    // void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom &rOb);
};

#endif