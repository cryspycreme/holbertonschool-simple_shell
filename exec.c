#include "headers.h"
/**
 * exec_cmd - function to execute a command using execve
 * @full_path: pointer to the full path of the command
 * @command: pointer to the array of command tokens
 *
 * Return: a code indicating the exit status of the command
 *          or -1 on failure.
 */

int exec_cmd(char *full_path, char **command)
{
	pid_t child;
	int execute, status;

	child = fork();
	if (child < 0)
	{
		perror("fork");
		return (-1);
	}
	if (child == 0)
	{
	    execute = execve(full_path, command, environ);
	    if (execute == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(child, &status, 0) == -1)
		{
			perror("waitpid");
		}
	}
	if (WIFEXITED(status)
			return (WEXITSTATUS(status));
			return (-1);
}
