#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 *
 *
 *
 *
 */

int main(int argc, char *argv[])
{
	char *args[100];
	int i;
	for(i = 0; i < argc; i++)
	{
		args[i] = malloc(strlen(argv[i]) + 1);
		strcpy(args[i], argv[i]);
	}
	args[argc] = NULL;
	execve(args[0], args, NULL);
	return 0;
}
