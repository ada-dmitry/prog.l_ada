#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    struct dirent **namelist;
    int n;
    char dir[255] = ".";

    if (argc > 1)
        strcpy(dir, argv[1]);
    n = scandir(dir, &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        while (n--)
        {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
    return 0;
}