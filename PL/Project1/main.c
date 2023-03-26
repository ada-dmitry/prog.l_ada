#include "st_func.h"
#define N 5

int main(int argc, char *argv[]){
    struct st1 q[N];

    st_rand(q,N);
    st_print(q,N);

    return 0;
}