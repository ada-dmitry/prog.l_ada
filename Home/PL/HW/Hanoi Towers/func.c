#include "head.h"


void linked_print(LinkList* l) {    
    while (l != NULL) {
        printf("%d %s\n", l->x, l->name);
        l = l->next;
    }
}

LinkList* add_tail(LinkList* l, LinkList node) {
    if (l->x == 0 && !strcmp(l->name, "\0")) {
        l->x = node.x;
        memcpy(l->name, node.name, LEN);
        l->next = NULL;
        l->prev = NULL;
        return l;
    }

    LinkList* res = l;
    while (l->next != NULL) l = l->next;

    LinkList* tmp = malloc(sizeof(LinkList));
    tmp->x = node.x;
    memcpy(tmp->name, node.name, LEN);
    tmp->prev = l;
    l->next = tmp;
    return res;
}

LinkList* add_head(LinkList* l, LinkList node) {
    if (l->x == 0 && !strcmp(l->name, "\0")) {
        l->x = node.x;
        memcpy(l->name, node.name, LEN);
        l->next = NULL;
        l->prev = NULL;
        return l;
    }

    LinkList* tmp = malloc(sizeof(LinkList));
    if (tmp == NULL)
        exit(1);
    
    tmp->next = l;
    l->prev = tmp;
    tmp->prev = NULL;
    tmp->x = node.x;
    memcpy(tmp->name, node.name, LEN);
    return tmp;
}

LinkList* del_head(LinkList* l) {
    if (l == NULL) return NULL;
    if (l->next == NULL) {
        free(l);
        return NULL;
    }
    LinkList* tmp = l->next;
    tmp->prev = NULL;
    free(l);
    return tmp;
}

void del_tail(LinkList* l) {
    if (l == NULL) return;
    else if (l->next == NULL) {
        free(l);
        l = NULL;
        return;
    }
    while (l->next != NULL) l = l->next;
    LinkList* tmp = l->prev;
    l->prev = NULL;
    free(l);
    tmp->next = NULL;
}

int len(LinkList* l) {
    int res = 0;
    if (l->x == 0 && !strcmp(l->name, "\0"))
        return 0;
    
    while (l != NULL) {
        res++;
        l = l->next;
    }
    return res;
}

LinkList get(LinkList* l, int n) {
    if (n > len(l)) exit(3);
    int i;
    for (i = 0; i < n; i++) {
        l = l->next;
    }
    return *l;
}

void tower_of_hanoi(int n, LinkList* start, LinkList* finish, LinkList* tmp) {
    if (n == 1) {
        finish = add_head(finish, get(start, 0));
        start = del_head(start);
        return;
    }

    tower_of_hanoi(n - 1, start, tmp, finish);

    finish = add_head(finish, get(start, 0));
    start = del_head(start);

    tower_of_hanoi(n - 1, tmp, finish, start);

    printf("\nPosition:\nStart:\n");
    linked_print(start);
    printf("Finish:\n");
    linked_print(finish);
    printf("Tmp:\n");
    linked_print(tmp);
}

void linked_free(LinkList* l) {
    while (l->next != NULL) l = l->next;

    while (l->prev != NULL) {
        LinkList* tmp = l;
        l = l->prev;
        free(tmp);
    }
}











