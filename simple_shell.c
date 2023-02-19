#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1000

/**
 * main - Entry point for simple shell program
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * @envp: Array of environmental variable strings
 *
 * Return: Always 0
 */
int main(int argc, char *argv[], char **envp)
{
	char command[MAX_COMMAND_LENGTH], *args[MAX_COMMAND_LENGTH], *arg;
	pid_t pid;
	int status, i;

	while (1)
	{
		printf("simple-shell->> ");
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;
		if (command[0] == '\n')
			continue;
		for (arg = strtok(command, " \t\n"), i = 0;
		     arg != NULL;
		     arg = strtok(NULL, " \t\n"))
			args[i++] = arg;
			args[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			fprintf(stderr, "Simple_shell: Command not found: %s\n", args[0]);
			exit(1);
		}
		else if (pid < 0)
		{
			fprintf(stderr, "Simple shell: fork failed\n");
			exit(1);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (0);
}

