#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Library added for ABS function usage */
#define MAX 512             /* Maximum size of loaded image */
#define LINE_LENGTH 1024    /* Helper buffers length */
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
  int *tmp_image;   // It's useful for dynamic creation of an array
  int R[MAX][MAX];  // RGB Colors
  int G[MAX][MAX];
  int B[MAX][MAX];
  _Bool color;      // If image has color, color == 1, if it's B&W, color == 0
} Image;

int  read(FILE *input_file, Image *image);
void show(char *file_name);
void save(options *file, Image *image);
void negative(Image *image);
void threshold(Image *image);
void halfThreshold(Image *image);
void contour(Image *image);
void histogram(Image *image);
void reset_options(options *choice);
int  process_options(int argc, char **argv, options *choice);

#endif
