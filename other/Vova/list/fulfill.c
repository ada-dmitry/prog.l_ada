#include "head.h"

int main(int argc, char *argv[])
{
    printf("Hello! Let's begin\n");
    srand(time(0));
    Node *n1 = NULL;
    Node *n2 = NULL;
    Node *n3 = NULL;

    if ((n1 = malloc(sizeof(Node))) == NULL || (n2 = malloc(sizeof(Node))) == NULL || (n3 = malloc(sizeof(Node))) == NULL)
    {
        printf("No memory for you\n");
        exit(2);
    }
    n1 = add_tail(n1, "tail");

    printf("First error\n");

    int i;
    for (i = 0; i < CO; i++)
    {
        char s[LEN];
        int m;
        printf("Let it be\n");
        for (m = 0; m < LEN - 1; m++)
            s[m] = 'V' + rand() % 2;
        s[LEN - 1] = '\0';

        n1 = add_tail(n1, s);
        printf("10");
        for (m = 0; m < LEN - 1; m++)
        {
            s[m] = 'V' + rand() % 2;
            printf("20");
        }
        s[LEN - 1] = '\0';
        n2 = add_tail(n2, s);
    }

    printf("Initial arrays:\n");
    node_print(n1);
    printf("\n");
    node_print(n2);

    n3 = find_0(n1, n2);

    printf("\n");

    printf("Final version:\n");
    node_print(n3);

    free(n1);
    free(n2);
    free(n3);

    printf("That's all for now\n");

    return 0;
}