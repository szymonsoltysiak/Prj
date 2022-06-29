#ifndef OBSLUGA_H
#define OBSLUGA_H
#include"struktura.h"

int czytaj (FILE*,t_obraz*);
int zapisz(FILE *,t_obraz*); 
void wyswietl(char*);
void pokaz_menu();
void konwersja(t_obraz*);
void pomoc();

#endif