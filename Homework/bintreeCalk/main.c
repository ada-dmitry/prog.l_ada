#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <error.h>
#include "head.h"

int main(int argc, char *argv[])
{
    char s[SIZE];
    Tree *tree = NULL;
    if (argc < 2)
    {
        printf("no expression\n");
        return 2;
    }
    strcpy(s, argv[1]);
    printf("processing %s\n", s);
    tree = maketree(s, 0, strlen(s) - 1);

    printf("\n tree: \n");
    showtree(tree, 0);

    printf("= %d \n", calculate(tree));
    return 0;
}