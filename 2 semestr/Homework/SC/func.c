#include "head.h"
#include <stdio.h>
#include <stdlib.h>

void linked_print(Stack *l) // Вывод стека
{
  while (l != NULL)
  {
    printf("%lF\n", l->x);
    l = l->next;
  }
}

Stack *add_head(Stack *l, double x) // Добавление головы, причем в двух вариациях(если голова изначально есть и если её нет)
{
  if (l == NULL)
  {
    l = malloc(sizeof(Stack));
    if (l == NULL)
      exit(1);
    l->x = x;
    l->next = NULL;
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
