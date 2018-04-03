/* Rafal Krokowski, Przetwarzanie Obrazow 1, 29.11.16r.

   Funkcja czytaj oraz wyswietl zostaly zaimplementowane z funkcji
   odczyt.c nalezacej do dr.inz.Muszynskiego.

   TESTY:
   Program byl sprawdzany dla plikow w formacie PGM znajdujacych sie
   na diablo w folderze obrazki/, konkretnie dla obrazow kubus.pgm i
   Lena.pgm. Po wybraniu metody przetwarzania obrazu i wywolaniu pozycji
   "Zapisz i wyswietl" z menu, automatycznie wlacza sie program display,
   ktory wyswietla 2 OBRAZY - pierwotny i przetworzony - dla wygody
   porownania zmian. Dzieje sie tak dopoki nie zakonczymy dzialania
   programu w menu.

   Uwaga: Obraz kubus.pgm pozostanie wlasciwie niezmieniony w wyniku
   rozciagania histogramu z powodu swojej malej rozdzielczosci - nalezy
   wykorzystac tu inny obraz, np. Lena.pgm.

   Odpowiednie funkcje programu posiadaja potrzebne komentarze, jednak
   bardziej oczywiste fragmenty kodu bronia sie same (sa dosc oczywiste)
   i nie wymagaja wyjasnienia.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#include "module1.h"

// Funkcja MAIN

int main() {
  TObraz obraz;
  int odczytano = 0;
  FILE *plik;
  char nazwa[100];
  int a;

  printf("Witaj w programie do przetwarzania obrazow!\n");
  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s", nazwa);
  plik = fopen(nazwa,"r");

  if (plik != NULL)    /* co spowoduje zakomentowanie tego warunku */
    odczytano = czytaj(plik, &obraz);
  if (odczytano != 0)
    wyswietl(nazwa);

  /* MENU UZYTKOWNIKA */

  printf("Co mam zrobic z wczytanym obrazem?\n");
      printf("1 - Negatyw\n");
      printf("2 - Progowanie\n");
      printf("3 - Polprogowanie bieli\n");
      printf("4 - Konturowanie\n");
      printf("5 - Rozciaganie histogramu\n");
      printf("6 - Zapisz i wyswietl zmiany\n");
      printf("7 - Zakonczenie dzialania programu\n");

  while(a !=7 ) {  /* Warunek konca petli, konczy tez dzialanie programu */
    scanf("%d", &a);

    switch (a) {
      /* Wywolujemy funkcje i informujemy o tym uzytkownika */
     case 1:
       neg(&obraz);
       printf("Negatyw wykonany poprawnie!\n");
       break;
     case 2:
       progow(&obraz);
       printf("Progowanie wykonane poprawnie!\n");
       break;
     case 3:
       polprogowB(&obraz);
       printf("Polprogowanie bieli wykonane poprawnie!\n");
       break;
     case 4:
       kont(&obraz);
       printf("Konturowanie wykonane poprawnie!\n");
       break;
     case 5:
       hist(&obraz);
       printf("Rozciaganie histogramu wykonane poprawnie!\n");
       break;
     case 6:
       zapisz(&obraz);
       char nazwa[100]={"obraz.pgm"};
       wyswietl(nazwa);
       printf("Zapisano zmiany w pliku!\n");
       break;
     case 7:
       printf("Zakonczenie dzialania programu!\n");
       break;
     default:
       printf("Podanej wartosci nie ma w menu!\n");
       break;
     }
  }

  fclose(plik);
  return 0;
}
