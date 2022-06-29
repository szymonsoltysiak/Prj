#include "Scena.hh"
#include <iostream>
#include <unistd.h>
#include <cmath>
#include <algorithm>

using namespace std;

Scena::Scena(shared_ptr<Lazik> ref)
{
    this->_AktywnyLazik = ref;
}

Lazik &Scena::getpointer()
{
    return *(_AktywnyLazik.get());
}

void Scena::zamienLazik(shared_ptr<Lazik> ptr)
{
    (this->getpointer()).set_Kolor(15);
    this->_AktywnyLazik = ptr;
    (this->getpointer()).set_Kolor(3);
}

void Scena::dodaj_do_listy(shared_ptr<ObiektGeom> Obiekt)
{
    (this->_ObiektySceny).push_front(Obiekt);
    Obiekt->Przelicz_i_Zapisz_Wierzcholki();
}

void Scena::przejazd(double Odl, PzG::LaczeDoGNUPlota Lacze)
{
    this->getpointer().set_Odl(Odl);
    for (int i = this->getpointer().get_Odl(); i > 0; --i)
    {
        usleep(10000);
        this->getpointer().Translacja(1, this->getpointer().get_Kat());
        std::list<std::shared_ptr<ObiektGeom>>::iterator Iter = _ObiektySceny.begin();
        for(; Iter != _ObiektySceny.end(); ++Iter)
        {
            if(this->getpointer().Czy_Kolizja((*Iter))==1 && this->getpointer().get_NazwaObiektu() != (*Iter)->get_NazwaObiektu() )  
            {std::cout<<endl<<"KOLIZJA!!!"<<endl; 
            //this->getpointer().Translacja(-10, this->getpointer().get_Kat());
            for(int j=0;j<15;++j) {
                usleep(10000);
                this->getpointer().Translacja(-1, this->getpointer().get_Kat());
                this->getpointer().Przelicz_i_Zapisz_Wierzcholki();
                Lacze.Rysuj();}
            this->getpointer().Przelicz_i_Zapisz_Wierzcholki();
            return;}
        }
        this->getpointer().Przelicz_i_Zapisz_Wierzcholki();
        Lacze.Rysuj();
    }
}

void Scena::skret(double Kat, PzG::LaczeDoGNUPlota Lacze)
{
    this->getpointer().set_Kat(fmod(this->getpointer().get_Kat(), 360));
    int i = this->getpointer().get_Kat();
    this->getpointer().set_Kat(this->getpointer().get_Kat() + Kat);
    if (Kat > 0)
    {
        for (; i <= this->getpointer().get_Kat(); ++i)
        {
            usleep(5000);
            this->getpointer().Rotacja(i);
            this->getpointer().Przelicz_i_Zapisz_Wierzcholki();
            Lacze.Rysuj();
        }
    }
    if (Kat < 0)
    {
        for (; i >= this->getpointer().get_Kat(); --i)
        {
            usleep(5000);
            this->getpointer().Rotacja(i);
            this->getpointer().Przelicz_i_Zapisz_Wierzcholki();
            Lacze.Rysuj();
        }
    }
}