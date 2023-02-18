#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1000

//There are no built-in commands for this shell program

int main (int argc, char * argv[],char **envp)
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		printf ("simple-shell->> ");

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			//For terminating the 'simple shell' program
			break;
		}
		if (command[0] == '\n')
		{
			//Prompts the user to enter another command if the user has 
			//entered a blank line 
			continue;
		}

		char * args[MAX_COMMAND_LENGTH];
		char *arg = strtok(command, " \t\n");
		int i = 0;
		while (arg != 0)
		{
			args[i++] = arg;
			arg = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		//Creates a new process for the child program "for external commands".
		//The parent process waits till its child terminates before it continues
		//running .
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
			exit (1);
		} 
		else 
		{
			waitpid(pid,&status,0);
		}
	}
		
	return (0);
}
	

