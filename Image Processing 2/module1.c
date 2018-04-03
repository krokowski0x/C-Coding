#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>           /* Biblioteka dodana, aby wykorzystac funkcje ABS */
#include "module1.h"

// Funkcja odczytu pliku
int czytaj(FILE *plik_we, TObraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;          /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL) {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" */
  if (fgets(buf,DL_LINII, plik_we) == NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0] != 'P') || koniec) {  /* Czy jest magiczne "P"? */
    fprintf(stderr, "Blad: To nie jest dobry plik\n");
    return(0);
  }

  if (buf[1] == '2' || buf[1] == '3') {
    if (buf[1] == '2')
      obraz->kolor = 0;
    else
      obraz->kolor = 1;
  } else
      fprintf(stderr, "Blad: To nie jest dobry plik\n");
  return(0);

  /* Pominiecie komentarzy */
  do {
    if ((znak = fgetc(plik_we)) == '#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, plik_we) == NULL)  /* Przeczytaj ja do bufora                */
	koniec = 1;                   /* Zapamietaj ewentualny koniec danych */
    } else {
      ungetc(znak, plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we, "%d %d %d", obraz->wymx, obraz->wymy, obraz->szarosci) != 3) {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }

  //Przypadek obrazu PPM - konwersja do PGM
  if(obraz->kolor == 1) {
    for(i = 0; i < obraz->wymy; i++) {
      for(j = 0; j < obraz->wymx; j++) {
	      obraz->obraz_pgm[i][j] = (obraz->R[i][j] + obraz->G[i][j] + obraz->B[i][j] / 3);
      }
    }
  }


  //Tablica na obraz PGM
  obraz->obrazek = (int *) calloc(obraz->wymx * obraz->wymy, sizeof(int));

  /* Pobranie obrazu PGM i zapisanie w tablicy */
    for (i = 0; i < obraz->wymy; i++) {
      for (j = 0; j < obraz->wymx; j++) {
	if (fscanf(plik_we, "%d", &(obraz->obraz_pgm[i][j])) != 1) {
	  fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
	}
      }
    }
  return obraz->wymx * obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                                    /* Zwroc liczbe wczytanych pikseli */

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display ");   /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

// Funkcja zapisujaca edytowany obraz

void zapisz(w_opcje *plik, TObraz *obraz)
{
  int i,j;
  plik->plik_we = fopen("obraz.pgm", "w");
  /* Wyswietlamy najpierw informacje o obrazie */
  fprintf(plik->plik_we, "P2\n %d %d\n %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
  for (j = 0; j < obraz->wymy; j++) {
    for(i = 0; i < obraz->wymx; i++) {
      /* Zapisujemy do pliku kolejne piksele z tablicy */
      fprintf(plik->plik_we, "%d", obraz->obraz_pgm[i][j]);
	  }
  }
}

// Funkcja negatywu

void neg(TObraz *obraz)
{
  int i,j;
  for (j = 0; j < obraz->wymy; j++) {
    for (i = 0; i < obraz->wymx; i++) {
      /* Od maksymalnej wartosci (szarosci) odejmujemy wartosc danego piksela */
      obraz->obraz_pgm[i][j] = (obraz->szarosci - obraz->obraz_pgm[i][j]);
    }
  }
}

// Funkcja progowania

void progow(TObraz *obraz)
{
  int a,i,j;
  float prog; /* Typ float, poniewaz prog bedzie ostatecznie ulamkiem */
  printf("Podaj prog w procentach:\n");
  scanf("%d", &a);
  prog=(a / 100 * (obraz->szarosci));
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      if(obraz->obraz_pgm[i][j] <= prog)
	      obraz->obraz_pgm[i][j] = 0;
      else
	      obraz->obraz_pgm[i][j] = obraz->szarosci;
    }
  }
}

// Funkcja polprogowania bieli

void polprogowB(TObraz *obraz)
{
  /* Funkcja analogiczna do poprzedniej */
  int a,i,j;
  float prog;
  printf("Podaj prog w procentach:\n");
  scanf("%d", &a);
  prog=(a / 100 * (obraz->szarosci));
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      if(obraz->obraz_pgm[i][j] <= prog)
	      obraz->obraz_pgm[i][j] = obraz->obraz_pgm[i][j];
      else
	      obraz->obraz_pgm[i][j] = obraz->szarosci;
    }
  }
}

// Funkcja konturowania

void kont(TObraz *obraz)
{
  int i,j;
  /* Pierwsze i ostatnie piksele nie maja innych 'obok' siebie, a wiec
     ucinamy po jednym pikselu z kazdej strony */
  for(i = 0; i < (obraz->wymx-1); i++){
    for(j = 0; j < (obraz->wymy-1); j++){
      /* Wz�r na konturowanie */
      obraz->obraz_pgm[i][j] = abs(obraz->obraz_pgm[i+1][j] - obraz->obraz_pgm[i][j]) +
                               abs(obraz->obraz_pgm[i][j+1] - obraz->obraz_pgm[i][j]);
    }
  }
  obraz->wymx--;
  obraz->wymy--;
}

// Funkcja rozciagania histogramu

void hist(TObraz *obraz)
{
  int i,j,lmax,lmin;
  /* W tej petli program szuka minimalnej i maksymalnej wartosci */
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      if(obraz->obraz_pgm[i][j] > lmax)
	      lmax = obraz->obraz_pgm[i][j];
      if(obraz->obraz_pgm[i][j] < lmin)
	      lmin = obraz->obraz_pgm[i][j];
    }
  }
  /* W tej petli dokonujemy faktycznego rociagniecia */
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      obraz->obraz_pgm[i][j] = (obraz->obraz_pgm[i][j]-lmin) / (lmax-lmin) * (obraz->szarosci);
    }
  }
}

void wyzeruj_opcje(w_opcje *wybor){
  wybor->plik_we = NULL;
  wybor->plik_wy = NULL;
  wybor->neg = 0;
  wybor->kont = 0;
  wybor->progow = 0;
  wybor->wyswietl = 0;
  wybor->polprogowB = 0;
  wybor->hist = 0;
}

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i, prog;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy = stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
      	nazwa_pliku_we = argv[i];
      	if (strcmp(nazwa_pliku_we, "-")==0) /* gdy nazwa jest "-"        */
      	  wybor->plik_we = stdin;            /* ustwiamy wejscie na stdin */
      	else                               /* otwieramy wskazany plik   */
      	  wybor->plik_we=fopen(nazwa_pliku_we, "r");
      } else
  	     return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
    break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy = argv[i];
	if (strcmp(nazwa_pliku_wy, "-") == 0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy = stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	  wybor->plik_wy = fopen(nazwa_pliku_wy, "w");
      } else
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d", &prog) == 1) {
	  wybor->progow = 1;
	  wybor->w_progu = prog;
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }
    case 'b': {
      if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d", &prog) == 1) {
	  wybor->polprogowB = 1;
	  wybor->w_progu = prog;
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;

    case 'n': {                 /* mamy wykonac negatyw */
      wybor->neg = 1;
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      wybor->kont = 1;
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietl = 1;
      break;
    }
    case 'h': {
      wybor->hist = 1;
      break;
    }
    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

    if(wybor->plik_we = NULL){
      return B_BRAKPLIKU;}
    return 0;
  }
}
