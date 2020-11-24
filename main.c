#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
  char argument_dir[100];
  if (argc == 2)
  {
    strncpy(argument_dir, argv[1], sizeof(argument_dir) - 1);
  }
  else if (argc == 1)
  {
    printf("Provide a directory name please: ");
    fgets(argument_dir, sizeof(argument_dir), stdin);
  }
  char *newline_pos = strrchr(argument_dir, '\n');
  if (newline_pos)
  {
    *newline_pos = '\0';
  }
  DIR *dir;
  dir = opendir(argument_dir);
  printf("argument_dir: %s\n", argument_dir);
  if (!dir)
  {
    printf("Directory with name [%s] is not available...\n", argument_dir);
    return -1;
  }
  int total_size = 0;
  struct dirent *entry;
  struct stat file;
  entry = readdir(dir);
  char f_name[100];
  strcpy(f_name, argument_dir);
  strcat(f_name, "/");
  printf("Statistics for directory: %s\n", argument_dir);
  while (entry)
  {
    if (entry->d_type == DT_REG)
    {

      strcat(f_name, entry->d_name);
      lstat(f_name, &file);
      total_size += file.st_size;
    }
    entry = readdir(dir);
  }
  printf("Total Directory Size: %d Bytes\n", total_size);
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
