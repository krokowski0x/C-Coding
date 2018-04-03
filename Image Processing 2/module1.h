#ifndef MODUL_H
#define MODUL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define W_OK 0
#define B_NIEPOPRAWNAOPCJA -1
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4

typedef struct {
  FILE *plik_we, *plik_wy;
  int neg,progow,kont,wyswietl,polprogowB,hist;
  int w_progu;
} w_opcje;

typedef struct {
  int wymx, wymy, szarosci;
  int obraz_pgm[MAX][MAX];
  int *obrazek;   //Potrzebne do dynamicznie tworzonej tablicy
  int R[MAX][MAX]; //Kolory
  int G[MAX][MAX];
  int B[MAX][MAX];
  _Bool kolor; //Jesli obraz bedzie kolorowy, kolor==1
} TObraz;

int czytaj(FILE *plik_we, TObraz *obraz);
void wyswietl(char *n_pliku);
void zapisz(w_opcje *plik, TObraz *obraz);
void neg(TObraz *obraz);
void progow(TObraz *obraz);
void polprogowB(TObraz *obraz);
void kont(TObraz *obraz);
void hist(TObraz *obraz);
void wyzeruj_opcje(w_opcje *wybor);
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);

#endif
