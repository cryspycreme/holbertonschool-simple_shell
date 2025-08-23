#include "headers.h"
#include <string.h>

int handle_exit(char **command, char *line, char *input_copy)
{
	if (strcmp(command[0], "exit") == 0)
	{
		cleanup(NULL, command, input_copy);
		free(line);
		exit(0);
	}
	return (0);
}

int handle_env(char **command, char *input_copy)
{
	int i;

	if (strcmp(command[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		cleanup(NULL, command, input_copy);
		return (1);
	}
	return (0);
}
