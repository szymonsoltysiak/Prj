#ifndef STRUKTURA_H
#define STRUKTURA_H

#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

/*struktura danych obrazu*/
typedef struct {
int wym_x, wym_y, odcieni, kolor;
void *piksele;
} t_obraz;

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,rozmycie,zmiana_poziomu,maski,wyswietlenie,pomoc;      /* opcje */
  int w_progu,nr_maski, zm_poz_czern,zm_poz_biel;              /* wartosc dla opcji*/ 
} t_opcje;

#endif