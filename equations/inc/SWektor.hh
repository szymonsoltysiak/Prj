#ifndef SWEKTOR_HH
#define SWEKTOR_HH


#include <iostream>



template <typename STyp, int SWymiar>
class SWektor {
    STyp  _Wsp[SWymiar+1];
  public:
    //SWektor() { for (STyp &Wsp: _Wsp) Wsp = 0; }
  
    STyp  operator [] (unsigned int Ind) const { return _Wsp[Ind]; }
    STyp &operator [] (unsigned int Ind)       { return _Wsp[Ind]; }

    SWektor<STyp,SWymiar> operator - (const SWektor<STyp,SWymiar> &Odjemnik) const;
    SWektor<STyp,SWymiar> operator * (STyp Mnoznik) const;
};




template <typename STyp, int SWymiar>
SWektor<STyp,SWymiar> SWektor<STyp,SWymiar>::operator - (const SWektor<STyp,SWymiar> &Odjemnik) const
{
  SWektor<STyp,SWymiar>  Wynik;

  for (unsigned int Ind = 0; Ind <= SWymiar; ++Ind) Wynik[Ind] = (*this)[Ind] - Odjemnik[Ind];
  return Wynik;
}


template <typename STyp, int SWymiar>
SWektor<STyp,SWymiar> SWektor<STyp,SWymiar>::operator * (STyp Mnoznik) const
{
  SWektor<STyp,SWymiar>  Wynik;

  for (unsigned int Ind = 0; Ind <= SWymiar; ++Ind) Wynik[Ind] = (*this)[Ind]*Mnoznik;
  return Wynik;  
}


template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &StrmWyj, const SWektor<STyp,SWymiar>& W)
{
  for (unsigned int Ind = 0; Ind <= SWymiar; ++Ind) {
    StrmWyj  << W[Ind]<< " ";
  }  
  return StrmWyj;
}

template <typename STyp, int SWymiar>
std::istream& operator >> (std::istream &StrmWej, SWektor<STyp,SWymiar>& W)
{
  for (unsigned int Ind = 0; Ind <= SWymiar; ++Ind) {
    StrmWej >> W[Ind];
  }  
  return StrmWej;
}

template <typename STyp, int SWymiar>
void swapW(SWektor<STyp,SWymiar>&W1,SWektor<STyp,SWymiar>&W2){
    STyp tmp;
    for(int i=0;i<=SWymiar;i++){
    tmp=W1[i];
    W1[i]=W2[i];
    W2[i]=tmp;
    }
}
#endif
