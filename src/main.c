#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int main(){
    
    char *input = (char*) malloc(512 * sizeof(char)); // user input on the shell
    FILE *file_ptr ;


    if (input == NULL)
    {
        perror("Unable to allocate memory!\n");
        return 1;
    }
    

    while (1)
    {
        /* store the user input and check  */
        printf(" ~ $ ");
        if (fgets(input, 510, stdin) == NULL)
        {
            break;
        }
        
        /* Removing Trailing \n */
        input[strcspn(input, "\n")] = 0;
        
        /* Tokenize the input with ' ' and check which command is used, any other command is being inputed then "Command not found..." */
        char *command = strtok(input, " ");
        char *parameter = strtok(NULL, " ");
        
        // printf("%s\n", parameter);

        if (command == NULL)
        {
            continue;
        }
        
        
        if (strcmp(command, "pwd") == 0)
        {
            /* Print current working directory */
            char *cwd = print_working_directory();
            printf("\n%s\n", cwd);
            free(cwd);
        }

        else if (strcmp(command, "echo") == 0)
        {
            if (parameter == NULL)
            {
                printf("\n\n");
            }
            else
            {
                /* If there is "" then remove it before print */
                if (parameter[0] == '"' && parameter[strlen(parameter) - 1] == '"')
                {
                    char *unquoted_parameter = strdup(parameter + 1);

                    if (unquoted_parameter != NULL)
                    {
                        unquoted_parameter[strlen(unquoted_parameter) - 1] = '\0';
                        printf("\n%s\n", unquoted_parameter);

                        free(unquoted_parameter);
                    }
                    
                }

                else if (parameter[0] == '"')
                {
                    printf("\nInvalid Parameter!...\n");
                }
                
                else
                {
                    printf("\n%s\n", parameter);
                }
            }
            
        }

        else if (strcmp(command, "touch") == 0)
        {
            if (parameter == NULL)
            {
               printf("touch: missing file name operand\n");
            }
            else 
            {
                /* Create the file */
                file_ptr = fopen(parameter, "w");

                if (file_ptr == NULL)
                {
                    perror("failed to create file\n");
                }
                else
                {
                    printf("File created successfully!\n");
                    fclose(file_ptr);
                }
            
            }
            
        }

        else if (strcmp(command, "mkdir") == 0) 
        {
            if (parameter == NULL)
            {
                printf("mkdir: missing operand\n");
            }
            else 
            {
                /* Create the directory */
                int status = make_directory(parameter);

                if (status == 0)
                {
                    printf("directory created successfully!\n");
                } 
                else
                {
                    printf("Unable to create the directory named %s\n", parameter);
                }
                
            }
            
        }

        else if (strcmp(command, "ls") == 0)
        {
            if (parameter != NULL)
            {
                printf("ls: invalid parameter...\n");
            }
            else
            {
                /* Print all the files and sub-directories */
                char *path = print_working_directory();
                print_files_and_sub_directories(path);

                free(path);
            }
        }
        
        else if (strcmp(command, "cd") == 0)
        {
            if (parameter == NULL)
            {
                printf("cd: invalid parameter...\n");
            }
            else
            {
                /* Change the directory */
                change_directory(parameter);
            }
            
        }
        
        
        else if (strcmp(command, "exit") == 0 || strcmp(command, "ex") == 0)
        {
            /* exit the shell */
            printf("Exiting the shell...\n");
            break;
        }

        else
        {
            printf("%s : command not found...\n",command);
        }
        

    }
    
    free(input);

    return 0;
}