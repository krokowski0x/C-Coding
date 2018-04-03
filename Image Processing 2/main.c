/* RAFAL KROKOWSKI, PRZETWARZANIE OBRAZOW 2, 10.01.2017r.

   ZMIANY:
   Program dziala teraz w oparciu o 2 struktury, ktore przechowuja informacje o obrazie, jego
   wielkosci i kolorze (zmienna typu _Bool) oraz wybranych opcjach wywolania programu.Podzielony
   jest tez na moduly. Zamiast menu uzytkownika musimy teraz wywolac program z odpowiadnimi
   opcjami -i, -o itd. W razie wybrania pliku w formacie .ppm zostanie on przeksztalcony na plik
   .pgm do ktorego zostanie utworzona "szyta na miare" dynamiczna tablica. Program posiada takze
   asercje sprawdzajace poprawnosc opcji czy formatu pliku.Dalsze przeksztalcenia odbywaja sie
   tak samo jak wczesniej na pliku .pgm tylko w oparciu o struktury.

   TESTY:
   Program kompiluje sie poprawnie za pomoca specjalnie stworzonego Makefile. Do testow
   wykorzystane byly pliki z katalogu /obrazki, konkretnie Kubus i Lena w formatach .pgm
   i .ppm. Testom poddane byly flagi [-i nazwa], [-o nazwa], [-p liczba], [-b liczba],
   [-n], [-r], [-d], [-h]. Dwie pierwsze opcje nalezy wpisac z nazwa pliku, w przeciwnym
   razie wystapi blad uchwytu pliku, o czym poinformuje nas odpowiednia asercja. Jednak
   odpowiednie dodanie opcji pozwala programowi dzialac poprawnie.

   CZESC PROGRAMU ODPOWIEDZIALNA ZA OBSLUGE OPCJI JEST WLASNOSCIA DR. MUSZYNSKIEGO
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#include "module1.h"

int main(int argc, char **argv) {
  TObraz obraz;
  w_opcje wybor;
  int odczytano = 0;
  char nazwa[100];
  FILE *plik_we, *plik_wy;

    przetwarzaj_opcje(argc, argv, &wybor);
    czytaj(plik_we, &obraz);
    if(wybor.kont == 1)
      kont(&obraz);
    if(wybor.neg == 1)
      neg(&obraz);
    if(wybor.progow == 1)
      progow(&obraz);
    if(wybor.polprogowB == 1)
      polprogowB(&obraz);
    if(wybor.hist == 1)
      hist(&obraz);
    zapisz(&wybor, &obraz);
    if(wybor.wyswietl == 1){
      wyswietl(nazwa);
    }

  fclose(plik_we);
  return 0;
}
