#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "rozmiar.h"
#include "SWektor.hh"
#include <iostream>


class Macierz {
  
  SWektor<STyp,SWymiar> Wiersz[ROZMIAR];
  public:
  /*SWektor get(int Ind) const{
    return Wiersz[Ind];
  }
  void set(int Ind, SWektor Wart){
    Wiersz[Ind]=Wart;
  }*/

  const SWektor<STyp,SWymiar>& operator[](size_t el) const {return Wiersz[el];}
  SWektor<STyp,SWymiar>& operator[](size_t el) {return Wiersz[el];}

  void Eliminacja();
  
};

std::istream& operator >> (std::istream &Strm, Macierz &Mac)
{
    //SWektor tmp;
    for(int i=0;i<ROZMIAR;i++)
    {
        Strm>>Mac[i];
    }
    return Strm;
}

std::ostream& operator << (std::ostream &Strm, const Macierz &Mac)
{
    for(int i=0;i<ROZMIAR;i++)
    {
        Strm<<Mac[i]<<std::endl;
    }
    return Strm;
} 

void Macierz::Eliminacja()
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
    //(*this)[0]=(*this)[0]*(1/(*this)[0][0]);

    for(int i=0;i<ROZMIAR;i++)
    {
        std::cout<<"Dzielimy wiersz "<<i+1<<". przez "<<(*this)[i][i]<<"."<<std::endl;
        (*this)[i]=(*this)[i]*(1/(*this)[i][i]);
        std::cout<<(*this)<<std::endl;
        for(int j=i+1;j<ROZMIAR;j++)
        {
            if( (*this)[j][i]!=0 ){
                std::cout<<"Odejmujemy od wiersza "<<j+1<<". wiersz "<<i+1<<". pomnozony przez "<<(*this)[j][i]<<std::endl;
                (*this)[j]=(*this)[j]-(*this)[i]*((*this)[j][i]);
                std::cout<<(*this)<<std::endl;
            }
        }
    }

    for(int i=ROZMIAR-1;i>0;i--){
        for(int j=i-1;j>=0;j--){
            std::cout<<"Odejmujemy od wiersza "<<j+1<<". wiersz "<<i+1<<". pomnozony przez "<<(*this)[j][i]<<std::endl;
            (*this)[j]=(*this)[j]-(*this)[i]*((*this)[j][i]);
            std::cout<<(*this)<<std::endl;
        }
    }
}


#endif