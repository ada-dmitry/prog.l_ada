#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <windows.h>

int main(int args, char *argv[])
{
    node *head = NULL;
    int r;
    srand(time(NULL));

    while ((r = (rand() % 100)) < 90)
        head = add_head(head, r);
    pr(head);
    head = del_head(head);
    pr(head);

    head = add_tail(head, 5);
    pr(head);

    head = del_tail(head);
    pr(head);
}
// Домашка: сортировка списка и вычисление длины списка(по желанию запись в файл и чтение с файла)
// Ханойские башни игра написать