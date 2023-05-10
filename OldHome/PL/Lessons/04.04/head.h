#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    int x;
    struct Node* next;
    struct Node* prev;
    char name[STR_LEN];
} Node;