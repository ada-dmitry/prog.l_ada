#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define DATA "exit"

int main(int argc, char *argv[]){
    int sock;
    socklen_t length;
    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    int rval;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("opening stream socket");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htoml(INADDR_ANY;
    if(argc == 2){
        server.sin_port = htons(atoi(argv[1]));
    }
    else{
        server.sin_port = 0;
    }
    if(bind(sock, (struct sockaddr *) &server, sizeof server) == -1){
        perror("binding stream socket");
        exit(1);
    }
    length = sizeof server;
    if(getsockname(sock,(struct sockaddr *) &server, &length) == -1){
        perror("getting socket name");
        exit(1);
    }
    printf("socket port %d\n", ntohs(server.sin_port));
    listen(sock, 5);
    do{
        if((msgsock = accept(sock,(struct sockaddr *) NULL, (socklen_t *) NULL)) == -1){
            perror("accept");
        }
        else
            do{
                memset(buf,0,sizeof buf);
                if((rval = read(msgsock, buf, 1024)) == -1)
                    perror("reading stream message");
                dprintf(1, "-[%d]\n", rval);
                if(rval == 0){
                    printf("connecting finished\n");
                }
                else{
                    dprintf(1,"[%s]\n", buf);
                }
            }while((rval > 0) && (strcmp(buf,FIN)));
            close(msgsock);

    }while(strcmp(buf,FIN));
    exit(0);
}
