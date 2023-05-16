#define N 5

typedef struct Stack
{
  double x;
  struct Stack *next;
} Stack;

void linked_print(Stack *l);
Stack *add_head(Stack *l, double x);
Stack *del_head(Stack *l);
int len(Stack *l);
Stack get(Stack *l, int n);