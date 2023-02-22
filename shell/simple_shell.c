#include "main.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void exit_shell() {
    exit(0);
}

void env_shell() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}

int main(void) 
{
    char command[MAX_COMMAND_LENGTH], *path_env = getenv("PATH");
    while (1)
    {
        printf("#cisfun$ ");
        if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) 
            break;
        command[strcspn(command, "\n")] = 0;
        char *args[MAX_ARGUMENTS+1];
        int arg_count = 0;
        char *token = strtok(command, " \t");
        while (token)
        {
            if (arg_count == MAX_ARGUMENTS)
            {
                printf("Error: Too many arguments\n");
                break;
            }
            args[arg_count++] = token, token = strtok(NULL, " \t");
        }
        args[arg_count] = NULL;
        if (arg_count == 0)
            continue;
        if (strcmp(args[0], "exit") == 0)
            exit_shell();
        else if (strcmp(args[0], "env") == 0)
            env_shell();
        else
        {
            pid_t pid = fork();
            if (pid == -1)
                printf("Error: Fork failed\n");
            else if (pid == 0) 
            {
                char command_path[MAX_COMMAND_LENGTH];
                int found = 0;
                for (char *path_token = strtok(path_env, ":"); path_token && !found; path_token = strtok(NULL, ":"))
                {
                    snprintf(command_path, MAX_COMMAND_LENGTH, "%s/%s", path_token, args[0]);
                    if (access(command_path, X_OK) == 0) found = 1, execvp(command_path, args);
                }
                if (!found) 
                    printf("Error: Command not found: %s\n", args[0]);
                exit(0);
            }
            else
            {
                waitpid(pid, NULL, 0);
            }
        }
    }
    return 0;
}
