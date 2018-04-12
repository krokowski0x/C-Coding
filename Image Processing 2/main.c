/* RAFAL KROKOWSKI, IMAGE PROCESSING 2, 10.01.2017r.

   CHANGES:
   Program now runs based on 2 structures, which stores info about the image, its size
   and color (or lack of it) and chosen options (used flags). It's also modular now.
   Instead of simple menu, it has to be now run with options -i, -o etc. If you want
   to use .ppm format, program converts it to .pgm, from which custom made, dynamic
   array will be created. Program has plenty of assertions, checking file format or
   options. The rest is the same as in Image Processing 1 but based on structs.

   TESTS:
   Program compiles correctly with custom made Makefile (not included in this repo).
   For tests, .ppm and .pgm images has been used with all the following flags: [-i name],
   [-o name], [-p number], [-b number], [-n], [-r], [-d], [-h]. You have to provide
   file name for the -i and -o flags or there will be a file handle error (there is an
   assertion for that as well).

   Flag parsing utility is dr.inz.Muszynski intellectual property.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Library added for ABS function usage */
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
      threshold()&image);
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
