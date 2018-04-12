#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#include "module1.h"

// Funkcja odczytu fileu
int read(FILE *input_file, Image *image) {
  char buff[LINE_LENGTH];      /* buffor pomocniczy do czytania naglowka i komentarzy */
  int character;                /* zmienna pomocnicza do czytania komentarzy */
  int end = 0;          /* czy napotkano end danych w fileu */
  int i, j;

  /*Sprawdzenie czy podano prawid�owy uchwyt fileu */
  if (input_file == NULL) {
    fprintf(stderr, "Error: No file handle\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buff, LINE_LENGTH,input_file) == NULL)   /* Wczytanie pierwszej linii fileu do buffora */
    end = 1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buff[0] != 'P') || (buff[1]!='2') || end ) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Error: File type is not PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((character = fgetc(input_file)) == '#') {         /* Czy linia rozpoczyna sie od characteru '#'? */
      if (fgets(buff,LINE_LENGTH,input_file) == NULL)  /* Przeczytaj ja do buffora                */
	      end = 1;                   /* Zapamietaj ewentualny end danych */
    }  else {
      ungetc(character, input_file);                   /* Gdy przeczytany character z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (character == '#' && !end);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil end danych         */

  /* Pobranie wymiarow imageu i liczby odcieni greys */
  if (fscanf(input_file, "%d %d %d", image->x, image->y, image->greys) != 3) {
    fprintf(stderr, "Error: Image size or greys not found\n");
    return(0);
  }
  /* Pobranie imageu i zapisanie w tablicy pgm_image*/
  for (i = 0; i < image->y; i++) {
    for (j = 0; j < image->x; j++) {
      if (fscanf(input_file, "%d", &(image->pgm_image[i][j])) !=1 ) {
	       fprintf(stderr, "Error: Wrong image size\n");
	       return(0);
      }
    }
  }
  return image->x * image->y;   /* Czytanie zakonczone sukcesem    */
}                                    /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie imageu o zadanej nazwie za pomoca thresholdramu "display"   */
void show(char *file_name) {
  char command[LINE_LENGTH];      /* buffor pomocniczy do zestawienia polecenia */

  strcpy(command, "display ");  /* konstrukcja polecenia postaci */
  strcat(command, file_name);     /* display "nazwa_fileu" &       */
  strcat(command, " &");
  printf("%s\n", command);      /* wydruk kontrolny polecenia */
  system(command);             /* wykonanie polecenia        */
}

// Funkcja zapisujaca edytowany image

int save(Image *image)
{
  FILE *file;
  int i,j;
  file = fopen("image.pgm","w");
  /* Wy�wietlamy najpierw informacje o imageie */
  fprintf(file, "P2\n %d %d\n %d\n", image->x, image->y, image->greys);
  for (j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      /* Zapisujemy do fileu kolejne piksele z tablicy */
      fprintf(file, "%d\n", image->pgm_image[i][j]);
	}
 }
  return 0;
}

// Funkcja negatywu

int negative(Image *image)
{
  int i,j;
  for (j = 0; j < image->y; j++){
    for (i = 0; i < image->x; i++){
      /* Od maksymalnej wartosci (greys) odejmujemy wartosc danego piksela */
      image->pgm_image[i][j] = (image->greys - image->pgm_image[i][j]);
    }
  }
  return 0;
}

// Funkcja thresholdowania

int threshold(Image *image)
{
  int a,i,j;
  float threshold; /* Typ float, poniewaz threshold bedzie ostatecznie ulamkiem */
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold = (a / 100 * (image->greys));
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->pgm_image[i][j] <= threshold)
	      image->pgm_image[i][j] = 0;
      else
	      image->pgm_image[i][j] = image->greys;
    }
  }
  return 0;
}

// Funkcja polthresholdowania bieli

int halfThreshold(Image *image)
{
  /* Funkcja analogiczna do poprzedniej */
  int a,i,j;
  float threshold;
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold = (a / 100 * (image->greys));
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->pgm_image[i][j]<=threshold)
	      image->pgm_image[i][j] = image->pgm_image[i][j];
      else
	      image->pgm_image[i][j] = image->greys;
    }
  }
  return 0;
}

// Funkcja konturowania

int contour(Image *image)
{
  int i,j;
  /* Pierwsze i ostatnie piksele nie maja innych 'obok' siebie, a wiec
     ucinamy po jednym pikselu z kazdej strony */
  for(i = 0; i < (image->x - 1); i++){
    for(j = 0; j < (image->y - 1); j++){
      /* Wz�r na konturowanie */
      image->pgm_image[i][j] = abs(image->pgm_image[i+1][j] - image->pgm_image[i][j]) +
                               abs(image->pgm_image[i][j+1] - image->pgm_image[i][j]);
    }
  }
  /* Linie kodu napisane metoda prob i bledow. Cos dzialo sie z koncem fileu,
     wiec ponownie ucinamy ostatnie piksele */
  image->x = image->x--;
  image->y = image->y--;
  return 0;
}

// Funkcja rozciagania histogramu

int histogram(Image *image)
{
  int i,j,lmax,lmin;
  /* W tej petli thresholdram szuka minimalnej i maksymalnej wartosci */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->pgm_image[i][j] > lmax)
	      lmax = image->pgm_image[i][j];
      if(image->pgm_image[i][j] < lmin)
	      lmin = image->pgm_image[i][j];
    }
  }
  /* W tej petli dokonujemy faktycznego rociagniecia */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      image->pgm_image[i][j] = (image->pgm_image[i][j] - lmin) / (lmax-lmin) * (image->greys);
    }
  }
  return 0;
}
