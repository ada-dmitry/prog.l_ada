#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5
#define LEN 5

typedef struct Unit
{
    struct Unit *next;
    struct Unit *prev;
    char name[LEN];
} Unit;

void node_print(Unit *n);
Unit get(Unit *node, int n);
Unit *xor_find(Unit *n1, Unit *n2);
Unit *add_tail(Unit *n, char s[]);