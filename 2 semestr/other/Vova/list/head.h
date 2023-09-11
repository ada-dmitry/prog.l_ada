#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CO 3
#define LEN 3

typedef struct Node
{
    char name[LEN];
    struct Node *ne;
    struct Node *prv;
} Node;

void node_print(Node *n);
Node *add_tail(Node *n, char s[]);
Node get(Node *node, int n);
Node *find_0(Node *n1, Node *n2);
int len(Node *n);