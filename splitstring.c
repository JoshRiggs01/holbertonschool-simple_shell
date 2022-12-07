#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *str, char *delimiter);

int main()
{
    char *str = "This is a string";
    char *delimiter = " ";
    char **words = split(str, delimiter);
    int i = 0;
    while (words[i] != NULL)
    {
        printf("%s\n", words[i]);
        i++;
    }
    return 0;
}

char **split(char *str, char *delimiter)
{
    char **words = malloc(sizeof(char *) * strlen(str));
    char *word = strtok(str, delimiter);
    int i = 0;
    while (word != NULL)
    {
        words[i] = word;
        word = strtok(NULL, delimiter);
        i++;
    }
    words[i] = NULL;
    return words;
}
