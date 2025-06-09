#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "utils.h"

/* Create functions here */
char *print_working_directory()
{
    // print the current working directory
    char *current = getcwd(NULL, 0);

    if (current != NULL)
    {
        return current;
    }
    else
    {
        return "Failed to get current directory";
    }
    
}

int make_directory(char *dir_name)
{
    int status = mkdir(dir_name, 0755);

    return status; // on success it will return 0 and on failure it will return -1
}

void print_files_and_sub_directories(char *path)
{
    DIR *dir;
    struct dirent *d;

    dir = opendir(path); // open the directory path

    if (dir)
    {
        while ((d = readdir(dir)) != NULL)
        {
            printf("%s\n", d->d_name);
        }
        
        closedir(dir);
    }
    else
    {
        perror("Unable to open the directory...\n");
    }
    
}

void change_directory(char *dir)
{
    

    if (chdir(dir) == 0)
    {
        char new_dir[512];

        if (getcwd(new_dir, sizeof(new_dir)) != NULL)
        {
            printf("You are at: %s\n", new_dir);
        }
        else
        {
            printf("failed to change directory to %s\n", dir);
        }

    }
    
}