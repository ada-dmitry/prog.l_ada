#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#define NUM 4

int main(int argc, char *argv[]){
    int pipefd[4][2];
    pid_t cpid[4];
    unsigned char i, tt;
    char buf;
    int rr, wt;

if (argc != 2){
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
}

srand(time(NULL));

for(i = 0; i < NUM; i++){
    if (pipe(pipefd[i]) == -1){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }
    tt = (unsigned char)rand()%8;
    dprintf(STDOUT_FILENO, "Time[%X]\n", tt);

    cpid[i] = fork();
    if (cpid[i] == -1){
        perror("Fork");
        exit(EXIT_FAILURE);
    }

    if (cpid[i] == 0){
        close(pipefd[i][0]);
        write(pipefd[i][1], argv[1], strlen(argv[1]));
        write(pipefd[i][1], &i, 1);
        write(pipefd[i][1], &tt, 1);
        close(pipefd[i][1]);
        sleep(tt);
        _exit(EXIT_FAILURE);
    } else {
        close(pipefd[i][1]);
    }
}

printf("Waiting...\n");

while((wt = waitpid(-1, NULL, WNOHANG)) > -1){
    if (wt > 0) for(i = 0; i < NUM; i++){
        if (cpid[i] == wt){
            while((rr = read(pipefd[i][0], &buf, 1)) > 0){
                write(STDOUT_FILENO, &buf, 1);
                dprintf(STDOUT_FILENO, "[%X]", buf);
            }
            if (rr == 0){
                write(STDOUT_FILENO, "\n", 1);
                close(pipefd[i][0]);
            }
        }
    }
}
if (errno == ECHILD)
    perror("Finish:");
else
    perror("Wait error:");
    exit(EXIT_SUCCESS);
}