/* Rafal Krokowski, Przetwarzanie Obrazow 1, 29.11.16r.

   Funkcja czytaj oraz wyswietl zostaly zaimplementowane z funkcji
   odczyt.c nalezacej do dr.inz.Muszynskiego.

   TESTY:
   Program byl sprawdzany dla fileow w formacie PGM znajdujacych sie
   na diablo w folderze imageki/, konkretnie dla imageow kubus.pgm i
   Lena.pgm. Po wybraniu metody przetwarzania imageu i wywolaniu pozycji
   "Zapisz i wyswietl" z menu, automatycznie wlacza sie program display,
   ktory wyswietla 2 OBRAZY - pierwotny i przetworzony - dla wygody
   porownania zmian. Dzieje sie tak dopoki nie zakonczymy dzialania
   programu w menu.

   Uwaga: Obraz kubus.pgm pozostanie wlasciwie niezmieniony w wyniku
   rozciagania histogramu z powodu swojej malej rozdzielczosci - nalezy
   wykorzystac tu inny image, np. Lena.pgm.

   Odpowiednie funkcje programu posiadaja potrzebne komentarze, jednak
   bardziej oczywiste fragmenty kodu bronia sie same (sa dosc oczywiste)
   i nie wymagaja wyjasnienia.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Library added for ABS function usage */
#include "module1.h"

// MAIN FUNCTION

int main() {
  Image image;
  int read = 0;
  FILE *file;
  char name[100];
  int a;

  printf("Welcome to image processing app!\n");
  /* Read selected file to the memory */
  printf("Your file name:\n");
  scanf("%s", name);
  file = fopen(name,"r");

  if (file != NULL)
    read = read(file, &image);
  if (read != 0)
    show(name);

  /*USER'S  MENU */

  printf("What should I do with this loaded image?\n");
      printf("1 - Negative\n");
      printf("2 - Thresholding\n");
      printf("3 - White half-thresholding\n");
      printf("4 - Contouring\n");
      printf("5 - Histogram equalization\n");
      printf("6 - Save and show changes\n");
      printf("7 - Exit the app\n");

  while(a != 7 ) {  /* When a is 7, exit the app */
    scanf("%d", &a);

    switch (a) {
      /* We run the function on image and inform user about it */
     case 1:
       negative(&image);
       printf("Negative done correctly!\n");
       break;
     case 2:
       threshold(&image);
       printf("Thresholding done correctly!\n");
       break;
     case 3:
       halfThreshold(&image);
       printf("White half-thresholding done correctly!\n");
       break;
     case 4:
       contour(&image);
       printf("Contouring done correctly!\n");
       break;
     case 5:
       histogram(&image);
       printf("Histogram equalization done correctly!\n");
       break;
     case 6:
       save(&image);
       char name[100]={"image.pgm"};
       show(name);
       printf("File changes saved successfully!\n");
       break;
     case 7:
       printf("App exited successfully!\n");
       break;
     default:
       printf("This value does not exist in the manu!\n");
       break;
     }
  }

  fclose(file);
  return 0;
}
