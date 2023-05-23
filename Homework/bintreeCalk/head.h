#define MPRT 255
#define SIZE 80

typedef struct tree
{
    unsigned char key;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} Tree;

Tree *tnew(void);
Tree *leaf(char c);
Tree *maketree(char expr[], int first, int last);
unsigned char priority(char c);
int lastop(char expr[], int first, int last);
int calculate(Tree *root);
void showtree(Tree *root, int level);
Tree *create(unsigned char key);
Tree *add(Tree *root, unsigned char key);
Tree *search(Tree *root, unsigned char key);
Tree *min(Tree *root);
Tree *max(Tree *root);
Tree *nextdel(Tree *root);
void delete(Tree *del);
