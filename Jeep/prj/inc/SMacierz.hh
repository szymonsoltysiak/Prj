#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <SWektor.hh>
#include <iostream>

template <typename STyp, int SWymiar>
class SMacierz
{

  SWektor<STyp, SWymiar> Wiersz[SWymiar];

public:
  SWektor<STyp, SWymiar> operator[](unsigned int Ind) const { return Wiersz[Ind]; }
  SWektor<STyp, SWymiar> &operator[](unsigned int Ind) { return Wiersz[Ind]; }
  SWektor<STyp, SWymiar> operator*(SWektor<STyp, SWymiar> Mnoznik);

  void OdejmowanieWiersza(int i, int j);

  void Zamiana();
};

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SMacierz<STyp, SWymiar>::operator*(SWektor<STyp, SWymiar> Mnoznik)
{
  STyp Suma = 0;
  SWektor<STyp, SWymiar> Wynik;
  for (int i = 0; i < SWymiar; ++i)
  {
    for (int j = 0; j < SWymiar; ++j)
    {
      Suma += (*this)[j][i] * Mnoznik[j];
    }
    Wynik[i] = Suma;
    Suma = 0;
  }
  return Wynik;
}

template <typename STyp, int SWymiar>
std::istream &operator>>(std::istream &StrmWej, SMacierz<STyp, SWymiar> &M)
{
  for (unsigned int Ind = 0; Ind < SWymiar; ++Ind)
  {
    StrmWej >> M[Ind];
  }
  return StrmWej;
}

template <typename STyp, int SWymiar>
std::ostream &operator<<(std::ostream &StrmWyj, const SMacierz<STyp, SWymiar> &M)
{
  for (unsigned int Ind = 0; Ind < SWymiar; ++Ind)
  {
    StrmWyj << M[Ind] << " " << std::endl;
  }
  return StrmWyj;
}

template <typename STyp, int SWymiar>
void SMacierz<STyp, SWymiar>::OdejmowanieWiersza(int i, int j)
{
  (*this)[j] = (*this)[j] - (*this)[i] * ((*this)[j][i]);
}

typedef SMacierz<double, 3> MacRot;

#endif
