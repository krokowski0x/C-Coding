/* RAFAL KROKOWSKI, PRZETWARZANIE OBRAZOW 2, 10.01.2017r.

   ZMIANY:
   Program dziala teraz w oparciu o 2 struktury, ktore przechowuja informacje o imageie, jego
   wielkosci i kolorze (zmienna typu _Bool) oraz wybranych opcjach wywolania programu.Podzielony
   jest tez na moduly. Zamiast menu uzytkownika musimy teraz wywolac program z odpowiadnimi
   opcjami -i, -o itd. W razie wybrania pliku w formacie .ppm zostanie on przeksztalcony na plik
   .pgm do ktorego zostanie utworzona "szyta na miare" dynamiczna tablica. Program posiada takze
   asercje sprawdzajace poprawnosc opcji czy formatu pliku.Dalsze przeksztalcenia odbywaja sie
   tak samo jak wczesniej na pliku .pgm tylko w oparciu o struktury.

   TESTY:
   Program kompiluje sie poprawnie za pomoca specjalnie stworzonegativeo Makefile. Do testow
   wykorzystane byly pliki z katalogu /imageki, konkretnie Kubus i Lena w formatach .pgm
   i .ppm. Testom poddane byly flagi [-i name], [-o name], [-p liczba], [-b liczba],
   [-n], [-r], [-d], [-h]. Dwie pierwsze opcje nalezy wpisac z name pliku, w przeciwnym
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
  Image image;
  options choice;
  int read = 0;
  char name[100];
  FILE *input_file, *output_file;

    process_options(argc, argv, &choice);
    read(input_file, &image);
    if(choice.contour == 1)
      contour(&image);
    if(choice.negative == 1)
      negative(&image);
    if(choithreshold== 1)
      threshold&image);
    if(choice.threshold == 1)
      threshold(&image);
    if(choice.histogram == 1)
      histogram(&image);
    save(&choice, &image);
    if(choice.show == 1){
      show(name);
    }

  fclose(input_file);
  return 0;
}
