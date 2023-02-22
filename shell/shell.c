#include "main.h"

#define MAX_COMMAND_LENGTH 100


int main(void)
{
  char command[MAX_COMMAND_LENGTH];
  pid_t pid;
  int status;
  
  while (1) 
  {
    printf("#cisfun$ ");
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
    {
      break;
    }
    /*remove the trailing newline character*/
    command[strcspn(command, "\n")] = 0;
    
    if (strchr(command, ';') || strchr(command, '|') || strchr(command, '>') || strchr(command, '<'))
    {
      printf("Error: Advanced features not supported\n");
      continue;
    }
    
    pid = fork();
    if (pid == -1) {
      printf("Error: Failed to create child process\n");
      continue;
    }
    else if (pid == 0)
    {
      // Child process
      char *args[] = { command, NULL };
      char *envp[] = { NULL };
      if (execve(command, args, envp) == -1)
        printf("Error: Command not found: %s\n", command);
    }
    else
    {
      // Parent process
      waitpid(pid, &status, 0);
    }
  }
  
  return 0;
}
