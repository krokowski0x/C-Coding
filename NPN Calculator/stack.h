#ifndef STACK_H
#define STSCK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack
{
   int data1;
   struct stack *data2;
} t_stack;

void push(t_stack **stack, int pomoc);
int  pop(t_stack **stack);
int  empty(t_stack **stack);
void print(t_stack **stack);
int  read_options(t_stack **stack, char *arr[], int i, int quit);

#endif
