#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Library added for ABS function usage */
#include "module1.h"

// File reading function
int read(FILE *input_file, Image *image) {
  char buff[LINE_LENGTH];   /* Helper buffer for reading comments and additional info */
  int character;            /* Helper variable for reading comments */
  int end = 0;              /* Is it EOF yet? */
  int i, j;

  // Check if there's a correct file handle
  if (input_file == NULL) {
    fprintf(stderr, "Error: No file handle\n");
    return(0);
  }

  // Checking for "magic number" - should be P2 */
  if (fgets(buff, LINE_LENGTH, input_file) == NULL)   /* Read first line to the buffer */
    end = 1;                                          /* Didn't succeed? EOF! */

  if ( (buff[0] != 'P') || (buff[1]!='2') || end ) {  /* Is there a magic "P2"? */
    fprintf(stderr, "Error: File type is not PGM\n");
    return(0);
  }

  // Skip these comments
  do {
    if ((character = fgetc(input_file)) == '#') {         /* Is the line starting at '#'? */
      if (fgets(buff,LINE_LENGTH,input_file) == NULL)     /* Read it to buffer */
	      end = 1;                                          /* If EOF, remember it */
    }  else {
      ungetc(character, input_file);    /* If the first character in line */
    }                                   /* is not '#', return it */
  } while (character == '#' && !end);   /* Keep doin' it until there are comments */
                                        /* or the EOF */

  // Getting image size and shades of grey
  if (fscanf(input_file, "%d %d %d", image->x, image->y, image->greys) != 3) {
    fprintf(stderr, "Error: Image size or greys not found\n");
    return(0);
  }

  // Getting image and saving it in pgm_image array
  for (i = 0; i < image->y; i++) {
    for (j = 0; j < image->x; j++) {
      if (fscanf(input_file, "%d", &(image->pgm_image[i][j])) !=1 ) {
	       fprintf(stderr, "Error: Wrong image size\n");
	       return(0);
      }
    }
  }
  return image->x * image->y;   /* Successful read so */
}                               /* Return amount of all pixels */

// Display image with "display" program
void show(char *file_name) {
  char command[LINE_LENGTH];      /* Helper buffer for concatenating command */

  strcpy(command, "display ");    /* Command has a following syntax: */
  strcat(command, file_name);     /* display "file_name" & */
  strcat(command, " &");
  printf("%s\n", command);        /* Print command for checking */
  system(command);                /* Run command */
}

// Saving edited image function

int save(Image *image) {
  FILE *file;
  int i,j;
  file = fopen("image.pgm","w");
  /* First, we print image info */
  fprintf(file, "P2\n %d %d\n %d\n", image->x, image->y, image->greys);
  for (j = 0; j < image->y; j++) {
    for(i = 0; i < image->x; i++) {
      /* Then we save it to file pixel by pixel */
      fprintf(file, "%d\n", image->pgm_image[i][j]);
	  }
  }
  return 0;
}

// Negative function

int negative(Image *image)
{
  int i,j;
  for (j = 0; j < image->y; j++){
    for (i = 0; i < image->x; i++){
      /* For mamximum value (greys) we subtract current pixel value */
      image->pgm_image[i][j] = (image->greys - image->pgm_image[i][j]);
    }
  }
  return 0;
}

// Threshold function

int threshold(Image *image)
{
  int a,i,j;
  float threshold; /* Float type, becouse threshold will finally be a fraction */
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold = (a / 100 * (image->greys));
  for(j = 0; j < image->y; j++) {
    for(i = 0; i < image->x; i++){
      if(image->pgm_image[i][j] <= threshold)
	      image->pgm_image[i][j] = 0;
      else
	      image->pgm_image[i][j] = image->greys;
    }
  }
  return 0;
}

// White halfthresholding function

int halfThreshold(Image *image)
{
  /* Same as the one before */
  int a,i,j;
  float threshold;
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold = (a / 100 * (image->greys));
  for(j = 0; j < image->y; j++) {
    for(i = 0; i < image->x; i++) {
      if(image->pgm_image[i][j]<=threshold)
	      image->pgm_image[i][j] = image->pgm_image[i][j];
      else
	      image->pgm_image[i][j] = image->greys;
    }
  }
  return 0;
}

// Contouring function

int contour(Image *image)
{
  int i,j;
  /* First and last pixels does not have others 'by their side'
     thus we cut one pixel at every side */
  for(i = 0; i < (image->x - 1); i++){
    for(j = 0; j < (image->y - 1); j++){
      /* Contouring equation */
      image->pgm_image[i][j] = abs(image->pgm_image[i+1][j] - image->pgm_image[i][j]) +
                               abs(image->pgm_image[i][j+1] - image->pgm_image[i][j]);
    }
  }
  /* Tried and true code - something was broken
     but worked after cutting one more pixel */
  image->x = image->x--;
  image->y = image->y--;
  return 0;
}

// Histogram equalization function

int histogram(Image *image)
{
  int i,j,lmax,lmin;
  /* In this loop, program seeks for min and max values */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->pgm_image[i][j] > lmax)
	      lmax = image->pgm_image[i][j];
      if(image->pgm_image[i][j] < lmin)
	      lmin = image->pgm_image[i][j];
    }
  }
  /* In this loop we do actual equalization */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      image->pgm_image[i][j] = (image->pgm_image[i][j] - lmin) / (lmax-lmin) * (image->greys);
    }
  }
  return 0;
}
