#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

/* Create functions here */
char *print_working_directory(){
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

int make_directory(char *dir_name){
    int status = mkdir(dir_name, 0755);

    return status; // on success it will return 0 and on failure it will return -1
}