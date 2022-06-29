#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"struktura.h"


int czytaj (FILE *plik_we, t_obraz *obraz){
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  if(obraz->piksele!=NULL)
  free(obraz->piksele);

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */


  if ( (buf[0]!='P')|| (buf[1]!='2' && buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2"? */   
    fprintf(stderr,"Blad: To nie jest plik PGM ani PPM\n");
    return(0);
  }

  if(buf[1]=='2') obraz->kolor=1; /*zapisujemy czy obraz jest czarno-bialy*/
  else obraz->kolor=3; /*czy kolorowy*/

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&(obraz->wym_x),&(obraz->wym_y),&(obraz->odcieni))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
    obraz->piksele = malloc(obraz->wym_x*obraz->wym_y*obraz->kolor*sizeof(int));
    int (*piksele)[obraz->wym_x*obraz->kolor];
    piksele=(int(*)[obraz->wym_x*obraz->kolor]) obraz->piksele;

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obraz->wym_y; i++) {
    for (j=0;j<obraz->wym_x*obraz->kolor;j++) {
      fscanf(plik_we, "%d", &(piksele[i][j]));}}
  
  return (obraz->wym_x)*(obraz->kolor)*(obraz->wym_y);   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int zapisz(FILE *plik_wy,t_obraz *obraz)
{
    int i,j;

    int (*piksele)[obraz->wym_x*obraz->kolor]; 
    piksele=(int(*)[obraz->wym_x*obraz->kolor]) obraz->piksele; 

    if (plik_wy==NULL) {
    fprintf(stderr,"Blad\n");
    return(0);}

    if(obraz->kolor==1)fprintf(plik_wy,"P2\n");
    else fprintf(plik_wy,"P3\n");
    fprintf(plik_wy,"%d %d %d\n",obraz->wym_x, obraz->wym_y, obraz->odcieni);

    
    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x*obraz->kolor;j++){
          fprintf(plik_wy,"%d ",piksele[i][j]);}
          fprintf(plik_wy,"\n");
          }

    fclose(plik_wy);
    return (obraz->wym_x)*(obraz->wym_y)*(obraz->kolor);
}


void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void pokaz_menu()
{
    printf("Opcje:\n");
    printf("1. Wczytaj plik\n");
    printf("2. Zapisz plik\n");
    printf("3. Wyswietl plik\n");
    printf("4. Negatyw\n");
    printf("5. Progowanie\n");
    printf("6. Konturowanie\n");
    printf("7. Rozmycie poziome\n");
    printf("8. Maski\n");
    printf("9. Zmiana poziomu\n");
    printf("0. Zakoncz\n");
    printf("h. Pomoc\n");
    printf("Twoj wybor: ");
}

void konwersja(t_obraz *obraz){
  int i,j;
  void *tmp;
  int (*piksele)[obraz->wym_x*obraz->kolor];
  piksele=(int(*)[obraz->wym_x*obraz->kolor]) obraz->piksele;

  tmp = malloc(obraz->wym_x*obraz->wym_y*sizeof(int));
  int (*t)[obraz->wym_x]; 
  t=(int(*)[obraz->wym_x]) tmp; 

  for (i=0;i<obraz->wym_y; i++) {
    for (j=0;j<obraz->wym_x*obraz->kolor;j+=3) {
      t[i][j/3]=(piksele[i][j]+piksele[i][j+1]+piksele[i][j+2])/3;}}

  free(obraz->piksele);
  obraz->piksele=tmp;
  obraz->kolor=1;
}

void pomoc(){
printf("POMOC:\n");
  printf("Wywyolywanie programu z lini komend:\n");
  printf("Obowiozkowo: -i nazwa pliku\n");
  printf("Opcjonalnie: -o nazwa pliku, -n, -k, -r, -d, -h\n");
  printf("-p liczba, -m liczba, -z liczba liczba\n\n");
  printf("Opis funkci:\n");
  printf("Obsluga:\n");
  printf("-i nazwa pliku: Wcztywanie pliku o podanej nazwie\n");
  printf("Obslugiwane typy plikow: .pgm .ppm\n");
  printf("-o nazwa pliku: Zapisywanie pliku o podanej nazwie\n");
  printf("Obslugiwane typy plikow: .pgm .ppm\n");
  printf("-d: Wyswietlanie pliku .pgm lub .ppm\n");
  printf("-h: Pomoc\n");

  printf("------------------------------------------------------------------------------------------------");

  printf("\nPrzetwarzanie obrazow:\n");
  printf("Te funkcje dzialaja dla plikow .pgm. Pliki .ppm sa najpierw konwetowane do .pgm i pozniej przetwarzane\n");
  printf("-n: Negatyw\n");
  printf("-k: Konturowanie\n");
  printf("-r: Rozmycie poziome\n");
  printf("-p liczba: Progowanie, gdzie liczba to wartosc progu w procentach\n");
printf("-z liczba liczba: Zmiana poziomow,\n");
printf("gdzie pierwsza liczba to nowy poziom czerni, a druga bieli\n");
}