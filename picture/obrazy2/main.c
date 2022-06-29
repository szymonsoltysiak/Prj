#include<stdio.h>
#include"struktura.h"
#include"obsluga.h"

int main(){
    char nazwa[100];
    t_obraz obraz;
    FILE *plik;

    printf("Podaj nazwe pliku:\n");
    scanf("%s",nazwa);
    plik=fopen(nazwa,"r");
    
    czytaj(plik,&obraz);
    konwersja(&obraz);

    char nazwa_pliku[100];
    printf("Podaj nazwe pliku (zakazane: tmp.pgm): ");
    scanf("%s",nazwa_pliku);
    FILE *plik_wy;
    plik_wy = fopen(nazwa_pliku, "w");
    zapisz(plik_wy,&obraz);
    wyswietl("tmp.pgm");

    return 0;
}