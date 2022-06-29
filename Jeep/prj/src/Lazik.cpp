#include <iostream>
#include <unistd.h>
#include <cmath>
#include <algorithm>
#include "lacze_do_gnuplota.hh"
#include "Lazik.hh"

using namespace std;

void Lazik::Przejazd(double Odl, PzG::LaczeDoGNUPlota Lacze)
{
    this->set_Odl(Odl);
    for (int i = this->_OdlDoPrzejechania; i > 0; --i)
    {
        usleep(10000);
        this->Translacja(1, this->_KatOrientacji);
        this->Przelicz_i_Zapisz_Wierzcholki();
        Lacze.Rysuj();
    }
}

void Lazik::Skret(double Kat, PzG::LaczeDoGNUPlota Lacze)
{
    this->set_Kat(fmod(this->_KatOrientacji, 360));
    int i = this->_KatOrientacji;
    this->set_Kat(this->_KatOrientacji + Kat);
    if (Kat > 0)
    {
        for (; i <= this->_KatOrientacji; ++i)
        {
            usleep(5000);
            this->Rotacja(i);
            this->Przelicz_i_Zapisz_Wierzcholki();
            Lacze.Rysuj();
        }
    }
    if (Kat < 0)
    {
        for (; i >= this->_KatOrientacji; --i)
        {
            usleep(5000);
            this->Rotacja(i);
            this->Przelicz_i_Zapisz_Wierzcholki();
            Lacze.Rysuj();
        }
    }
}

void Lazik::Kolko(PzG::LaczeDoGNUPlota Lacze)
{
    for (int i = 0; i < 36; i++)
    {
        this->Przejazd(2, Lacze);
        this->Skret(10, Lacze);
    }
}
void LazikSFR::Podnies(shared_ptr<ProbkaRegolitu> Probka)
{
    if (this->Czy_Kolizja(Probka) == 2)
    {
        Probka->set_Polozenie(0, 200);
        Probka->set_Polozenie(1, 200);
        (this->_ListaProbek).push_front(Probka);
        Probka->Przelicz_i_Zapisz_Wierzcholki();
    }
}
