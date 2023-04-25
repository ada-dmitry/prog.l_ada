#include "head.h"


int main(int argc, char* argv[]) {
    srand(time(0));
    LinkList* l1 = malloc(sizeof(LinkList));
    LinkList* l2 = malloc(sizeof(LinkList));
    LinkList* l3 = malloc(sizeof(LinkList));

    if (l1 == NULL || l2 == NULL || l3 == NULL)
        exit(1);

    int i, j;
    char s[LEN];
    for (i = 0; i < N; i++) {        
        for (j = 0; j < LEN - 1; j++)
            s[j] = 'a' + rand() % 25;
        s[j + 1] = '\0';
        
        LinkList l;
        l.x = i;
        memcpy(l.name, s, LEN);
        l.next = NULL;
        l.prev = NULL;

        l1 = add_tail(l1, l);
    }

    tower_of_hanoi(N, l1, l3, l2);

    // printf("Done:\n");

    linked_free(l1);
    linked_free(l2);
    linked_free(l3);

    return 0;
}