#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    int x;
    struct node* next;
}Plate;

void print_plates(Plate* plates);
Plate* push(Plate* plates, int x);
Plate* remove_plate(Plate* plates);
int pop(Plate** plates);
int len(Plate* plates);
int isnm(char *str);