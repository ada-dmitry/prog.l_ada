#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#define DATA 20
#define NUM 4

struct Data {
    char s[DATA + 1];
    pid_t cpid;
    unsigned char i, t;
};

int main(int argc, char *argv[]){
    int pipefd[4][2];
    pid_t cpid[4];
    unsigned char i, tt;
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
        struct Data data;
        close(pipefd[i][0]);
        for(int j = 0; j < i; j++){
            close(pipefd[j][0]);
            close(pipefd[j][1]);
        }
        data.cpid = getpid();
        data.i = i;
        data.t = tt;
        strncpy(data.s, argv[1], DATA);
        write(pipefd[i][1], &data, sizeof(struct Data));
        close(pipefd[i][1]);
        sleep(tt);
        _exit(EXIT_FAILURE);
    } else {
        dprintf(STDOUT_FILENO, "Start [%d]\n", cpid[i]);
        close(pipefd[i][1]);
    }
}

printf("Waiting...\n");

while((wt = waitpid(-1, NULL, WNOHANG)) > -1){
    if (wt > 0) for(i = 0; i < NUM; i++){
        if (cpid[i] == wt){
            struct Data data;
            while((rr = read(pipefd[i][0], &data, sizeof(struct Data))) > 0){
                dprintf(STDOUT_FILENO, "[%d] num = %d, time = %d [%s]\n", data.cpid, data.i, data.t, data.s);
            }
            if (rr == 0) close(pipefd[i][0]);
        }
    }
    usleep(3000000);
}
if (errno == ECHILD)
    perror("Finish:");
else
    perror("Wait error:");
    exit(EXIT_SUCCESS);
}