
#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void pr(tower *tmp)
{
    if (tmp == NULL)
    {
        printf("[%p]\n", tmp);
        return;
    }
    while (tmp)
    {
        printf("[%14p]<-[%14p]->[%14p] ", tmp->prev, tmp, tmp->next);
        printf("data: [%4ld] s[%s]\n", tmp->data, tmp->s);
        tmp = tmp->next;
    }
    printf("-------------\n");
}
tower *add_head(tower *crown, int hh)
{
    tower *tmp = NULL;
    int i;
    if ((tmp = malloc(sizeof(tower))) == NULL)
    {
        perror("malloc: NULL");
        exit(2);
    }
    tmp->prev = NULL;
    tmp->data = hh;
    for (i = 0; i < N - 1; i++)
        tmp->s[i] = ((char)(65 + rand() % 25));
    tmp->s[N - 1] = '\0';
    if (crown == NULL)
        tmp->next = NULL;
    else
    {
        tmp->next = crown;
        crown->prev = tmp;
    }
    return tmp;
}
tower *del_head(tower *crown)
{
    tower *tmp = crown;
    if (crown == NULL)
        return NULL;
    if (crown->next == NULL)
    {
        free(crown);
        return NULL;
    }
    crown = crown->next;
    crown->prev = NULL;
    free(tmp);
    return crown;
}

int length(tower *list)
{
    tower *tmp = list;
    int res = 0;
    if (list == NULL)
        return 0;
    if (list->data == 0 && !strcmp(list->s, "\0"))
        return 0;
    else
    {
        while (tmp->prev != NULL)
            tmp = tmp->prev;
        while (tmp != NULL)
        {
            res++;
            tmp = tmp->next;
        }
    }
    return res;
}

tower *adv_add_head(tower *crown, int hh, char string[])
{
    tower *tmp = NULL;
    if ((tmp = malloc(sizeof(tower))) == NULL)
    {
        perror("malloc: NULL");
        exit(2);
    }
    tmp->prev = NULL;
    tmp->data = hh;
    memcpy(tmp->s, string, N);
    if (crown == NULL)
        tmp->next = NULL;
    else
    {
        tmp->next = crown;
        crown->prev = tmp;
    }
    return tmp;
}
void swap(tower *a, tower *b)
{
    tower *tmp = NULL;
    if ((tmp = malloc(sizeof(tower))) == NULL)
        exit(1);
    tmp->data = a->data;
    a->data = b->data;
    b->data = tmp->data;
    memcpy(tmp->s, a->s, N);
    memcpy(a->s, b->s, N);
    memcpy(b->s, tmp->s, N);
    free(tmp);
}

tower *get(tower *list, int n)
{
    if (n >= length(list))
        exit(3);
    int i;
    for (i = 0; i < n; i++)
        list = list->next;
    return list;
}

tower *sort(tower *crown)
{
    if (crown == NULL || crown->next == NULL)
        return crown;
    int i, j, n = length(crown);
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (get(crown, j)->data < get(crown, i)->data)
                swap(get(crown, i), get(crown, j));
        }
    }
    return crown;
}
tower *printextra(tower *crown, int len, int i)
{
    if (len < i || len == 0)
    {
        printf("*********************************|");
        return crown;
    }
    else
    {
        printf("[%14p] data: [%4ld] s[%s]|", crown, crown->data, crown->s);
        return crown->prev;
    }
}
tower *end(tower *crown)
{
    tower *tmp = NULL;
    tmp = crown;
    if (crown == NULL)
        return crown;
    while (tmp->next != NULL)
        tmp = tmp->next;
    return tmp;
}

void printftof(tower *head1, tower *head2, tower *head3)
{
    int a = length(head1), b = length(head2), c = length(head3), maximum, i;
    maximum = max(a, b);
    maximum = max(maximum, c);
    head1 = end(head1);
    head2 = end(head2);
    head3 = end(head3);
    for (i = maximum; i > 0; i--)
    {
        head1 = printextra(head1, a, i);
        head2 = printextra(head2, b, i);
        head3 = printextra(head3, c, i);
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("Tower 1                           |Tower 2                           |Tower 3                           |\n");
    printf("----------------------------------------------------------------------------------------------------------\n\n");
}
int max(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}

void hanoi_tower(int n, tower **head_from, tower **head_to, tower **head_aux, tower **const tower1, tower **const tower2, tower **const tower3)
{
    if (n == 0)
    {
        printf("No linked list");
        exit(6);
    }
    else if (n == 1)
    {
        if (length(*head_to) == 0)
            printftof(*tower1, *tower2, *tower3);
        *head_to = adv_add_head(*head_to, (*head_from)->data, (*head_from)->s);
        *head_from = del_head(*head_from);
        if (length(*head_from) == 0)
            printftof(*tower1, *tower2, *tower3);
        return;
    }
    hanoi_tower(n - 1, head_from, head_aux, head_to, tower1, tower2, tower3);
    printftof(*tower1, *tower2, *tower3);
    *head_to = adv_add_head(*head_to, (*head_from)->data, (*head_from)->s);
    *head_from = del_head(*head_from);
    printftof(*tower1, *tower2, *tower3);
    hanoi_tower(n - 1, head_aux, head_to, head_from, tower1, tower2, tower3);
}