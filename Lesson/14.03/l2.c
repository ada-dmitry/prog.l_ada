#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<error.h>
#define N 5
struct st1{
    int i;
    char s[128];
};
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
    struct st1 *pq=NULL;
    srand(time(NULL));

    if((pq=malloc(N*sizeof(struct st1))) == NULL){
        printf("malloc: NULL\n");
        exit(2);
    }
    st_rand(pq,N);
    st_print(pq,N);
    free(pq);
    pq = NULL;
    return 0;
}