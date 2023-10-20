#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define errExit(msg)    do { perror(msg); _exit(EXIT_FAILURE); } while (0)

#define SOCK_PATH  "/tmp/unix_sock.server"
#define DATA "Hello from server"
#define BUF 128
#define FINS "exit_s"
#define FINC "exit_c"

void child_handler(int sig) {
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

void session(int client_sock, struct sockaddr_un server_sockaddr, struct sockaddr_un client_sockaddr){     
 int rc;
 char inbuf[BUF];
 char outbuf[BUF];
 int bytes_rec = 0;
 size_t bs = BUF;
 socklen_t len;
 pid_t ppid, pid;

 ppid=getppid();
 pid=getpid();

   len = sizeof(client_sockaddr);
   rc = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);
   if (rc == -1){
      close(client_sock);
      errExit("getpeer");
   } else {
      printf("[%d] Client socket filepath: %s\n", pid, client_sockaddr.sun_path);
   }
   do { 
     printf("waiting for %s...\n",client_sockaddr.sun_path);
     memset(inbuf, 0, bs);                
     bytes_rec = recv(client_sock, inbuf, bs, 0);
     if (bytes_rec == -1){
        close(client_sock);
        errExit("recv");
     } else {
      printf("[%s]:  %s\n", client_sockaddr.sun_path, inbuf);
     }
    
     memset(outbuf, 0, bs);
     strcpy(outbuf, DATA);      
     printf("Sending data...\n");
     rc = send(client_sock, outbuf, strlen(outbuf)+1, 0);
     if (rc == -1) {
        close(client_sock);
        errExit("send");
     } else {
        printf("Data sent!\n");
     }
     if (strcmp(inbuf,FINS) == 0 ) {kill(ppid,SIGTERM);break;}
   } while (strcmp(inbuf,FINC));
   memset(outbuf, 0, bs);
   sprintf(outbuf,"Exit %d\n",pid);      
   rc = send(client_sock, outbuf, strlen(outbuf)+1, 0);
   if (rc == -1) {
      close(client_sock);
      errExit("send");
   } 
   close(client_sock);
   exit(0);
}

int main(void){

 int server_sock, client_sock, rc;
 socklen_t len;
 struct sockaddr_un server_sockaddr;
 struct sockaddr_un client_sockaddr;     
 int backlog = 10;
 pid_t pid;

 struct sigaction new_act, old_act;
 sigemptyset (&new_act.sa_mask);
 new_act.sa_flags = SA_RESTART;
 new_act.sa_handler = child_handler;
 sigaction (SIGCHLD, &new_act, &old_act);

 len = sizeof(server_sockaddr);
 memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
 memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    
 server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
 if (server_sock == -1) errExit("socket");
    
 server_sockaddr.sun_family = AF_UNIX;   
 strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    
 unlink(SOCK_PATH);
 rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);
 if (rc == -1){
    close(server_sock);
    errExit("bind");
 }
    
 rc = listen(server_sock, backlog);
 if (rc == -1){
    close(server_sock);
    errExit("listen");
 }

 printf("socket listening...\n");

 do {
   client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len);
   if (client_sock == -1){
      close(server_sock);
      close(client_sock);
      errExit("accept");
   }
   if ((pid = fork()) == -1 ) {
      close(server_sock);
      close(client_sock);
      errExit("fork");
   }
   if (pid == 0) session(client_sock,server_sockaddr,client_sockaddr);
   close(client_sock);
 } while (1);
   

 close(server_sock);
 unlink(SOCK_PATH);
    
 return 0;
}
