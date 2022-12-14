#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>

/** Define a constant for the maximum length of a command*/
#define MAX_COMMAND_LENGTH 100

int main() 
{
    /** Declare the command variable at the beginning of the function*/
    char command[MAX_COMMAND_LENGTH];
	/** declating the length and result variable outside of the while lopp*/
    int length = 0;
    int result = 0;

    /**
     * Loop until the user enters the "exit" command.
     */
    while (1) 
    {
        /** Display the prompt and read the user's input*/
        printf("($) ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) 
	{
            /** If end of file is reached (Ctrl+D), exit the program*/
            break;
        }

        /** Remove the trailing newline character from the command*/
       	length = strlen(command);
        if (length > 0 && command[length - 1] == '\n') 
	{
            command[length - 1] = 0;
        }

        /** If the user entered the "exit" command, exit the program*/
        if (strcmp(command, "exit") == 0) 
	{
            break;
        }

        /** Try to execute the command using the system() function*/
       	result = system(command);

        /** If the command was not found, print an error message*/
        if (result == 127) 
	{
            fprintf(stderr, "simple_shell: command not found: %s\n", command);
        }
    }

    return (0);
}

