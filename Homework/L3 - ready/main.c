#include "head.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    Unit *n1 = NULL;
    Unit *n2 = NULL;
    Unit *n3 = NULL;
    if ((n1 = malloc(sizeof(Unit))) == NULL ||
        (n2 = malloc(sizeof(Unit))) == NULL ||
        (n3 = malloc(sizeof(Unit))) == NULL)
    {
        printf("Could not malloc\n");
        exit(2);
    }

    int i;
    for (i = 0; i < N; i++)
    {
        char s[LEN];
        int j;

        for (j = 0; j < LEN - 1; j++)
            s[j] = 'a' + rand() % 2;
        s[LEN - 1] = '\0';

        n1 = add_tail(n1, s);

        for (j = 0; j < LEN - 1; j++)
            s[j] = 'a' + rand() % 2;
        s[LEN - 1] = '\0';
        n2 = add_tail(n2, s);
    }

    printf("First array:\n");
    node_print(n1);
    printf("\n");
    printf("Second array:\n");
    node_print(n2);

    n3 = xor_find(n1, n2);

    printf("\nThird array:\n");
    node_print(n3);

    free(n1);
    free(n2);
    free(n3);

    return 0;
}