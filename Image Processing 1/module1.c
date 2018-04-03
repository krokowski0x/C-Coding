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

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII,plik_we) == NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0] != 'P') || (buf[1]!='2') || koniec ) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak = fgetc(plik_we)) == '#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we) == NULL)  /* Przeczytaj ja do bufora                */
	      koniec = 1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak, plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we, "%d %d %d", obraz->wymx, obraz->wymy, obraz->szarosci) != 3) {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i = 0; i < obraz->wymy; i++) {
    for (j = 0; j < obraz->wymx; j++) {
      if (fscanf(plik_we, "%d", &(obraz->obraz_pgm[i][j])) !=1 ) {
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

  strcpy(polecenie, "display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

// Funkcja zapisujaca edytowany obraz

int zapisz(TObraz *obraz)
{
  FILE *plik;
  int i,j;
  plik = fopen("obraz.pgm","w");
  /* Wy�wietlamy najpierw informacje o obrazie */
  fprintf(plik, "P2\n %d %d\n %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
  for (j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      /* Zapisujemy do pliku kolejne piksele z tablicy */
      fprintf(plik, "%d\n", obraz->obraz_pgm[i][j]);
	}
 }
  return 0;
}

// Funkcja negatywu

int neg(TObraz *obraz)
{
  int i,j;
  for (j = 0; j < obraz->wymy; j++){
    for (i = 0; i < obraz->wymx; i++){
      /* Od maksymalnej wartosci (szarosci) odejmujemy wartosc danego piksela */
      obraz->obraz_pgm[i][j] = (obraz->szarosci - obraz->obraz_pgm[i][j]);
    }
  }
  return 0;
}

// Funkcja progowania

int progow(TObraz *obraz)
{
  int a,i,j;
  float prog; /* Typ float, poniewaz prog bedzie ostatecznie ulamkiem */
  printf("Podaj prog w procentach:\n");
  scanf("%d", &a);
  prog = (a / 100 * (obraz->szarosci));
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      if(obraz->obraz_pgm[i][j] <= prog)
	obraz->obraz_pgm[i][j] = 0;
      else
	obraz->obraz_pgm[i][j] = obraz->szarosci;
    }
  }
  return 0;
}

// Funkcja polprogowania bieli

int polprogowB(TObraz *obraz)
{
  /* Funkcja analogiczna do poprzedniej */
  int a,i,j;
  float prog;
  printf("Podaj prog w procentach:\n");
  scanf("%d", &a);
  prog = (a / 100 * (obraz->szarosci));
  for(j = 0; j < obraz->wymy; j++){
    for(i = 0; i < obraz->wymx; i++){
      if(obraz->obraz_pgm[i][j]<=prog)
	obraz->obraz_pgm[i][j] = obraz->obraz_pgm[i][j];
      else
	obraz->obraz_pgm[i][j] = obraz->szarosci;
    }
  }
  return 0;
}

// Funkcja konturowania

int kont(TObraz *obraz)
{
  int i,j;
  /* Pierwsze i ostatnie piksele nie maja innych 'obok' siebie, a wiec
     ucinamy po jednym pikselu z kazdej strony */
  for(i = 0; i < (obraz->wymx - 1); i++){
 for(j = 0; j < (obraz->wymy - 1); j++){
      /* Wz�r na konturowanie */
      obraz->obraz_pgm[i][j] = abs(obraz->obraz_pgm[i+1][j] - obraz->obraz_pgm[i][j]) +
                               abs(obraz->obraz_pgm[i][j+1] - obraz->obraz_pgm[i][j]);
    }
  }
  /* Linie kodu napisane metoda prob i bledow. Cos dzialo sie z koncem pliku,
     wiec ponownie ucinamy ostatnie piksele */
  obraz->wymx = obraz->wymx--;
    obraz->wymy = obraz->wymy--;
  return 0;
}

// Funkcja rozciagania histogramu

int hist(TObraz *obraz)
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
      obraz->obraz_pgm[i][j] = (obraz->obraz_pgm[i][j] - lmin) / (lmax-lmin) * (obraz->szarosci);
    }
  }
  return 0;
}
