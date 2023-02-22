#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *path_env = getenv("PATH");
    pid_t pid;
    int status;

    if (path_env == NULL)
    {
        printf("Error: PATH environment variable is not set\n");
        return 1;
    }

    while (1)
    {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
            break;
        command[strcspn(command, "\n")] = '\0';

        if (strpbrk(command, ";|<>"))
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

        char *command_path = NULL;
        char *path_token = strtok(path_env, ":");
        while (path_token != NULL)
        {
            char *temp_path = malloc(strlen(path_token) + strlen(args[0]) + 2);
            sprintf(temp_path, "%s/%s", path_token, args[0]);
            if (access(temp_path, X_OK) == 0)
            {
                command_path = temp_path;
                break;
            }
            free(temp_path);
            path_token = strtok(NULL, ":");
        }

        if (command_path == NULL)
        {
            printf("Error: Command not found: %s\n", args[0]);
            continue;
        }

        pid = fork();
        if (pid < 0)
        {
            printf("Error: Failed to fork process\n");
        }
        else if (pid == 0)
        {
            if (execv(command_path, args) == -1)
            {
                printf("Error: Failed to execute command: %s\n", args[0]);
                exit(1);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }

        free(command_path);
    }

    return 0;
}
