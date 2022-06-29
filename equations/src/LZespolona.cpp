#include <iostream>
#include <cmath>
#include <cctype>
#include<stdio.h>
#include "LZespolona.hh"
using namespace std;

LZespolona LZespolona::operator+(LZespolona Skl2)
{
	LZespolona Wynik;

	Wynik.re = LZespolona::re + Skl2.re;
	Wynik.im = LZespolona::im + Skl2.im;
	return Wynik;
}

LZespolona LZespolona::operator-(LZespolona Skl2)
{
	LZespolona Wynik;

	Wynik.re = LZespolona::re - Skl2.re;
	Wynik.im = LZespolona::im - Skl2.im;
	return Wynik;
}

LZespolona LZespolona::operator*(LZespolona Skl2)
{
	LZespolona Wynik;

	Wynik.re = (LZespolona::re * Skl2.re) - (LZespolona::im * Skl2.im);
	Wynik.im = (LZespolona::re * Skl2.im) + (LZespolona::im * Skl2.re);
	return Wynik;
}

LZespolona LZespolona::operator*(double Skl2)
{
	LZespolona Wynik;

	Wynik.re = LZespolona::re * Skl2;
	Wynik.im = LZespolona::im * Skl2;
	return Wynik;
}

LZespolona LZespolona::Sprzezenie()
{
	LZespolona Wynik;
	Wynik.re = re;
	Wynik.im = (-1) * im;

	return Wynik;
}

double LZespolona::modul()
{
	double Obliczenie;
	Obliczenie = ((LZespolona::re) * (LZespolona::re)) + ((LZespolona::im) * (LZespolona::im));
	return Obliczenie;
}

LZespolona LZespolona::operator/(double dzielnik)
{

	LZespolona Wynik;

	if (dzielnik != 0)
	{
		Wynik.re = LZespolona::re / dzielnik;
		Wynik.im = LZespolona::im / dzielnik;
	}
	else
	{
		cout << "Dzielenie przez zero!" << endl;
	}

	return Wynik;
}

LZespolona LZespolona::operator/(LZespolona Skl2)
{
	LZespolona Wynik;
	double modull = Skl2.modul();

	if (modull == 0)
	{
		throw std::domain_error("Dzielenie przez zero");
	}
	else
	{
		Wynik = (*this) * Skl2.Sprzezenie();
	}
	return Wynik / modull;
}

std::ostream &operator<<(std::ostream &out, LZespolona lz)
{	
	double re=lz.getRe();
	double im=lz.getIm();
	out << "(" << re << std::showpos << im << std::noshowpos << "i)";

	return out;
}

std::istream &operator>>(std::istream &in, LZespolona &lz)
{
	char znak, NawiasP, Litera;
	double re, im;
	in >> znak;
	if (in.fail())
		return in;

	if (znak != '(')
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	in >> re;
	if (in.fail())
	{
		return in;
	}

	in >> im;
	if (in.fail())
	{
		return in;
	}

	in >> Litera;
	if (in.fail())
		return in;

	if (Litera != 'i')
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	in >> NawiasP;
	if (in.fail())
		return in;
	if (NawiasP != ')')
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	lz.setLZesp(re, im);
	return in;
}
bool LZespolona::operator==(LZespolona Arg2)
{
	//return (this->re == Arg2.re && this->im == Arg2.im);
        return (abs(this->re-Arg2.re)<0.0000001 && abs(this->im-Arg2.im)<0.0000001);
}

bool LZespolona::operator!=(int Arg2)
{
	//return (this->re == Arg2 && this->im == Arg2);
        return !(abs(this->re-Arg2)<0.0000001 && abs(this->im-Arg2)<0.0000001);
}

LZespolona operator/(int Skl1, LZespolona Skl2){
    LZespolona Wynik, tmp;
    tmp.re=Skl1;
    tmp.im=0;
    Wynik=tmp/Skl2;
    return Wynik;
}

LZespolona LZespolona::operator =(double Skl1)
{
	LZespolona Wynik;
	Wynik.re=Skl1;
	Wynik.im=0;
	return Wynik;
}