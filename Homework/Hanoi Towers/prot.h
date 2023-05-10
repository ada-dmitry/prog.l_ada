#define N 10

typedef struct Node
{
    long int data;
    struct Node *next;
    struct Node *prev;
    char s[N];
} tower;

void pr(tower *tmp);
tower *add_head(tower *crown, int hh);
tower *del_head(tower *crown);
int length(tower *list);
tower *sort(tower *crown);
tower *get(tower *list, int n);
void swap(tower *a, tower *b);
tower *adv_add_head(tower *crown, int hh, char string[]);
void hanoi_tower(int n, tower **head_from, tower **head_to, tower **head_aux, tower **const tower1, tower **const tower2, tower **const tower3);
void printftof(tower *head1, tower *head2, tower *head3);
tower *end(tower *crown);
tower *printextra(tower *crown, int len, int i);
int max(int a, int b);