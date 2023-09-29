
#include "func.h"

int main(int argc, char *argv[])
{
    int pipefd[n][2], fd_ans;
    caddr_t addr_ans;
    pid_t cpid[n];
    short mat1[n][n], mat2[n][n];
    fd_ans = open(argv[2], O_RDWR | O_CREAT);
    srand(time(NULL));
    init_matr(n, mat1);
    init_matr(n, mat2);
    out_matr(n, mat1);
    trans(n, mat2);
    printf("\n");
    out_matr(n, mat2);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        cpid[i] = fork();
        if (cpid[i] == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid[i] == 0)
        {
            int result[n];
            close(pipefd[i][0]);
            for (int j = 0; j < i; j++)
            {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }
            for (int j = 0; j < n; j++)
            {
                int sum = 0;
                for (int k = 0; k < n; k++)
                {
                    sum += mat1[i][k] * mat2[j][k];
                }
                result[j] = sum;
            }
            write(pipefd[i][1], result, n * sizeof(int));
            close(pipefd[i][1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pipefd[i][1]);
        }
    }

    printf("Resulting mat\n");
    for (int i = 0; i < n; i++)
    {
        waitpid(cpid[i], NULL, WNOHANG);
        int result[n];
        read(pipefd[i][0], result, n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
           //printf("[%d] ", result[j]);
            addr_ans = mmap((caddr_t)0, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);

        }
        printf("\n");
        close(pipefd[i][0]);
    }
    exit(EXIT_SUCCESS);
}
