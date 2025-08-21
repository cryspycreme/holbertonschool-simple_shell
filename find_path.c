#include "headers.h"

/**
 * find_path - searches for the path of command
 *
 * @command: the command that is passed in from the shell
 * Return: full path name of the command.
 */

char *find_path(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int dir_length, command_length;
	struct stat buf;

	path = _getenv("PATH");
	path_copy = strdup(path);

	command_length = strlen(command);

	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		dir_length = strlen(path_token);
		file_path = malloc(dir_length + command_length + 2);

		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);
		strcat(file_path, "\0");

		if (stat(file_path, &buf) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		else
		{
			free(file_path);
			path_token = strtok(NULL, ":");
		}
	}

	free(path_copy);

	if (stat(command, &buf) == 0)
	{
		return (command);
	}
	return (0);
}
