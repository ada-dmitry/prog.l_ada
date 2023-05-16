#include "head.h"
#include <stdio.h>
#include <stdlib.h>

void linked_print(Stack *l)
{
  while (l != NULL)
  {
    printf("%lF\n", l->x);
    l = l->next;
  }
}

Stack *add_head(Stack *l, double x)
{
  if (l == NULL)
  {
    l = malloc(sizeof(Stack));
    if (l == NULL)
      exit(1);
    l->x = x;
    l->next = NULL;
  }

  if (l->x == 0.0)
  {
    l->x = x;
    l->next = NULL;
    return l;
  }

  Stack *tmp = malloc(sizeof(Stack));
  if (tmp == NULL)
    exit(1);

  tmp->next = l;
  tmp->x = x;
  return tmp;
}

Stack *del_head(Stack *l)
{
  if (l == NULL)
    return NULL;
  else if (l->next == NULL)
  {
    free(l);
    l = NULL;
    return NULL;
  }
  Stack *tmp = l->next;
  free(l);
  l = NULL;
  return tmp;
}

int len(Stack *l)
{
  int res = 0;
  while (l != NULL)
  {
    res++;
    l = l->next;
  }
  return res;
}

Stack get(Stack *l, int n)
{
  if (n > len(l))
    exit(3);
  int i;
  for (i = 0; i < n; i++)
  {
    l = l->next;
  }
  return *l;
}