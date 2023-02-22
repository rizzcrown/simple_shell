#include "main.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/*
 * This program is a simple shell that reads user input, searches for the corresponding
 * executable file in the system's directories specified in the PATH environment variable,
 * and executes the command with the specified arguments.
 * The program continues to prompt for user input until the user types "exit".
 */

int main(void)
{
    char command[MAX_COMMAND_LENGTH], *path_env = getenv("PATH");
    while (1)
	{
        printf("#cisfun$ ");
        if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) break;
        command[strcspn(command, "\n")] = 0;

        // Check if user has entered "exit"
        if (strcmp(command, "exit") == 0) {
            exit(0);
        }

        char *args[MAX_ARGUMENTS+1];
        int arg_count = 0;
        char *token = strtok(command, " \t");
        while (token)
		{
            if (arg_count == MAX_ARGUMENTS) {
                printf("Error: Too many arguments\n");
                break;
            }
            args[arg_count++] = token, token = strtok(NULL, " \t");
        }
        args[arg_count] = NULL;
        if (arg_count == 0) continue;
        char command_path[MAX_COMMAND_LENGTH];
        int found = 0;
        for (char *path_token = strtok(path_env, ":"); path_token && !found; path_token = strtok(NULL, ":"))
		{
            snprintf(command_path, MAX_COMMAND_LENGTH, "%s/%s", path_token, args[0]);
            if (access(command_path, X_OK) == 0) found = 1;
        }
        if (!found)
		{
            printf("Error: Command not found: %s\n", args[0]);
            continue;
        }
        pid_t pid = fork();
        if (pid < 0)
		{
            printf("Error: Failed to fork process\n");
        } else if (pid == 0)
		{
            execv(command_path, args);
            printf("Error: Failed to execute command: %s\n", args[0]);
            exit(1);
        } else {
            wait(NULL);
        }
    }
    return 0;
}

