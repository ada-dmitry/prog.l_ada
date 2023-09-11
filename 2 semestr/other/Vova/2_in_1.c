#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 3
#define LENG 3

typedef struct Node
{
  struct Node *next;
  struct Node *pr;
  char name[LENG];
} Node;

void node_print(Node *n)
{
  while (n != NULL)
  {
    printf("%s\n", n->name);
    n = n->next;
  }
}

Node *add_tail(Node *n, char s[])
{
  Node *res = n;
  Node *tmp = malloc(sizeof(Node));
  if (n == NULL)
  {
    if ((n = malloc(sizeof(Node))) == NULL)
    {
      printf("Deny malloc\n");
      exit(1);
    }
    n->next = NULL;
    n->pr = NULL;
    memcpy(n->name, s, LENG);
    return n;
  }
  if (!strcmp(n->name, "\0"))
  {
    memcpy(n->name, s, LENG);
    n->next = NULL;
    n->pr = NULL;
    return n;
  }

  while (n->next != NULL)
    n = n->next;

  memcpy(tmp->name, s, LENG);
  tmp->pr = n;
  n->next = tmp;
  return res;
}

Node get(Node *node, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    node = node->next;
  }
  return *node;
}

int len(Node *n)
{
  int res = 0;
  while (n != NULL)
  {
    res++;
    n = n->next;
  }
  return res;
}

Node *find_0(Node *n1, Node *n2)
{
  int i, j, f = 0;
  Node *res = NULL;
  if ((res = malloc(sizeof(Node))) == NULL)
  {
    printf("Deny malloc\n");
    exit(3);
  }

  for (i = 0; i < len(n1); i++)
  {
    Node tmp1 = get(n1, i);
    for (j = 0; j < len(n2); j++)
    {
      Node tmp2 = get(n2, j);
      if (strcmp(tmp1.name, tmp2.name) == 0)
      {
        f = 1;
      }
    }
    if (f == 0)
    {
      Node tmp = get(n1, i);
      res = add_tail(res, tmp.name);
    }
    f = 0;
  }

  for (i = 0; i < len(n2); i++)
  {
    Node tmp2 = get(n2, i);
    for (j = 0; j < len(n1); j++)
    {
      Node tmp1 = get(n1, j);
      if (strcmp(tmp2.name, tmp1.name) == 0)
      {
        f = 1;
      }
    }
    if (f == 0)
    {
      Node tmp = get(n2, i);
      res = add_tail(res, tmp.name);
    }
    f = 0;
  }

  return res;
}

int main()
{
  Node *n1 = NULL;
  Node *n2 = NULL;
  Node *n3 = NULL;
  int i;
  printf("Hello. Let's begin\n");
  printf("\n");
  srand(time(0));

  if ((n1 = malloc(sizeof(Node))) == NULL ||
      (n2 = malloc(sizeof(Node))) == NULL ||
      (n3 = malloc(sizeof(Node))) == NULL)
  {
    printf("Deny malloc\n");
    exit(2);
  }

  for (i = 0; i < N; i++)
  {
    char s[LENG];
    int j;

    for (j = 0; j < LENG - 1; j++)
      s[j] = 'a' + rand() % 2;
    s[LENG - 1] = '\0';

    n1 = add_tail(n1, s);

    for (j = 0; j < LENG - 1; j++)
      s[j] = 'a' + rand() % 2;
    s[LENG - 1] = '\0';
    n2 = add_tail(n2, s);
  }

  printf("Initial arrays:\n");
  node_print(n1);
  printf("\n");
  node_print(n2);

  n3 = find_0(n1, n2);

  printf("\n");
  printf("Final array:\n");
  node_print(n3);

  free(n1);
  free(n2);
  free(n3);

  printf("\n");
  printf("That's all for now\n");

  return 0;
}
