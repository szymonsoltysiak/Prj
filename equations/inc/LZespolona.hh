#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH
#include <iostream>
using namespace std;

class LZespolona
{
    // atrybuty
private:
    

public:
    double re;
    double im;

    double getRe()
    {
        return re;
    }
    
    double getIm()
    {
        return im;
    }

    void setLZesp(double re, double im)
    {
        LZespolona::re = re;
        LZespolona::im = im;
    }
    

    LZespolona operator+(LZespolona Skl1);
    LZespolona operator-(LZespolona Skl1);
    LZespolona operator*(LZespolona Skl1);
    LZespolona operator*(double Skl1);
    LZespolona operator/(LZespolona Skl2);
    LZespolona operator/(double dzielnik);
    LZespolona operator=(double Skl1);
    bool operator==(LZespolona Arg2);
    bool operator!=(int Arg2);
    LZespolona Sprzezenie();
    double modul();
};

std::ostream &operator<<(std::ostream &out, LZespolona lz);
std::istream &operator>>(std::istream &in, LZespolona &lz);
LZespolona operator/(int Skl1, LZespolona Skl2);



#endif