#define MPRT 255
#define SIZE 80

typedef struct tree
{
    unsigned char key;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} Tree;
