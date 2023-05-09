typedef struct tnode { 
    int field;
    struct tnode *left;
    struct tnode *right;
    struct tnode *parent;
} tree;

tree *init_root(tree *root, int field);
tree *add_node(tree *root, int field);
tree *find_node(tree * root, int field);
tree *minim(tree *root);
tree *maxim(tree *root);
tree *findForDel(tree *root);
tree *del_node(tree *root, int field);
void print_tree(tree *root);