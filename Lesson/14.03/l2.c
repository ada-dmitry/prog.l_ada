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

    srand(time(NULL));
    for(k=0; k<n; k++){
        (temp+k)->i = rand()%100;
        for(j=0;j<127;j++){
            (temp+k)->s[j]=((char)(65+rand()%25));
        }
    (temp+k)->s[127]='\0';
    }
}

void st_print(struct st1 temp[], int n){
    int k;
    for(k=0;k<n;k++){
        printf("%d->[%2d][%s]\n", k, temp[k].i, (temp+k)->s);
    }
}

int main(int argc, char *argv[]){
    struct st1 q[N];

    st_rand(q,N);
    st_print(q,N);

    return 0;
}