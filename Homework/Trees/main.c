#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Дерево улетает в SF
int main(int argc, char *argv[])
{
    tree *root = NULL;
    root = init_root(root, 'A');
    // preorder(root);
    root = del_node(root, 'A');
    exit(0);
    // preorder(root);
    printf("\n");
    root = add_node(root, 'F');
    root = add_node(root, 'B');
    root = add_node(root, 'D');
    root = add_node(root, 'G');
    root = add_node(root, 'C');
    root = add_node(root, 'H');
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    root = del_node(root, 'B');
    preorder(root);
    printf("\n");
    return 0;
}