#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <poll.h>

#define NUM 4
#define errExit(msg) do { perror(msg); _exit(EXIT_FAILURE); } while (0)
#define errExit1(msg) { perror(msg); _exit(EXIT_FAILURE); }

struct Child {
unsigned char lifetime;
char* message;
};

void child_handler(int sig) {
pid_t pid;
while((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

int main(int argc, char *argv[]) {

struct sigaction new_act, old_act;
sigemptyset (&new_act.sa_mask);
new_act.sa_flags = 0;
new_act.sa_handler = child_handler;

sigaction (SIGCHLD, &new_act, &old_act);

int pipefd[NUM][2];
pid_t cpid[NUM];

int nfds, num_open_fds;
struct pollfd *pfds;
int ready;

unsigned char i,tt;
char buf;
int rr;

struct Child children[NUM];

if (argc != 2) {
fprintf(stderr, "Usage: %s <string>\n", argv[0]);
_exit(EXIT_FAILURE);
}

srand(time(NULL));

num_open_fds = nfds = NUM;
pfds = calloc(nfds, sizeof(struct pollfd));
if (pfds == NULL) errExit("malloc");

for (i=0;i<NUM;i++){
tt=(unsigned char)rand()%9;
dprintf(STDOUT_FILENO,"child %d life time is %X\n",i,tt);

children[i].lifetime = tt;
children[i].message = argv[1];

if (pipe(pipefd[i]) == -1) errExit("pipe");
pfds[i].fd = pipefd[i][0];
pfds[i].events = POLLIN;
if ((cpid[i] = fork()) == -1) errExit("fork");

if (cpid[i] == 0) {
close(pipefd[i][0]);
for (int j=0; j<i; j++){
close(pipefd[j][0]);
close(pipefd[j][1]);
}
write(pipefd[i][1], children + i, sizeof(struct Child));
sleep(tt);
close(pipefd[i][1]);
_exit(EXIT_SUCCESS);
}
}

for (int j=0; j<i; j++) close(pipefd[j][1]);

dprintf(STDOUT_FILENO,"Opened %d pipes, waiting...\n",num_open_fds);

while (num_open_fds > 0) {

do{
dprintf(STDOUT_FILENO,"\ntry poll:\n");
for (i = 0; i < NUM; i++) pfds[i].revents=0;
ready = poll(pfds, nfds, -1);
if(ready == -1)
switch (errno) {
case EINTR: dprintf(STDOUT_FILENO,"\nPoll interrupted, repeat.\n");
continue;
default: errExit("poll");
}
} while (ready <= 0);

for (i = 0; i < NUM; i++) {
if (pfds[i].revents != 0) {
dprintf(STDOUT_FILENO," fd=%d; events: %7s%8s%9s%8s%8s ", pfds[i].fd,
(pfds[i].revents & POLLIN) ? "POLLIN " : "",
(pfds[i].revents & POLLHUP) ? "POLLHUP " : "",
(pfds[i].revents & POLLNVAL) ? "POLLNVAL " : "",
(pfds[i].revents & POLLPRI) ? "POLLPRI " : "",
(pfds[i].revents & POLLERR) ? "POLLERR " : "");
if (pfds[i].revents & POLLIN) {

do {
rr=read(pfds[i].fd, &buf, 1);
if (rr < 0)
switch (errno) {
case EINTR: dprintf(STDOUT_FILENO,"\nRead interrupted, repeat.\n");
continue;
default: errExit("read");
}
if(rr == 0 )
dprintf(STDOUT_FILENO,"\n");
else
dprintf(STDOUT_FILENO,"[%2X]",buf);
} while (rr > 0);

}
else
if ((pfds[i].revents & (POLLHUP | ~POLLIN))) {
dprintf(STDOUT_FILENO,"Closing [%d], pipefd %d, pfds.fd %d\n",i,pipefd[i][0],pfds[i].fd);
if (close(pfds[i].fd) < 0 ) errExit("close pfds");
pfds[i].fd = -1;
pfds[i].events=0;
num_open_fds--;
dprintf(STDOUT_FILENO,"Still opened fds %d\n",num_open_fds);
}
}
}
}

return EXIT_SUCCESS;
}