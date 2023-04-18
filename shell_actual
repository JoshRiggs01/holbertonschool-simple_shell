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

	while (1) /** Loop until the user enters the "exit" command.*/
	{
		if (isatty(fileno(stdin)))
		printf("($) ");

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			break; /** If end of file is reached (Ctrl+D), exit the program*/
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
	}
	exit(EXIT_SUCCESS);
	return (0);
}