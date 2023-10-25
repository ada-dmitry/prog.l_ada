#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//./client_app stud*** "port"

#define DATA "Hello, World!"

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in server;
  struct hostent *hp;
  char buf[1024];

  if (argc < 3)
  {
    printf("c_inet hostname port [data]\n");
    _exit(1);
  }

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("opening stream socket");
    exit(1);
  }

  hp = malloc(sizeof(struct hostent));

  server.sin_family = AF_INET;
  hp = gethostbyname(argv[1]);
  if (hp == (struct hostent *)0)
  {
    fprintf(stderr, "%s: unknown host\n", argv[1]);
    exit(2);
  }
  memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  if (connect(sock, (struct sockaddr *)&server, sizeof server) == -1)
  {
    perror("connecting stream socket");
    exit(1);
  }
  getchar();
  memset(buf, 0, 1024);
  if (argc > 3)
  {
    printf("[%s]\n", argv[3]);
    strcpy(buf, argv[3]);
  }
  else
  {
    strcpy(buf, DATA);
  }
  if (write(sock, buf, strlen(buf)) == -1)
    perror("writing on stream socket");
  close(sock);
  exit(0);
}
