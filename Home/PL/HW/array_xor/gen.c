#include "header.h"

int main(int argc, char *argv[])
{
    printf("Cto-Nibud\n");
    srand(time(0));
    Node *n1 = NULL;
    Node *n2 = NULL;
    Node *n3 = NULL;

    if ((n1 = malloc(sizeof(Node))) == NULL || (n2 = malloc(sizeof(Node))) == NULL || (n3 = malloc(sizeof(Node))) == NULL)
    {
        printf("could not malloc\n");
        exit(2);
    }
    n1 = add_tail(n1, "bebebe");
    
    printf("Error here 1\n");
    int i;
    for (i = 0; i < COUNT; i++)
    {
        char s[LEN];
        int j;
        printf("sss\n");
        for (j = 0; j < LEN - 1; j++)
            s[j] = 'a' + rand() % 2;
        s[LEN - 1] = '\0';

        n1 = add_tail(n1, s);
        printf("11");
        for (j = 0; j < LEN - 1; j++){
            s[j] = 'a' + rand() % 2;
            printf("22");
        }
        s[LEN - 1] = '\0';
        n2 = add_tail(n2, s);
    }

    printf("Source arrays:\n");
    node_print(n1);
    printf("\n");
    node_print(n2);

    n3 = xor_find(n1, n2);

    printf("\nFinal array:\n");
    node_print(n3);

    free(n1);
    free(n2);
    free(n3);

    return 0;
}