#ifndef STOS_H
#define STOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stos
{
   int dana1;
   struct stos *dana2;
} t_stos;

void push(t_stos **stos, int pomoc);
int pop(t_stos **stos);
int empty(t_stos **stos);
void print(t_stos **stos);
int czytaj_opcje(t_stos **stos, char *tab[], int i, int quit);

#endif
