#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {
    char *line = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    int status;

    while (isatty(fileno(stdin))) {
        printf("shell$ ");
        fflush(stdout);

        line_size = getline(&line, &line_buf_size, stdin);

        if (line_size == -1) {
            break;
        }

        line[line_size - 1] = '\0';

        char *args[2] = {line, NULL};

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process
            execvp(args[0], args);
            perror("execvp");
            _exit(EXIT_FAILURE);
        } else {
            // parent process
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}
