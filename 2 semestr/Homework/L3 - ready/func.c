#include "head.h"

void node_print(Unit *n)
{
    while (n != NULL)
    {
        printf("%s\n", n->name);
        n = n->next;
    }
}

Unit get(Unit *node, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        node = node->next;
    }
    return *node;
}

int len(Unit *n)
{
    int res = 0;
    while (n != NULL)
    {
        res++;
        n = n->next;
    }
    return res;
}

Unit *xor_find(Unit *n1, Unit *n2)
{
    int i, j, f = 0;
    Unit *res = NULL;
    if ((res = malloc(sizeof(Unit))) == NULL)
    {
        printf("could not malloc\n");
        exit(3);
    }

    for (i = 0; i < len(n1); i++)
    {
        Unit tmp1 = get(n1, i);
        for (j = 0; j < len(n2); j++)
        {
            Unit tmp2 = get(n2, j);
            if (strcmp(tmp1.name, tmp2.name) == 0)
            {
                f = 1;
            }
        }
        if (f == 0)
        {
            Unit tmp = get(n1, i);
            res = add_tail(res, tmp.name);
        }
        f = 0;
    }

    for (i = 0; i < len(n2); i++)
    {
        Unit tmp2 = get(n2, i);
        for (j = 0; j < len(n1); j++)
        {
            Unit tmp1 = get(n1, j);
            if (strcmp(tmp2.name, tmp1.name) == 0)
            {
                f = 1;
            }
        }
        if (f == 0)
        {
            Unit tmp = get(n2, i);
            res = add_tail(res, tmp.name);
        }
        f = 0;
    }

    return res;
}

Unit *add_tail(Unit *n, char s[])
{
    if (n == NULL)
    {
        if ((n = malloc(sizeof(Unit))) == NULL)
        {
            printf("could not malloc\n");
            exit(1);
        }
        n->next = NULL;
        n->prev = NULL;
        memcpy(n->name, s, LEN);
        return n;
    }
    if (!strcmp(n->name, "\0"))
    {
        memcpy(n->name, s, LEN);
        n->next = NULL;
        n->prev = NULL;
        return n;
    }

    Unit *res = n;
    while (n->next != NULL)
        n = n->next;

    Unit *tmp = malloc(sizeof(Unit));
    memcpy(tmp->name, s, LEN);
    tmp->prev = n;
    n->next = tmp;
    return res;
}
