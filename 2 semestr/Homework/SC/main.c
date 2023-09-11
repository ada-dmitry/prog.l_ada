#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  srand(time(0));
  Stack *numbers = NULL;
  char c;

  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
    {
      break;
    }
    else if (c == ' ')
    {
      continue;
    }

    switch (c)
    {
    case '0' ... '9':
      numbers = add_head(numbers, (double)(c - '0'));
      break;

    case '+':
    case '-':
    case '*':
    case '/':

      double a = numbers->x;
      numbers = del_head(numbers);
      double b = numbers->x;
      numbers = del_head(numbers);

      b = (c == '+') ? b + a : b;
      b = (c == '-') ? b - a : b;
      b = (c == '*') ? b * a : b;
      b = (c == '/') ? b / a : b;

      numbers = add_head(numbers, b);
      break;
    }
  }

  printf("res: %lF\n", numbers->x);

  free(numbers);
  return 0;
}