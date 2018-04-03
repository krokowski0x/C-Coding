#include <stdlib.h>
#include <stdio.h>
#include "stos.h"

void push(t_stos **stos, int pomoc)
{
   t_stos *tmp;
   tmp = (t_stos*) malloc(sizeof(t_stos));
   tmp->dana1 = pomoc;
   tmp->dana2 = *stos;
   *stos = tmp;
}

int pop(t_stos **stos)
{
  int pomoc;
  t_stos *tmp;

  if(*stos != NULL){
    pomoc = (*stos)->dana1;
    tmp = *stos;
    *stos = (*stos)->dana2;
    free(tmp);
    return pomoc;
  }
  else
    fprintf(stderr, "Stos jest pusty");
}

int empty(t_stos **stos)
{
  t_stos *tmp;
  int i;

  if(*stos == NULL)
    return 0;
  tmp = *stos;
  for(i = 0; tmp != NULL; i++)
    tmp = tmp->dana2;
  return i;
}

void print(t_stos **stos)
{
  t_stos *tmp;
  tmp = *stos;
  while(tmp != NULL){
    printf("%d ", tmp->dana1);
    tmp = tmp->dana2;
  }
  printf("\n");
}

int czytaj_opcje(t_stos **stos, char *tab[], int i, int quit){

  int a, b;

  switch(*tab[i]) {

  case '+':
    a = pop(stos);
    b = pop(stos);
    push(stos, (a+b));
    break;
  case '-':
    a = pop(stos);
    b = pop(stos);
    push(stos, (b-a));
    break;
  case '*':
    a = pop(stos);
    b = pop(stos);
    push(stos, (a*b));
    break;
  case '/':
    a = pop(stos);
    b = pop(stos);
    push(stos, (b/a));
    break;
  case '#':
    a = pop(stos);
    break;
  case '$':
    a = pop(stos);
    b = pop(stos);
    push(stos, a);
    push(stos, b);
    break;
  case '?':
    print(stos);
    break;
  case '&':
    a = pop(stos);
    push(stos, a);
    push(stos, a);
    break;
  case 'q':
    quit == 1;
    break;
  }
}
