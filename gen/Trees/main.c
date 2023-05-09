#include <stdio.h>
#include <stdio.h>
#include "head.h"

int main(int argc, char *argv[]){
    tree *root=NULL;
    root = init_root(root, 65);
    print_tree(root);
    printf("\n");
    root=del_node(root, 65);
    print_tree(root);
    printf("\n");
    root = add_node(root, 70);
    root = add_node(root, 66);
    root = add_node(root, 68);
    root = add_node(root, 71);
    root = add_node(root, 67);
    root = add_node(root, 72);
    print_tree(root);
    printf("\n");
    root = del_node(root, 66);
    print_tree(root);
    printf("\n");
    return 0;
}