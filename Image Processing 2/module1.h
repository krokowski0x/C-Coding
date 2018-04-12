#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#define MAX 512            /* Maksymalny rozmiar wczytywanego imageu */
#define LINE_LENGTH 1024      /* Dlugosc buforow pomocniczych */
#define OK 0
#define WRONG_OPTION -1
#define NO_NAME -2
#define NO_VALUE -3
#define NO_FILE -4

typedef struct {
  FILE *input_file, *output_file;
  int negative, threshold, contour, show, halfThreshold, histogram, threshold_value;
} options;

typedef struct {
  int x, y, greys;
  int pgm_image[MAX][MAX];
  int *tmp_image;   //Potrzebne do dynamicznie tworzonej tablicy
  int R[MAX][MAX]; //Kolory
  int G[MAX][MAX];
  int B[MAX][MAX];
  _Bool color; //Jesli image bedzie colorowy, color==1
} Image;

int  read(FILE *input_file, Image *image);
void show(char *n_pliku);
void save(options *plik, Image *image);
void negative(Image *image);
void threshold(Image *image);
void halfThreshold(Image *image);
void contour(Image *image);
void histogram(Image *image);
void reset_options(options *choice);
int  process_options(int argc, char **argv, options *choice);

#endif
