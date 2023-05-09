#define COUN 4
#define LEN 8

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

typedef struct People
{
    int count;
    char name[LEN];
} People;

void print_struc(People professions[], int n);
void sort_sel(People professions[], int n);
void st_rand(People professions[], int n);
People *binSearch(People professions[], int n, int k);
void pst(People professions[], int s, int n);
int find_para(People t1[], int n1, People t2[], int n2);
void st_fprintf(People professions[], int n, char path[], char access[]);
int lines_numf(char path[]);
void st_fscanf(People t[], int n, char path[]);
void swap(People *t1, People *t2);