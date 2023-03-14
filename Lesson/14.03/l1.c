#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int a[], int c, int d, int n){
    int temp;
    if((c>=n) || (d>=n)) return;
    temp = a[c];
    a[c] = a[d];
    a[d] = temp;
}

void pa(int a[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("a[%d] = %2d ", i, a[i]);
    }
    printf("\n");
}

void init(int *a, int n){
    srand(time(NULL));
    while(n--){
        *(a++)=rand()%100;
    }
}

int main2(int n){
    int a[n];

    init(a,n);
    pa(a,n);
    swap(a,1,4,n);
    pa(a,n);
    return 0;
}

int main(){
    int alenght;
    printf("input n = ");
    scanf("%d", &alenght);
    return main2(alenght);
}