#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#define N 10
#define n 100

void init_matr(int c, short int mat[c][c]);
void out_matr(int c, short int mat[c][c]);
void trans(int c, short int mat[c][c]);