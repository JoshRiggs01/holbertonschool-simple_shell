#include "main.h"
/**
 * main - entry point
 */
/** Define a constant for the maximum length of a command*/
#define MAX_COMMAND_LENGTH 100
int main(void)
{
	char command[MAX_COMMAND_LENGTH]; /** declaring command var name*/
	int length = 0;
	int result = 0; /** declating the length and result variable outside lopp*/
	char buf[1024];

	while (1) /** Loop until the user enters the "exit" command.*/
	{
		if (isatty(fileno(stdin)))
		{
			write(STDOUT_FILENO, "($) ", 4);
		}

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			break; /** If end of file is reached (Ctrl+D), exit the program*/
			exit(EXIT_SUCCESS);
		}
		length = strlen(command); /** Remove the trailing \n frm cmd*/
		if (length > 0 && command[length - 1] == '\n')
		{
			command[length - 1] = 0;
		}
			if (strcmp(command, "exit") == 0)
			{
				break;
			}
			result = system(command);
			if (result == 127) /**command not found print error*/
			{
				fprintf(stderr, "simple_shell: command not found: %s\n", command);
			}
			else if (result == 0)
			{
				FILE *fp = popen(command, "r");
				if (fp == NULL)
				{
					perror("popen");
					exit(EXIT_FAILURE);
				}
				while (fgets(buf, sizeof(buf), fp) != NULL)
			{
				char *token = strtok(buf, "\n");
				while (token != NULL)
				{
					write(STDOUT_FILENO, token, strlen(token));
					write(STDOUT_FILENO, "\n", 1);
					token = strtok(NULL, "\n");
				}
			}
			pclose(fp);
			}
	}
	return (0);
}