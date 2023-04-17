#include "head.h"

void print_plates(Plate *plates)
{
    if (plates == NULL)
    {
        printf("[%p]\n", plates);
        return;
    }
    while(plates){
        printf("[%14p]->[%14p] ", plates, plates->next);
        printf("data: [%4d]\n", plates->x);
        plates = plates->next;
    }
    printf("-------------\n");
}

Plate* push(Plate* plates, int d){
    Plate *temp = NULL;
    if((temp=malloc(sizeof(Plate)))==NULL){
        perror("malloc:NULL");
        exit(2);
    }
    temp->x = d;
    if(plates==NULL) temp->next=NULL;
    else{
        temp->next=plates;
    } 
    return temp;
}

Plate* del_head(Plate* plates){
    Plate *temp=plates;
    if(plates==NULL) return NULL;
    if(plates->next==NULL){
        free(plates);
        return NULL;
    }
    plates = plates->next;
    free(temp);
    return plates;
}

int len(Plate* plates){
    int ans = 0;
    Plate *temp = plates;
    if(plates==NULL) return 0;
    while(temp){
        ans++;
        temp=temp->next;
    }
    return ans;
}

int pop(Plate** plates){
    int i;
    if(*plates==NULL){
        printf("Error");
        exit(4);
    }
    i = (*plates)->x;
    *plates = del_head(*plates);
    return i;
}

int isnm(char *str){
    int i = 0, n = strlen(str);
    for(i=0; i<n; i++){
        if(!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}