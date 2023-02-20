#include "main.h"

#define MAX_COMMAND_LENGTH 100


int main(void)
{
  char command[MAX_COMMAND_LENGTH];
  
  while (1) 
  {
    printf("#cisfun$ ");
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
      break;
    /*remove the trailing newline character*/
    command[strcspn(command, "\n")] = 0;
    
    if (strchr(command, ';') || strchr(command, '|') || strchr(command, '>') || strchr(command, '<'))
    {
      printf("Error: Advanced features not supported\n");
      continue;
    }
    
    char *token = strtok(command, " \t");
    if (token == NULL)
      continue;
    else if (strtok(NULL, " \t") != NULL)
    {
      printf("Error: Command lines must be one word\n");
      continue;
    }
    
    char *args[] = { token, NULL };
    char *envp[] = { NULL };
    if (execve(token, args, envp) == -1)
      printf("Error: Command not found: %s\n", token);

  }
  
  return 0;
}
