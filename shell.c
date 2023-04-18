#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>

/** Define a constant for the maximum length of a command */
#define MAX_COMMAND_LENGTH 100

/** Declare functions for built-in commands */
void execute_cd(char** args);
void execute_pwd();
void execute_echo(char** args);

int main(void)
{
  char command[MAX_COMMAND_LENGTH];
  int length = 0;
  int result = 0;

  while (1)
  {
    if (isatty(fileno(stdin)))
      printf("($) ");

    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
    {
      break;
    }
    length = strlen(command);
    if (length > 0 && command[length - 1] == '\n')
    {
      command[length - 1] = 0;
    }

    // Split the command string into an array of arguments
    char* args[MAX_COMMAND_LENGTH];
    char* token = strtok(command, " ");
    int i = 0;
    while (token != NULL) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (strcmp(args[0], "exit") == 0)
    {
      break;
    }

    if (strcmp(args[0], "cd") == 0) {
      execute_cd(args);
      continue;
    }

    if (strcmp(args[0], "pwd") == 0) {
      execute_pwd();
      continue;
    }

    if (strcmp(args[0], "echo") == 0) {
      execute_echo(args);
      continue;
    }

    // Check if the command should be run in the background
    int background = 0;
    if (i > 1 && strcmp(args[i-1], "&") == 0) {
      background = 1;
      args[i-1] = NULL;
    }

    pid_t pid = fork();
    if (pid == 0) {
      // Child process
      execvp(args[0], args);
      fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
      exit(EXIT_FAILURE);
    } else if (pid < 0) {
      // Fork failed
      fprintf(stderr, "simple_shell: fork failed\n");
      exit(EXIT_FAILURE);
    } else {
      // Parent process
      if (!background) {
        waitpid(pid, &result, 0);
      }
    }
  }
  return (0);
}

void execute_cd(char** args) {
  if (args[1] == NULL) {
    chdir(getenv("HOME"));
  } else {
    chdir(args[1]);
  }
}

void execute_pwd() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    fprintf(stderr, "simple_shell: pwd failed\n");
  }
}

void execute_echo(char** args) {
  for (int i = 1; args[i] != NULL; i++) {
    printf("%s ", args[i]);
  }
  printf("\n");
}