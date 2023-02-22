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
            break;
        command[strcspn(command, "\n")] = 0;

        const char special_chars[] = {';', '|', '>', '<'};
        for (int i = 0; i < strlen(special_chars); i++)
        {
            if (strchr(command, special_chars[i]))
            printf("Error: Advanced features not supported\n");
            continue;
        }
        pid = fork();
        if (pid == -1)
        {
            printf("Error: Failed to create child process\n");
            continue;
        } else if (pid == 0)
        {
            char *args[] = { command, NULL};
            char *envp[] = { NULL };
        if (execve(command, args, envp) == -1)
            printf("Error: Command not found: %s\n", command);
        } else
        {
            waitpid(pid, &status, 0);
        }
    }
    return (0);
}
