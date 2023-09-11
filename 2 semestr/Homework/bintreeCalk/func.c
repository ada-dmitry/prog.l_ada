#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <error.h>
#include "head.h"

Tree *tnew(void)
{
    Tree *tmp;
    if ((tmp = malloc(sizeof(Tree))) == NULL)
    {
        perror("malloc:");
        exit(1);
    }
    tmp->key = 0;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

Tree *leaf(char c)
{
    Tree *tmp;
    tmp = tnew();
    tmp->key = c;
    return tmp;
}

Tree *maketree(char expr[], int first, int last)
{
    Tree *root;
    int k;

    if (first == last)
    {
        return leaf(expr[first]);
    }

    k = lastop(expr, first, last);
    root = tnew();
    root->key = expr[k];
    root->left = maketree(expr, first, k - 1);
    root->right = maketree(expr, k + 1, last);
    return root;
}

unsigned char priority(char c)
{
    if ((c - '0' >= 0) && (c - '0' <= 9))
    {
        return MPRT;
    }
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return c;
}

int lastop(char expr[], int first, int last)
{
    unsigned char min, prt;
    int i, k;
    min = MPRT;
    for (i = first; i <= last; i++)
    {
        prt = priority(expr[i]);
        if (prt <= min)
        {
            min = prt;
            k = i;
        }
    }
    return k;
}

int calculate(Tree *root)
{
    int num1, num2;
    if (!(root->left))
    {
        return root->key - 0x30;
    }
    num1 = calculate(root->left);
    num2 = calculate(root->right);
    switch (root->key)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    case '^':
        return pow(num1, num2);
    }
    return 0xffffffff;
}

void showtree(Tree *root, int level)
{
    if ((root->key > 31) && (root->key < 127))
    {
        printf("%c ", root->key);
    }
    else
    {
        printf("%X ", root->key);
    }

    if (root->right)
    {
        printf("------> ");
        level++;
        showtree(root->right, level);
        level--;
    }
    if (root->left)
    {
        int i = 0;

        printf("\n");
        for (i = 0; i < level; i++)
        {
            printf("          ");
        }
        printf("| \n");

        for (i = 0; i < level; i++)
        {
            printf("          ");
        }
        showtree(root->left, level);
    }
}

Tree *create(unsigned char key)
{
    Tree *tmp;
    if ((tmp = malloc(sizeof(Tree))) == NULL)
    {
        perror("malloc:");
        exit(1);
    }
    tmp->key = key;
    tmp->parent = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

Tree *add(Tree *root, unsigned char key)
{
    Tree *rtmp = root, *rsave = NULL, *tmp;
    if ((tmp = malloc(sizeof(Tree))) == NULL)
    {
        perror("malloc:");
        exit(1);
    }
    while (rtmp)
    {
        rsave = rtmp;
        if (key < rtmp->key)
        {
            rtmp = rtmp->left;
        }
        else if (key > rtmp->key)
        {
            rtmp = rtmp->right;
        }
        else
        {
            printf("\n There is element %c \n", key);
            return root;
        }
    }
    tmp->parent = rsave;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->key = key;
    if (key < rsave->key)
    {
        rsave->left = tmp;
    }
    else
    {
        rsave->right = tmp;
    }
    return root;
}

Tree *search(Tree *root, unsigned char key)
{
    if ((root == NULL) || (root->key == key))
    {
        return root;
    }
    if (key < root->key)
    {
        return search(root->left, key);
    }
    else if (key > root->key)
    {
        return search(root->right, key);
    }
}

Tree *min(Tree *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
Tree *max(Tree *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

Tree *nextdel(Tree *root)
{
    Tree *l = NULL;
    if (root->right != NULL)
    {
        return min(root->right);
    }
    l = root->parent;
    while ((l != NULL) && (root == l->right))
    {
        root = l;
        l = l->parent;
    }
    return l;
}

void delete(Tree *del)
{
    Tree *tmp;
    if (del == NULL)
    {
        printf("\n no such elem \n");
        return;
    }
    if ((del->left == NULL) && (del->right == NULL))
    {
        if (del == del->parent->right)
        {
            del->parent->right = NULL;
        }
        else
        {
            del->parent->right = NULL;
        }
        free(del);
        return;
    }

    if ((del->left == NULL) && (del->right != NULL))
    {
        if (del == del->parent->right)
        {
            del->parent->right = del->right;
            del->parent->right->parent = del->parent;
        }
        else
        {
            del->parent->left = del->right;
            del->parent->left->parent = del->parent;
        }
        free(del);
        return;
    }

    if ((del->left != NULL) && (del->right == NULL))
    {
        if (del == del->parent->right)
        {
            del->parent->right = del->left;
            del->parent->right->parent = del->parent;
        }
        else
        {
            del->parent->left = del->left;
            del->parent->left->parent = del->parent;
        }
        free(del);
        return;
    }

    if ((del->left != NULL) && (del->right != NULL))
    {
        tmp = min(del->right);
        del->key = tmp->key;
        delete (tmp);
    }
}
