       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>
       #include <unistd.h>

       static void
       usage(const char *pname)
       {
           fprintf(stderr, "Usage: %s [-cx] pathname proj-id num-sems\n",
                   pname);
           fprintf(stderr, "    -c           Use IPC_CREAT flag\n");
           fprintf(stderr, "    -x           Use IPC_EXCL flag\n");
           exit(EXIT_FAILURE);
       }

       int
       main(int argc, char *argv[])
       {
           int    semid, nsems, flags, opt;
           key_t  key;

           flags = 0;
           while ((opt = getopt(argc, argv, "cx")) != -1) {
               switch (opt) {
               case 'c': flags |= IPC_CREAT;   break;
               case 'x': flags |= IPC_EXCL;    break;
               default:  usage(argv[0]);
               }
           }

           if (argc != optind + 3)
               usage(argv[0]);

           key = ftok(argv[optind], argv[optind + 1][0]);
           if (key == -1) {
               perror("ftok");
               exit(EXIT_FAILURE);
           }

           nsems = atoi(argv[optind + 2]);

           semid = semget(key, nsems, flags | 0600);
           if (semid == -1) {
               perror("semget");
               exit(EXIT_FAILURE);
           }

           printf("ID = %d\n", semid);

           exit(EXIT_SUCCESS);
       }
