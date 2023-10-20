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

#define SERVER_PATH "/tmp/unix_sock.server"
#define CLIENT_PATH "unix_sock.client"
#define DATA "Hello from client"
#define BUF 128

int main(int argc,char *argv[]){

    int client_sock, rc, len;
    struct sockaddr_un server_sockaddr; 
    struct sockaddr_un client_sockaddr; 
    char buf[BUF];
    size_t bs=BUF;
    char cpath[22];

    srand(time(NULL));
    sprintf(cpath,"%03d-%s",rand()%1000,CLIENT_PATH); 
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
    if (rc == -1){
        perror("bind");
        close(client_sock);
        exit(1);
    }
        
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    rc = connect(client_sock, (struct sockaddr *) &server_sockaddr, len);
    if(rc == -1){
        perror("connect");
        close(client_sock);
        exit(1);
    }
    
    if (argc > 1) 
       strcpy(buf, argv[1]);
    else    
       strcpy(buf, DATA);                 

    printf("Sending data...\n");
    rc = send(client_sock, buf, strlen(buf), 0);
    if (rc == -1) {
        perror("send");
        close(client_sock);
        exit(1);
    }   
    else {
        printf("Data sent!\n");
    }

    printf("Waiting to recieve data...\n");
    memset(buf, 0, sizeof(buf));
    rc = recv(client_sock, buf, bs,0);
    if (rc == -1) {
        perror("recv");
        close(client_sock);
        exit(1);
    }   
    else {
        printf("DATA RECEIVED = %s\n", buf);
    }
    
    close(client_sock);
    unlink(cpath);
    
    return 0;
}
