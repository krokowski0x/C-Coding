#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#include "module1.h"

// Funkcja odczytu pliku
int read(FILE *input_file, Image *image) {
  char buff[LINE_LENGTH];      /* buffor pomocniczy do czytania naglowka i komentarzy */
  int character;                /* zmienna pomocnicza do czytania komentarzy */
  int end = 0;          /* czy napotkano end danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (input_file == NULL) {
    fprintf(stderr, "Error: No file handle\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznegativeo" */
  if (fgets(buff,LINE_LENGTH, input_file) == NULL)   /* Wczytanie pierwszej linii pliku do buffora */
    end = 1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buff[0] != 'P') || end) {  /* Czy jest magiczne "P"? */
    fprintf(stderr, "Error: File not found\n");
    return(0);
  }

  if (buff[1] == '2' || buff[1] == '3') {
    if (buff[1] == '2')
      image->color = 0;
    else
      image->color = 1;
  } else
      fprintf(stderr, "Error: File not found\n");
  return(0);

  /* Pominiecie komentarzy */
  do {
    if ((character = fgetc(input_file)) == '#') {         /* Czy linia rozpoczyna sie od characteru '#'? */
      if (fgets(buff, LINE_LENGTH, input_file) == NULL)  /* Przeczytaj ja do buffora                */
	      end = 1;                   /* Zapamietaj ewentualny end danych */
    } else {
      ungetc(character, input_file);                   /* Gdy przeczytany character z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (character == '#' && !end);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil end danych         */

  /* Pobranie wymiarow imageu i liczby odcieni greys */
  if (fscanf(input_file, "%d %d %d", image->x, image->y, image->greys) != 3) {
    fprintf(stderr, "Error: Image size or greys not found\n");
    return(0);
  }

  //Przypadek imageu PPM - konwersja do PGM
  if(image->color == 1) {
    for(i = 0; i < image->y; i++) {
      for(j = 0; j < image->x; j++) {
	      image->image_pgm[i][j] = (image->R[i][j] + image->G[i][j] + image->B[i][j] / 3);
      }
    }
  }


  //Tablica na image PGM
  image->imageek = (int *) calloc(image->x * image->y, sizeof(int));

  /* Pobranie imageu PGM i zapisanie w tablicy */
    for (i = 0; i < image->y; i++) {
      for (j = 0; j < image->x; j++) {
	if (fscanf(input_file, "%d", &(image->image_pgm[i][j])) != 1) {
	  fprintf(stderr, "Error: Wrong image size\n");
	  return(0);
	}
      }
    }
  return image->x * image->y;   /* Czytanie zakonczone sukcesem    */
}                                    /* Zwroc liczbe wczytanych pikseli */

/* Wyswietlenie imageu o zadanej nazwie za pomoca thresholdramu "display"   */
void show(char *n_pliku) {
  char polecenie[LINE_LENGTH];      /* buffor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display ");   /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie);      /* wydruk contourolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

// Funkcja zapisujaca edytowany image

void zapisz(w_opcje *plik, Image *image)
{
  int i,j;
  plik->input_file = fopen("image.pgm", "w");
  /* Wyswietlamy najpierw informacje o imageie */
  fprintf(plik->input_file, "P2\n %d %d\n %d\n", image->x, image->y, image->greys);
  for (j = 0; j < image->y; j++) {
    for(i = 0; i < image->x; i++) {
      /* Zapisujemy do pliku kolejne piksele z tablicy */
      fprintf(plik->input_file, "%d", image->image_pgm[i][j]);
	  }
  }
}

// Funkcja negativeatywu

void negative(Image *image)
{
  int i,j;
  for (j = 0; j < image->y; j++) {
    for (i = 0; i < image->x; i++) {
      /* Od maksymalnej wartosci (greys) odejmujemy wartosc danegativeo piksela */
      image->image_pgm[i][j] = (image->greys - image->image_pgm[i][j]);
    }
  }
}

// Funkcja thresholdowania

void thresholdow(Image *image)
{
  int a,i,j;
  float threshold; /* Typ float, poniewaz threshold bedzie ostatecznie ulamkiem */
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold=(a / 100 * (image->greys));
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->image_pgm[i][j] <= threshold)
	      image->image_pgm[i][j] = 0;
      else
	      image->image_pgm[i][j] = image->greys;
    }
  }
}

// Funkcja polthresholdowania bieli

void halfThreshold(Image *image)
{
  /* Funkcja analogiczna do poprzedniej */
  int a,i,j;
  float threshold;
  printf("Enter threshold in percentage:\n");
  scanf("%d", &a);
  threshold = (a / 100 * (image->greys));
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->image_pgm[i][j] <= threshold)
	      image->image_pgm[i][j] = image->image_pgm[i][j];
      else
	      image->image_pgm[i][j] = image->greys;
    }
  }
}

// Funkcja contourowania

void contour(Image *image)
{
  int i,j;
  /* Pierwsze i ostatnie piksele nie maja innych 'obok' siebie, a wiec
     ucinamy po jednym pikselu z kazdej strony */
  for(i = 0; i < (image->x-1); i++){
    for(j = 0; j < (image->y-1); j++){
      /* Wz�r na contourowanie */
      image->image_pgm[i][j] = abs(image->image_pgm[i+1][j] - image->image_pgm[i][j]) +
                               abs(image->image_pgm[i][j+1] - image->image_pgm[i][j]);
    }
  }
  image->x--;
  image->y--;
}

// Funkcja rozciagania histogramu

void histogram(Image *image)
{
  int i,j,lmax,lmin;
  /* W tej petli thresholdram szuka minimalnej i maksymalnej wartosci */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      if(image->image_pgm[i][j] > lmax)
	      lmax = image->image_pgm[i][j];
      if(image->image_pgm[i][j] < lmin)
	      lmin = image->image_pgm[i][j];
    }
  }
  /* W tej petli dokonujemy faktycznegativeo rociagniecia */
  for(j = 0; j < image->y; j++){
    for(i = 0; i < image->x; i++){
      image->image_pgm[i][j] = (image->image_pgm[i][j]-lmin) / (lmax-lmin) * (image->greys);
    }
  }
}

void reset_options(w_opcje *choice){
  choice->input_file = NULL;
  choice->output_file = NULL;
  choice->negative = 0;
  choice->contour = 0;
  choice->thresholdow = 0;
  choice->show = 0;
  choice->halfThreshold = 0;
  choice->histogram = 0;
}

int process_options(int argc, char **argv, w_opcje *choice) {
  int i, threshold;
  char *input_file_name, *output_file_name;

  reset_options(choice);
  choice->output_file = stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak characteru "-" */
      return WRONG_OPTION;
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
      	input_file_name = argv[i];
      	if (strcmp(input_file_name, "-")==0) /* gdy nazwa jest "-"        */
      	  choice->input_file = stdin;            /* ustwiamy wejscie na stdin */
      	else                               /* otwieramy wskazany plik   */
      	  choice->input_file=fopen(input_file_name, "r");
      } else
  	     return NO_NAME;                   /* blad: brak nazwy pliku */
    break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	output_file_name = argv[i];
	if (strcmp(output_file_name, "-") == 0)/* gdy nazwa jest "-"         */
	  choice->output_file = stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	  choice->output_file = fopen(output_file_name, "w");
      } else
	return NO_NAME;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i < argc) { /* wczytujemy kolejny argument jako wartosc thresholdu */
	if (sscanf(argv[i],"%d", &threshold) == 1) {
	  choice->thresholdow = 1;
	  choice->threshold_value = threshold;
	} else
	  return NO_VALUE;     /* blad: niepoprawna wartosc thresholdu */
      } else
	return NO_VALUE;             /* blad: brak wartosci thresholdu */
      break;
    }
    case 'b': {
      if (++i < argc) { /* wczytujemy kolejny argument jako wartosc thresholdu */
	if (sscanf(argv[i],"%d", &threshold) == 1) {
	  choice->halfThreshold = 1;
	  choice->threshold_value = threshold;
	} else
	  return NO_VALUE;     /* blad: niepoprawna wartosc thresholdu */
      } else
	return NO_VALUE;             /* blad: brak wartosci thresholdu */
      break;

    case 'n': {                 /* mamy wykonac negativeatyw */
      choice->negative = 1;
      break;
    }
    case 'k': {                 /* mamy wykonac contourowanie */
      choice->contour = 1;
      break;
    }
    case 'd': {                 /* mamy showic image */
      choice->show = 1;
      break;
    }
    case 'h': {
      choice->histogram = 1;
      break;
    }
    default:                    /* nierozpoznana opcja */
      return WRONG_OPTION;
    } /*end switch */
  } /* end for */

    if(choice->input_file = NULL){
      return NO_FILE;}
    return 0;
  }
}
