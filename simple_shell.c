#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char *args[100];
	char *token;
	char *input;
	char *delim = " ";
	int i = 0;
	int status;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		input = malloc(sizeof(char) * 1024);
		if (input == NULL)
		{
			perror("Error: malloc failed\n");
			exit(1);
		}
		if (fgets(input, 1024, stdin) == NULL)
		{
			perror("Error: fgets failed\n");
			exit(1);
		}
		token = strtok(input, delim);
		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		args[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Error: execve failed\n");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("Error: fork failed\n");
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}
}
