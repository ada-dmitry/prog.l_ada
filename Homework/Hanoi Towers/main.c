#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{

    tower *crown1 = NULL, *crown2 = NULL, *crown3 = NULL;
    int r;

    srand(time(NULL));

    printf("Generated linked list (method of crown1)\n");
    while ((r = (rand() % 100)) < 75)
        crown1 = add_head(crown1, r);
    pr(crown1);

    printf("Length of linked list is: %d\n", length(crown1));

    printf("Sorted linked list\n");
    sort(crown1);
    pr(crown1);

    hanoi_tower(length(crown1), &crown1, &crown3, &crown2, &crown1, &crown2, &crown3);
    return 0;
}