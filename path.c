#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	char *path;
	char *token;
	char *file;
	char *dir;
	char *fullpath;
	struct stat buf;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	file = argv[1];
	path = getenv("PATH");
	token = strtok(path, ":");

	while (token != NULL) {
		dir = token;
		fullpath = malloc(strlen(dir) + strlen(file) + 2);
		if (fullpath == NULL) {
			perror("malloc");
			exit(1);
		}
		sprintf(fullpath, "%s/%s", dir, file);
		if (stat(fullpath, &buf) == 0) {
			if (S_ISREG(buf.st_mode)) {
				printf("%s\n", fullpath);
				exit(0);
			}
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}

	exit(1);
}
