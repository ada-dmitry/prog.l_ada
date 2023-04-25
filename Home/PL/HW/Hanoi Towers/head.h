#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 3
#define LEN 8

typedef struct LinkList {
    int x;
    char name[LEN];
    struct LinkList* next;
    struct LinkList* prev;
} LinkList;

void linked_print(LinkList* l);
LinkList* add_tail(LinkList* l, LinkList node);
LinkList* add_head(LinkList* l, LinkList node);
LinkList* del_head(LinkList* l);
void del_tail(LinkList* l);
int len(LinkList* l);
LinkList get(LinkList* l, int n);
void tower_of_hanoi(int n, LinkList* start, LinkList* finish, LinkList* tmp);
void linked_free(LinkList* l);