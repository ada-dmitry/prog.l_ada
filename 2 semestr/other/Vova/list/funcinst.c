#include "head.h"

void node_print(Node *n)
{
    while (n != NULL)
    {
        printf("%s\n", n->name);
        n = n->ne;
    }
}

int len(Node *n)
{
    int f = 0;
    while (n != NULL)
    {
        f++;
        n = n->ne;
    }
    return f;
}

Node *add_tail(Node *n, char s[])
{
    if (n == NULL)
    {
        if ((n = malloc(sizeof(Node))) == NULL)
        {
            printf("No memory for you\n");
            exit(1);
        }
        n->ne = NULL;
        n->prv = NULL;
        memcpy(n->name, s, LEN);
        return n;
    }
    if (!strcmp(n->name, "\0"))
    {
        memcpy(n->name, s, LEN);
        n->ne = NULL;
        n->prv = NULL;
        return n;
    }
    Node *res = n;
    while (n->ne != NULL)
    {
        printf("%p\n", n);
        n = n->ne;
    }
    Node *tmp = malloc(sizeof(Node));
    memcpy(tmp->name, s, LEN);
    tmp->prv = n;
    n->ne = tmp;
    return res;
}

Node get(Node *node, int n)
{
    int k;
    for (k = 0; k < n; k++)
    {
        node = node->ne;
    }
    return *node;
}

Node *find_0(Node *n1, Node *n2)
{
    int i, j, f = 0;
    Node *res = NULL;
    if ((res = malloc(sizeof(Node))) == NULL)
    {
        printf("No memory for you\n");
        exit(3);
    }

    for (i = 0; i < len(n1); i++)
    {
        for (j = 0; j < len(n2); j++)
        {
            if (strcmp(get(n1, i).name, get(n2, j).name) == 0)
            {
                f = 1;
            }
        }
        if (f == 0)
            res = add_tail(res, get(n1, i).name);
        f = 0;
    }

    for (i = 0; i < len(n2); i++)
    {
        for (j = 0; j < len(n1); j++)
        {
            if (strcmp(get(n2, i).name, get(n1, j).name) == 0)
            {
                f = 1;
            }
        }
        if (f == 0)
            res = add_tail(res, get(n2, i).name);
        f = 0;
    }

    return res;
}