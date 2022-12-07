#include <stdio.h>
#include <stdlib.h>

/**
 * _getenv - gets an environment variable
 * @name: name of the variable
 * Return: pointer to the value of the variable
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char *value;

	while (environ[i] != NULL)
	{
		while (environ[i][j] != '=')
			j++;
		if (_strncmp(environ[i], name, j) == 0)
		{
			value = malloc(sizeof(char) * (_strlen(environ[i]) - j));
			if (value == NULL)
				return (NULL);
			j++;
			while (environ[i][j] != '\0')
			{
				value[k] = environ[i][j];
				j++;
				k++;
			}
			value[k] = '\0';
			return (value);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

#include <stdio.h>
#include <stdlib.h>


/**
 * _strncmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes to compare
 * Return: 0 if strings are equal, 1 if not
 */
int _strncmp(char *s1, const char *s2, int n)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}
