#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char command[100];
    printf("$ ");
    scanf("%s", command);
    printf("%s\n", command);
    return 0;
}
