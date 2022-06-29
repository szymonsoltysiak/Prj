#include "SWektor.hh"
#include "SMacierz.hh"
#include "SKolumna.hh"
#include "rozmiar.h"
#include "LZespolona.hh"

using namespace std;

int main()
{
     char c;
     cin>>c;
     switch (c)
     {
     case 'z':
     SMacierz<LZespolona,ROZMIAR> MacierzZ, KopiaZ;
     SKolumna<LZespolona,ROZMIAR> WynikZ, BladZ;
     cin>>MacierzZ;
     KopiaZ=MacierzZ;
     MacierzZ.Eliminacja();
     WynikZ.Wynik(MacierzZ);
     cout<<endl<<"Wektor rozwiazan: "<<endl<<WynikZ<<endl;
     BladZ.Wynik(KopiaZ);
     BladZ=WynikZ*KopiaZ-BladZ;
     cout<<endl<<"Wektor bledu: "<<endl<<BladZ<<endl;
     break;

     case 'r':     
     SMacierz<double,ROZMIAR> MacierzR, KopiaR;
     SKolumna<double,ROZMIAR> WynikR, BladR;
     cin>>MacierzR;
     KopiaR=MacierzR;
     MacierzR.Eliminacja();
     WynikR.Wynik(MacierzR);
     cout<<endl<<"Wektor rozwiazan: "<<endl<<WynikR<<endl;
     BladR.Wynik(KopiaR);
     BladR=WynikR*KopiaR-BladR;
     cout<<endl<<"Wektor bledu: "<<endl<<BladR<<endl;
     break;   

     default:
          cout<<"Bledny znak"<<endl;
          return 1;
          break;
     }
}
