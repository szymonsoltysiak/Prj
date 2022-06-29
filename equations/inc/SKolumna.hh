#ifndef KOLUMNA_HH
#define KOLUMNA_HH

#include "rozmiar.h"
#include "SWektor.hh"
#include "SMacierz.hh"
#include <iostream>

template <typename STyp, int SWymiar>
class SKolumna {
    STyp  _Wsp[SWymiar];
  public:
  
    STyp  operator [] (unsigned int Ind) const { return _Wsp[Ind]; }
    STyp &operator [] (unsigned int Ind)       { return _Wsp[Ind]; }
    SKolumna<STyp,SWymiar> operator * (const SMacierz<STyp,SWymiar> Mac);
    SKolumna<STyp,SWymiar> operator - (SKolumna<STyp,SWymiar> Kolumna);

    void Wynik(SMacierz<STyp,SWymiar> M){
        for(int i=0;i<SWymiar;i++){
          (*this)[i]=M[i][SWymiar];
        }
      }

};

template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &StrmWyj, const SKolumna<STyp,SWymiar>& W)
{
  for (unsigned int Ind = 0; Ind < SWymiar; ++Ind) {
    StrmWyj << " " << W[Ind];
  }  
  return StrmWyj;
}

template <typename STyp, int SWymiar>
SKolumna<STyp,SWymiar> SKolumna<STyp,SWymiar>::operator * (const SMacierz<STyp,SWymiar> Mac)
{
  SKolumna<STyp,SWymiar> Wynik;

    for(int i=0;i<SWymiar;i++){
        Wynik[i]=0;
        for(int j=0;j<SWymiar;j++){
	    Wynik[i] = Wynik[i]+Mac[i][j]*(*this)[j];
    }
    }
	return Wynik;
}


template <typename STyp, int SWymiar>
SKolumna<STyp,SWymiar> SKolumna<STyp,SWymiar>::operator - (SKolumna<STyp,SWymiar> Kolumna)
{
  SKolumna<STyp,SWymiar> Wynik;

  for(int i=0;i<SWymiar;i++){
      Wynik[i]=(*this)[i]-Kolumna[i];
  }

  return Wynik;
}


#endif