#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("%d\n", getppid());
	return 0;
}
