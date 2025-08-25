#include "headers.h"
#include <string.h>

/**
 * handle_exit - exits the shell
 *
 * @command: pointer to array of strings ie command line
 * @line: input from the command line
 * @input_copy: copy of input string
 * Return: 0 - exit
 */

int handle_exit(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		return (-1);
	}
	return (0);
}

/**
 * handle_env - prints the environment
 *
 * @command: pointer to array of strings ie command line
 * @input_copy: copy of input string
 * Return: 1 if command success, 0 on failure
 */

int handle_env(char **command)
{
	int i;

	if (strcmp(command[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	return (0);
}
