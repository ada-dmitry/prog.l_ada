#include "funcHeader.h"

void print_struc(People professions[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("count: %3d; name: %s\n", professions[i].count, professions[i].name);
}

void sort_sel(People professions[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (professions[j].count < professions[i].count)
                swap(professions + i, professions + j);
        }
    }
}

void st_rand(People professions[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        professions[i].count = rand() % 3 + 1;
        for (j = 0; j < LEN - 1; j++)
            professions[i].name[j] = 'a' + rand() % 25;
        professions[i].name[j + 1] = '\0';
    }
}

People* binSearch(People professions[], int n, int k) {
    People* ans = NULL;
    int right = 0, left = n - 1;
    
    while (right <= left) {
        int mid = (left + right) / 2;

        if (professions[mid].count == k) {
            ans = &professions[mid];
            break;
        }
        right = (professions[mid].count < k) ? mid + 1: right;
        left = (professions[mid].count > k) ? mid - 1: left;
    }
    return ans;
}

void pst(People professions[], int s, int n) {
    if (n >= s) {
        printf("Out of range\n");
        exit(2);
    }
    
    printf("count: %2d; name: %s\n", professions[n].count, professions[n].name);
}


int find_para(People t1[], int n1, People t2[], int n2) {
    int ans = 0, i;
    for (i = 0; i < n1; i++) {
        People* tans = binSearch(t2, n2, t1[i].count);
        if (tans == NULL) continue;
        ans++;
    }
    return ans;
}


void st_fprintf(People professions[], int n, char path[], char access[]) {
    int i;
    FILE* f = fopen(path, access);
    if (f == NULL) {
        printf("Could not open file %s\n", path);
        exit(3);
    }

    for (i = 0; i < n; i++) {
        fprintf(f, "%d %s\n", professions[i].count, professions[i].name);
    }

    fclose(f);
}

int lines_numf(char path[]) {
    int ans = 0;
    char c;
    FILE* f = fopen(path, "r"); 
    if (f == NULL) {
        printf("Faila %s net...\n", path);
        exit(3);
    }

    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') ans++;
    }

    fclose(f);
    return ans;
}

void st_fscanf(People t[], int n, char path[]) {
    int i;
    FILE* f = fopen(path, "r"); 
    if (f == NULL) {
        printf("Faila %s net...\n", path);
        exit(3);
    }

    for (i = 0; i < n; i++) {
        fscanf(f, "%d %s\n", &t[i].count, t[i].name);
    }
    fclose(f);
}

void swap(People* t1, People* t2) {
    People* tmp = malloc(sizeof(People));

    if (tmp == NULL) {
        printf("could not malloc\n");
        exit(1);
    }

    memcpy(tmp, t1, sizeof(People));
    memcpy(t1, t2, sizeof(People));
    memcpy(t2, tmp, sizeof(People));
    free(tmp);
}
