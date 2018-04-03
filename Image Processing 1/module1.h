#ifndef MODUL_H
#define MODUL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

typedef struct {
  int wymx, wymy, szarosci;
  int obraz_pgm[MAX][MAX];
} TObraz;

int czytaj(FILE *plik_we, TObraz *obraz);
void wyswietl(char *n_pliku);
void zapisz(w_opcje *plik, TObraz *obraz);
void neg(TObraz *obraz);
void progow(TObraz *obraz);
void polprogowB(TObraz *obraz);
void kont(TObraz *obraz);
void hist(TObraz *obraz);

#endif
