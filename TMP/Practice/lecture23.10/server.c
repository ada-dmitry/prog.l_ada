#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "tpf_unix_sock.server"

int main(void){
 int server_sock, rc;
 socklen_t len;
 int bytes_rec = 0;
 struct sockaddr_un server_sockaddr, peer_sock;
 char buf[256];
 memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);
    
    server_sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_sock == -1){
        perror("socket");
        exit(1);
    }

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);
    rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);
    if (rc == -1){
        perror("bind");
        close(server_sock);
        exit(1);
    }
    

    printf("waiting to recvfrom...\n");
    bytes_rec = recvfrom(server_sock, buf, 256, 0, (struct sockaddr *) &peer_sock, &len);
    if (bytes_rec == -1){
        perror("recv");
        close(server_sock);
        exit(1);
    }
    else {
       printf("DATA RECEIVED = %s\n", buf);
    }
    

    close(server_sock);

    return 0;
}

