#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 6

typedef struct Stack {
  double x;
  struct Stack *next;
} Stack;

Stack get(Stack *l, int n);
Stack *add_head(Stack *l, double x);
void stack_print(Stack *l);
int len(Stack *l);
Stack *del_head(Stack *l);
