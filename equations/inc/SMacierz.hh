#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "rozmiar.h"
#include "SWektor.hh"
#include <iostream>

template <typename STyp, int SWymiar>
class SMacierz {
  
  SWektor<STyp,SWymiar> Wiersz[SWymiar];
  public:
  //SMacierz() {for(int i=0;i<SWymiar;++i) Wiersz[i].SWektor();}
  /*Wektor get(int Ind) const{
    return Wiersz[Ind];
  }
  void set(int Ind, Wektor Wart){
    Wiersz[Ind]=Wart;
  }*/

  SWektor<STyp,SWymiar>  operator [] (unsigned int Ind) const { return Wiersz[Ind]; }
  SWektor<STyp,SWymiar> &operator [] (unsigned int Ind)       { return Wiersz[Ind]; }

  void OdejmowanieWiersza(int i, int j);

  void Zamiana(); 
  void ZerowanieDol();
  void ZerowanieGora();
  void Eliminacja();
};

template <typename STyp, int SWymiar>
std::istream& operator >> (std::istream &StrmWej,SMacierz<STyp,SWymiar>& M)
{
  for (unsigned int Ind = 0; Ind < SWymiar; ++Ind) {
    StrmWej >> M[Ind];
  }  
  return StrmWej;
}

template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &StrmWyj, const SMacierz<STyp,SWymiar>& M)
{
  for (unsigned int Ind = 0; Ind < SWymiar; ++Ind) {
    StrmWyj << M[Ind] << " "<<std::endl;
  }  
  return StrmWyj;
}

template <typename STyp, int SWymiar>
void SMacierz<STyp,SWymiar>::OdejmowanieWiersza(int i, int j)
{
    std::cout<<"Odejmujemy od wiersza "<<j+1<<". wiersz "<<i+1<<". pomnozony przez "<<(*this)[j][i]<<std::endl;
    (*this)[j]=(*this)[j]-(*this)[i]*((*this)[j][i]);
    std::cout<<(*this)<<std::endl;
}

template <typename STyp, int SWymiar>
void SMacierz<STyp,SWymiar>::Zamiana()
{
  if((*this)[0][0]!=0){
    for(int i=1;i<ROZMIAR;i++)
    {
        if((*this)[0][i]!=0){ 
            swapW((*this)[0],(*this)[i]);
            std::cout<<"Zamieniamy wiersz 1. z wierszem "<<++i<<"."<<std::endl;
            std::cout<<(*this)<<std::endl;
            break;}
    }
    }
}

template <typename STyp, int SWymiar>
void SMacierz<STyp,SWymiar>::ZerowanieDol()
{
    for(int i=0;i<ROZMIAR;i++)
    {
        std::cout<<"Dzielimy wiersz "<<i+1<<". przez "<<(*this)[i][i]<<"."<<std::endl;
        (*this)[i]=(*this)[i]*(1/(*this)[i][i]);
        std::cout<<(*this)<<std::endl;
        for(int j=i+1;j<ROZMIAR;j++)
        {
            if( (*this)[j][i]!=0 ){
                (*this).OdejmowanieWiersza(i,j);
            }
        }
    }
}

template <typename STyp, int SWymiar>
void SMacierz<STyp,SWymiar>::ZerowanieGora()
{
  for(int i=ROZMIAR-1;i>0;i--){
        for(int j=i-1;j>=0;j--){
            (*this).OdejmowanieWiersza(i,j);
        }
    }
}


template <typename STyp, int SWymiar>
void SMacierz<STyp,SWymiar>::Eliminacja()
{
  (*this).Zamiana();
  (*this).ZerowanieDol();  
  (*this).ZerowanieGora();  
}


#endif
