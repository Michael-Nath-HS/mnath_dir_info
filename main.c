// Michael Nath
// Period 10 - Systems Level Programming
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    DIR *dir;
    dir = opendir(".");
    int total_size = 0;
    struct dirent *entry;
    struct stat file;
    entry = readdir(dir);
    char *f_type;
    printf("Statistics for directory: %s\n", entry->d_name);
    while (entry)
    {
        if (entry->d_type == DT_REG)
        {
            stat(entry->d_name, &file);
            total_size += file.st_size;
        }
        entry = readdir(dir);
    }
    printf("Total Diectory Size: %d Bytes\n", total_size);
    rewinddir(dir);
    entry = readdir(dir);
    printf("Directories:\n");
    while (entry)
    {
        if (entry->d_type == DT_DIR)
        {
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(dir);
    }
    rewinddir(dir);
    entry = readdir(dir);
    printf("Files:\n");
    while (entry)
    {
        if (entry->d_type == DT_REG)
        {
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(dir);
    }
    closedir(dir);
}