#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void pr(node *tmp){
    int i;
    if(tmp == NULL){printf("[%p]\n", tmp); return;}
    while(tmp){
        printf("[%14p]<-[%14p]->[%14p]   ", tmp->prev, tmp, tmp->next);
        printf("data: [%4ld] s[" , tmp->data);
        for(i=0;i<COUN; i++) printf("%c", tmp->s[i]);
        printf("]\n");
        tmp = tmp->next;
    }
    printf("---------------------\n");
}

node *add_head(node *head, int hh){
    node *tmp=NULL;
    int i;
    if((tmp=malloc(sizeof(node)))==NULL){
        perror("malloc: NULL");
        exit(2);
    }
    tmp->prev=NULL;
    tmp->data=hh;
    for(i=0;i<COUN;i++) tmp->s[i]=((char)(65+rand()%25));
    if(head==NULL) tmp->next=NULL;
    else{
        tmp->next=head;
        head->prev=tmp;
    }
    return tmp;
}

node *add_tail(node *head, int hh){
    node *tmp=NULL;
    node *t = NULL;
    int i;
    if((tmp=malloc(sizeof(node)))==NULL){
        perror("malloc: NULL");
        exit(3);
    }

    tmp->data=hh;
    for(i=0;i<COUN;i++) tmp->s[i]=((char)(65+rand()%25));
    tmp->next=NULL;
    if(head==NULL) tmp->prev=NULL;
    else{
        t = head;
        while(t->next!=NULL) t = t->next;
        t->next=tmp;
        tmp->prev=head;
    }
    return head;
}

node *del_head(node *head){
    node *tmp = head;
    if(head==NULL) return NULL;
    if(head -> next == NULL){
        free(head);
        return NULL;
    }
    head = head->next;
    head -> prev = NULL;
    free(tmp);
    return head;
}

node *del_tail(node *list){
    node *tail = NULL;
    if(list==NULL) return NULL;
    if(list -> next == NULL){
        free(list);
        return NULL;
    }
    tail = list;
    while(tail->next->next) tail = tail->next;
    free(tail->next);
    tail -> next=NULL;
    return list;
}