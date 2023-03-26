#include <stdio.h>
#define N 5
void sort_Select(int x, int *arr){
    int ind, temp = 0;
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
void sort_insert(int l, int *arr){
    int i, j, x;
    for(i=0;i<l;i++){
        j = i-1;
        x = arr[i];
        while((arr[j]>x)&&(j>=0)){
            arr[j+1] = arr[j];
            j--;
        arr[j+1] = x;
        }
    }


}
int main(int argc, char** argv) {
    int l,i;
    //printf("Vvedite razmer massiva: ");
    //scanf("%d", l);
    int arr[N] = {4,5,2,3,1};
    int arra[N] = {3,5,2,4,1};
    sort_Select(N, arr);
    sort_insert(N, arra);
    for(i=0;i<N;i++){
        printf("%d", arr[i]);
    }
    printf("\n");
    for(i=0;i<N;i++){
        printf("%d", arra[i]);
    }
    return 0;
}
