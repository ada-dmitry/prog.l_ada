#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5
#define STR_LEN 8

typedef struct Node {
    int x;
    struct Node* next;
    struct Node* prev;
    char name[STR_LEN];
} Node;

void linked_print(Node* l);
Node* add_tail(Node* l, int x, char name[]);
Node* add_head(Node* l, int x, char name[]);
Node* del_head(Node* l);
void del_tail(Node* l);
int len(Node* l);
Node get(Node* l, int n);

void swap(Node* l1, int i, int j);
void select_sort(Node* l);
void list_fprintf(Node* l, char path[]);
Node* list_fscanf(char path[]);