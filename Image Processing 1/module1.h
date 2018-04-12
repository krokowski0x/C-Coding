#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Library added for ABS function usage */

#define MAX 512             /* Maximum size of loaded image */
#define LINE_LENGTH 1024    /* Helper buffers length */

typedef struct {
  int x, y, greys;
  int pgm_image[MAX][MAX];
} Image;

int  read(FILE *input_file, Image *image);
void show(char *file_name);
void save(options *file, Image *image);
void negative(Image *image);
void threshold(Image *image);
void halfThreshold(Image *image);
void contour(Image *image);
void histogram(Image *image);

#endif
