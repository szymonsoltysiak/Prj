#include<stdio.h>
#include"struktura.h"
#include"linia_komend.h"
#include"obsluga.h"
#include"filtry.h"

int main(int argc, char ** argv)
{
    t_opcje opcje;
    t_obraz obraz;
    int kod_bledu, odczytano = 0;
    FILE *plik;
    char wybor[2]=" ", wybor2[2]=" ",nazwa[100];

    if(argc>1){
        kod_bledu=przetwarzaj_opcje(argc,argv,&opcje);

        if (kod_bledu)
            printf("Blad nr %d\n", kod_bledu);
         
        

        else{
            if(argc==2 && (&opcje)->pomoc) pomoc();
            else{
            czytaj((&opcje)->plik_we,&obraz);
            if((&opcje)->pomoc) pomoc();
            if(    ((&opcje)->negatyw || (&opcje)->progowanie || (&opcje)->konturowanie || (&opcje)->rozmycie
            || (&opcje)->zmiana_poziomu || (&opcje)->maski) && (&obraz)->kolor==3) konwersja(&obraz);
            if((&opcje)->negatyw) negatyw(&obraz);
            if((&opcje)->progowanie) progowanie(&obraz, (&opcje)->w_progu);
            if((&opcje)->konturowanie) konturowanie(&obraz);
            if((&opcje)->rozmycie) rozmycie(&obraz);
            if((&opcje)->zmiana_poziomu) zmiana_poziomow(&obraz, (&opcje)->zm_poz_czern, (&opcje)->zm_poz_biel);
            if((&opcje)->wyswietlenie) {
                if((&obraz)->kolor==1){
                plik = fopen("tmp.pgm", "w");
                zapisz(plik,&obraz);
                wyswietl("tmp.pgm");}
                if((&obraz)->kolor==3){
                plik = fopen("tmp.ppm", "w");
                zapisz(plik,&obraz);
                wyswietl("tmp.ppm");}}
            zapisz((&opcje)->plik_wy,&obraz);}
        }
    }

    else{
    while(wybor[0] != '0')
    {
        pokaz_menu();

        scanf("%1s", wybor);

        switch(wybor[0])
        {
            case '1':
                printf("Podaj nazwe pliku:\n");
                scanf("%s",nazwa);
                plik=fopen(nazwa,"r");
                if (plik != NULL) {       
                odczytano = czytaj(plik,&obraz);
                fclose(plik);
                }

                if (odczytano != 0)
                    printf("Wczytano plik\n");
                else printf("Nie udalo sie wczytac pliku\n");
                break;

            case '2':
                printf("Podaj nazwe pliku:\n");
                scanf("%s",nazwa);
                plik=fopen(nazwa,"w");
                zapisz(plik,&obraz);
                break;

            case '3':
                if((&obraz)->kolor==1){
                plik = fopen("tmp.pgm", "w");
                zapisz(plik,&obraz);
                wyswietl("tmp.pgm");}
                if((&obraz)->kolor==3){
                plik = fopen("tmp.ppm", "w");
                zapisz(plik,&obraz);
                wyswietl("tmp.ppm");}
                break;

            case '4':
                if((&obraz)->kolor==3) konwersja(&obraz);
                negatyw(&obraz);
                break;

            case '5':
                if((&obraz)->kolor==3) konwersja(&obraz);
                printf("Podaj wartosc progu w procentach:\n");
                scanf("%d", &((&opcje)->w_progu));
                progowanie(&obraz, (&opcje)->w_progu);
                break;

            case '6':
                if((&obraz)->kolor==3) konwersja(&obraz);
                konturowanie(&obraz);
                break;

            case '7':
                if((&obraz)->kolor==3) konwersja(&obraz);
                rozmycie(&obraz);
                break;

            case '8':
                if((&obraz)->kolor==3) konwersja(&obraz);
                printf("Podaj nowy poziom czerni w procentach:\n");
                scanf("%d", &((&opcje)->zm_poz_czern));
                printf("Podaj nowy poziom bieli w procentach:\n");
                scanf("%d", &((&opcje)->zm_poz_biel));
                zmiana_poziomow(&obraz, (&opcje)->zm_poz_czern, (&opcje)->zm_poz_biel);
                break;

	        case '0': break;
            case 'h': pomoc(); break;
            default: printf("\t\tnierozpoznano\n");

    }printf("\n");
    }}

    remove("tmp.pgm");
    remove("tmp.ppm");

    return kod_bledu;
}