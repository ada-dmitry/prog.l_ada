#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>

#define errExit(msg)       do { perror(msg); _exit(EXIT_FAILURE); } while (0)
#define SerrExit(s,msg)    do { close(s); perror(msg); _exit(EXIT_FAILURE); } while (0)

#define SERVER_PATH "/tmp/unix_sock.server"
#define CLIENT_PATH "unix_sock.client"
#define DATA "Hello from client"
#define BUF 128
#define FINS "exit_s"
#define FINC "exit_c"
//#define INFO 

int rcvBuffer(int sock_fd){
      int rcvBufferSize;
      socklen_t sockOptSize = sizeof(rcvBufferSize);
      getsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, &sockOptSize);
#ifdef INFO
      printf("initial socket receive buf %d\n", rcvBufferSize);
#endif
      return rcvBufferSize;
}

int recvCount(const void *s, int size){
   register int count;
   register int mark;
   register char *p;
   p=(char *)s;
   count = 0;
   mark = 0;
   do {
     if (*p && !(*(p+1))) count++;
#ifdef INFO
     printf("[%c][%X]\n",*p,*p);
#endif
     p++;
     mark++;
   } while (!((*p == '\0') && (*(p+1)=='\0')) && (mark < size));
   return count;
}

int main(int argc,char *argv[]){

    int client_sock, rc, len;
    struct sockaddr_un server_sockaddr; 
    struct sockaddr_un client_sockaddr; 
    char obuf[BUF];
    char **ibuf;
    size_t obs=BUF,ibs;
    char cpath[22];

    sprintf(cpath,"%d-%s",getpid(),CLIENT_PATH); 
    len = sizeof(client_sockaddr);
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
     
    client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_sock == -1) {
        perror("socket");
        exit(1);
    }


    client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, cpath); 
    
    unlink(cpath);
    rc = bind(client_sock, (struct sockaddr *) &client_sockaddr, len);
    if (rc == -1) SerrExit(client_sock,"bind");

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    rc = connect(client_sock, (struct sockaddr *) &server_sockaddr, len);
    if (rc == -1) SerrExit(client_sock,"connect");
    
    ibs=rcvBuffer(client_sock);
    if ((ibuf=(char **)malloc(ibs)) == NULL ) errExit("malloc");

    do {
      memset(obuf, 0, obs);
       printf("> ");
      scanf("%s",obuf);

      printf("Sending data...\n");
      rc = send(client_sock, obuf, strlen(obuf)+1, 0);
      if (rc == -1) {
         perror("send");
         close(client_sock);
         exit(1);
      } else {
        printf("Data sent!\n");
      }

      printf("Waiting to recieve data...\n");
      memset(ibuf, 0, ibs);
      rc = recv(client_sock, ibuf, ibs,0);
      if (rc == -1) {
         perror("recv");
         close(client_sock);
         exit(1);
      } else {
        int c = recvCount(ibuf,ibs);
#ifdef INFO
        char *p = (char *)ibuf;
        printf("count: %d resieved\n",c);
        for (int i = 0; i < 32; i++){
           printf("[%c][%X]",*p,*p);
           p++;
        }
        printf("\n");
#endif
#ifndef INFO
        char p[obs];
        char *tp = (char *)ibuf;
//        if ((ibuf=(char **)malloc(ibs)) == NULL ) errExit("malloc");
        for (int i = 0; i < c; i++){
           memset(p,0,obs);
           while (*tp) {strncat(p,tp,1);tp++;}
           tp++;
//           printf("DATA RECEIVED [%ld] = %s\n", strlen(ibuf[i]),ibuf[i]);
           printf("DATA RECEIVED [%ld] = %s\n", strlen(p),p);
//           printf("DATA RECEIVED [%ld] = %s\n", strlen(p[i]),p[i]);
        }
#endif
      }
      
    } while (strcmp(obuf,FINC) && strcmp(obuf,FINS));

    close(client_sock);
    unlink(cpath);
    
    return 0;
}
