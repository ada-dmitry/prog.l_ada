#define COUN 40


typedef struct Node {
    long int data;
    struct Node *next;
    struct Node *prev;
    char s[COUN];
} node;

void pr(node *tmp);
node *add_head(node *head, int hh);
node *add_tail(node *head, int hh);
node *del_head(node *head);
node *del_tail(node *list);
// node *sort(node *head);
// int lenghth(node *list);
// void writefile(const char *path, node *head);
// node *readfile(const char *path);
