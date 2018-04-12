/* Rafal Krokowski, Image Processing 1, 29.11.16r.

   Read() and show() functions has been implemented from
   function 'odczyt.c' which is dr.inz.Muszynski intellectual property.

   TESTS:
   App was tested for files in the PGM format. After chosing image
   processing function from main menu and running 'Save and show changes',
   display program automatically fires and displays 2 IMAGES - original
   ond processed one - for simplicity of compraing changes. Changes are
   added incrementally until we end the program.

   Warning: Histogram equalization seems to has no effect if we use
            low resolution image. I strongly recommend using higher
            quality images.
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
