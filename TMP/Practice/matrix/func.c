
#include "func.h"

void init_matr(int c, short int mat[c][c])
{
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mat[i][j] = rand() % N;
        }
    }
}
void out_matr(int c, short int mat[c][c])
{
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("[%d] ", mat[i][j]);
        }
        printf("\n");
    }
}

void trans(int c, short int mat[c][c])
{
    for (int i = 0; i < c; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            short c;
            c = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = c;
        }
    }
}
