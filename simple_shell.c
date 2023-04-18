#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main()
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid;
	int status;
	int input_is_terminal = isatty(STDIN_FILENO);

	while (1)
	{
		if (input_is_terminal)
		{
			printf("$ ");
		}

		fgets(command, MAX_COMMAND_LENGTH, stdin);

		if (strcmp(command, "exit") == 0)
		{
			return (0);
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execlp(command, command, NULL);
			perror("execlp");
			_exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
