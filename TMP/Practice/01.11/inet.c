#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIN "exit"
#define FINS "exit_s"
#define FINC "exit_c"
#define BUF 1024
#define DATA "Answer"
#define GET "GET"
#define HTTPOK "HTTP/1.1 200 OK\n\n"
#define INDEX "index.html"
// #include "data.h"

void session(int msgsock)
{
    int sock;
    socklen_t length;
    struct sockaddr_in server;
    char ibuf[BUF];
    char obuf[BUF];
    int rval, sval;
    int fd, offt;
    do
    {
        memset(ibuf, 0, BUF);
        if ((rval = read(msgsock, ibuf, 1024)) == -1)
            perror("reading stream message");
        dprintf(1, "-[%d]\n", rval);
        if (rval == 0)
            printf("Connection finished\n");
        else
        {
            dprintf(1, "[%s]\n", ibuf);
            memset(obuf, 0, BUF);
            if (!strncmp(ibuf, GET, 3))
            {
#ifdef INDEX
                strcpy(obuf, HTTPOK);
                offt = strlen(obuf);
                fd = open(INDEX, O_RDONLY);
                read(fd, obuf + offt, BUF - offt);
                close(fd);
#else
                strcpy(obuf, DATA1);
#endif
            }
            else
            {
                strcpy(obuf, DATA);
            }
            sval = send(msgsock, obuf, strlen(obuf), 0);
            dprintf(1, "Sent [%d]\n", sval);
        }
    } while ((rval > 0) && (strncmp(ibuf, GET, 3)));
    exit(0);
}

int main(int argc, char *argv[])
{
    int sock;
    socklen_t length;
    struct sockaddr_in server;
    int msgsock;
    pid_t pid;
    const int enable = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("opening stream socket");
        exit(1);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        exit(2);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (argc == 2)
        server.sin_port = htons(atoi(argv[1]));
    else
        server.sin_port = 0;

    if (bind(sock, (struct sockaddr *)&server, sizeof server) == -1)
    {
        perror("binding stream socket");
        exit(1);
    }

    length = sizeof server;
    if (getsockname(sock, (struct sockaddr *)&server, &length) == -1)
    {
        perror("getting socket name");
        exit(1);
    }
    printf("Socket port %d\n", ntohs(server.sin_port));

    listen(sock, 5);
    pid_t cpid;
    do
    {
        if ((msgsock = accept(sock, (struct sockaddr *)NULL, (socklen_t *)NULL)) == -1)
            perror("accept");
        else
        {
            cpid = fork();
            if (cpid == 0)
            {
                session(msgsock);
            }
        }
        close(msgsock);
    } while (1);
    /*
    do {
       if ((msgsock = accept(sock,(struct sockaddr *) NULL,(socklen_t *) NULL)) == -1)
          perror("accept");
       else
       do {
         memset(ibuf, 0, BUF);
         if ((rval = read(msgsock, ibuf, 1024)) == -1) perror("reading stream message");
         dprintf(1, "-[%d]\n", rval);
         if (rval == 0) printf("Connection finished\n");
         else{
             dprintf(1, "[%s]\n", ibuf);
             memset(obuf, 0, BUF);
             if (!strncmp(ibuf, GET, 3)){
                 strcpy(obuf, DATA1);
             }else{
                 strcpy(obuf, DATA);
             }
             sval = send(msgsock, obuf, strlen(obuf), 0);
             dprintf(1, "Sent [%d]\n", sval);
         }
       } while ((rval > 0) && (strncmp(ibuf, GET, 3)));
     close(msgsock);
    } while (strcmp(ibuf, FIN))
    */
    exit(0);
}
