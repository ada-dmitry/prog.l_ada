#include <stdio.h>
#include <stdlib.h>
#include "head.h"

tree *init_root(tree *root, int field)
{
    tree *tmp = malloc(sizeof(tree)); // Выделение памяти под корень дерева
    tmp->field = field;               // Присваивание значения ключу
    tmp->parent = NULL;               // Присваивание указателю на родителя значения NULL
    tmp->left = tmp->right = NULL;    // Присваивание указателю на левое и правое поддерево значения NULL
    root = tmp;
    return root;
}

tree *add_node(tree *root, int field)
{
    tree *root2 = root, *root3 = NULL; // Выделение памяти под узел дерева
    tree *tmp = malloc(sizeof(tree));  // Присваивание значения ключу
    tmp->field = field;
    while (root2 != NULL)
    {
        root3 = root2;
        if (field < root2->field)
            root2 = root2->left;
        else
            root2 = root2->right;
    }
    tmp->parent = root3; // Присваивание указателю на левое и правое поддерево значения NULL
    tmp->left = NULL;
    tmp->right = NULL;
    if (field < root3->field)
        root3->left = tmp;
    else
        root3->right = tmp;
    return root;
}

tree *find_node(tree *root, int field) // Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
{
    if ((root == NULL) || (root->field == field))
        return root; // Поиск нужного узла
    if (field < root->field)
        return find_node(root->left, field);
    else
        return find_node(root->right, field);
}

// Минимальный элемент дерева
tree *minim(tree *root)
{
    tree *lef = root;
    while (lef->left != NULL)
        lef = lef->left;
    return lef;
}

// Максимальный элемент дерева
tree *maxim(tree *root)
{
    tree *rig = root;
    while (rig->right != NULL)
        rig = rig->right;
    return rig;
}

tree *findForDel(tree *root)
{
    tree *rig = root, *lef = NULL; // Если есть правое поддерево, то ищем минимальный элемент в этом поддереве
    if (rig->right != NULL)
        return minim(rig->right);
    lef = rig->parent;
    while ((lef != NULL) && (rig == lef->right))
    {
        rig = lef;
        lef = lef->parent;
    }
    return lef;
}

tree *del_node(tree *root, int field)
{
    if (root == NULL)
        return NULL;
    

    // Поиск удаляемого узла по ключу
    tree *rig = root, *lef = NULL, *tmp = NULL;
    lef = find_node(root, field);

    // 1 случай: у узла нет потомков
    if ((lef->left == NULL) && (lef->right == NULL))
    {
        printf("no children\n");
        if (lef == lef->parent->right)
            lef->parent->right = NULL;
        else
            lef->parent->left = NULL;
        free(lef);
        return root;
    }
    // 2 случай: потомок один - поддерево справа
    if ((lef->left == NULL) && (lef->right != NULL))
    {
        tmp = lef->parent;
        printf("left\n");
        if (lef == tmp->right)
        {
            tmp->right = lef->right;
        }
        else
            tmp->left = lef->right;
        free(lef);
        return tmp;
    }
    // 2 случай: потомок один - поддерево слева
    if ((lef->left != NULL) && (lef->right == NULL))
    {
        printf("right\n");
        tmp = lef->parent;
        if (lef == tmp->right)
            tmp->right = lef->left;
        else
            tmp->left = lef->left;
        free(lef);
        return tmp;
    }
    // 3 случай: оба потомка
    if ((lef->left != NULL) && (lef->right != NULL))
    {
        printf("both\n");
        tmp = findForDel(lef);
        lef->field = tmp->field;
        if (tmp->right == NULL)
            tmp->parent->left = NULL;
        else
            tmp->parent->left = tmp->right;
        free(tmp);
    }
    return root;
}

void preorder(tree *root)
{
    if (root == NULL)
        return;
    if (root->field)
        printf("%d\n", root->field);
    preorder(root->left);
    preorder(root->right);
}

void postorder(tree *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    if (root->field)
        printf("%d ", root->field);
}

void inorder(tree *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    if (root->field)
        printf("%d ", root->field);
    inorder(root->right);
}