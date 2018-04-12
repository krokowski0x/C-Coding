#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void push(t_stack **stack, int help)
{
   t_stack *tmp;
   tmp = (t_stack*) malloc(sizeof(t_stack));
   tmp->data1 = help;
   tmp->data2 = *stack;
   *stack = tmp;
}

int pop(t_stack **stack)
{
  int help;
  t_stack *tmp;

  if(*stack != NULL){
    help = (*stack)->data1;
    tmp = *stack;
    *stack = (*stack)->data2;
    free(tmp);
    return help;
  }
  else
    fprintf(stderr, "Stack is empty");
}

int empty(t_stack **stack)
{
  t_stack *tmp;
  int i;

  if(*stack == NULL)
    return 0;
  tmp = *stack;
  for(i = 0; tmp != NULL; i++)
    tmp = tmp->data2;
  return i;
}

void print(t_stack **stack)
{
  t_stack *tmp;
  tmp = *stack;
  while(tmp != NULL){
    printf("%d ", tmp->data1);
    tmp = tmp->data2;
  }
  printf("\n");
}

int read_options(t_stack **stack, char *arr[], int i, int quit){

  int a, b;

  switch(*arr[i]) {

  case '+':
    a = pop(stack);
    b = pop(stack);
    push(stack, (a+b));
    break;
  case '-':
    a = pop(stack);
    b = pop(stack);
    push(stack, (b-a));
    break;
  case '*':
    a = pop(stack);
    b = pop(stack);
    push(stack, (a*b));
    break;
  case '/':
    a = pop(stack);
    b = pop(stack);
    push(stack, (b/a));
    break;
  case '#':
    a = pop(stack);
    break;
  case '$':
    a = pop(stack);
    b = pop(stack);
    push(stack, a);
    push(stack, b);
    break;
  case '?':
    print(stack);
    break;
  case '&':
    a = pop(stack);
    push(stack, a);
    push(stack, a);
    break;
  case 'q':
    quit == 1;
    break;
  }
}
