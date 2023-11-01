#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    if (argc > 1)
        dir = opendir(argv[1]);
    else
        dir = opendir("/");
    if (!dir)
    {
        perror("diropen");
        return 1;
    };
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%d - %s [%d] %d\n",
               entry->d_ino, entry->d_name, entry->d_type,
               entry->d_reclen);
    };
    closedir(dir);
    return 0;
}