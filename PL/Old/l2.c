#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<error.h>
struct st1{
    int i;
    char s[128];
};
/*
void sort_Select(int x, struct st1 ){
    struct st1 temp;
    int i,j;
    for(i=0;i<(x-1);i++){
        ind = i;
        for(j=i+1;j<x;j++){
            if(arr[ind]>arr[j]){
                ind = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[ind];
        arr[ind] = temp; 
    }
}
*/
void st_rand(struct st1 temp[], int n){
    int k;
    int j;

    
    for(k=0; k<n; k++){
        (temp+k)->i = rand()%100;
        for(j=0;j<127;j++){
            (temp+k)->s[j]=((char)(65+rand()%25));
        }
    (temp+k)->s[127]='\0';
    }
}
/*void swap(struct st1 temp[], int c, int d, int n){
        Дописать функцию!
}
*/
void st_print(struct st1 temp[], int n){
    int k;
    for(k=0;k<n;k++){
        printf("%d->[%2d][%s]\n", k, temp[k].i, (temp+k)->s);
    }
}
int main(int argc, char *argv[]){
    int alenght;
    printf("input n = ");
    scanf("%d", &alenght);
    struct st1 *pq=NULL;
    srand(time(NULL));

    if((pq=malloc(alenght*sizeof(struct st1))) == NULL){
        printf("malloc: NULL\n");
        exit(2);
    }
    st_rand(pq,alenght);
    st_print(pq,alenght);
    free(pq);
    pq = NULL;
    return 0;
}
