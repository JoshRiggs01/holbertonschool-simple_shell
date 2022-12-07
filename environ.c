#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[], char *env[])
{
	printf("%p\n", env);
	printf("%p\n", environ);
	return 0;
}
