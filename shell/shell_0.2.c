#include "main.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main()
{
  char command[MAX_COMMAND_LENGTH];
  pid_t pid;
  int status;
  
  while (1)
  {
    printf("#cisfun$ ");
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
      break;
    
    command[strcspn(command, "\n")] = 0;
    
    if (strchr(command, ';') || strchr(command, '|') || strchr(command, '>') || strchr(command, '<'))
    {
      printf("Error: Advanced features not supported\n");
      continue;
    }
    
    char *args[MAX_ARGUMENTS+1];
    int arg_count = 0;
    char *token = strtok(command, " \t");
    while (token != NULL)
    {
      if (arg_count == MAX_ARGUMENTS)
      {
        printf("Error: Too many arguments\n");
        break;
      }
      args[arg_count++] = token;
      token = strtok(NULL, " \t");
    }
    args[arg_count] = NULL;
    
    if (arg_count == 0)
      continue;
    pid = fork();
    if (pid == 0)
    {
      execve(args[0], args, NULL);
      printf("Error: Command not found: %s\n", args[0]);
    }
    else if (pid < 0)
    {
      printf("Error: Fork failed");
    }
    else
    {
      wait(&status);
    }
  }
  return 0;
}

