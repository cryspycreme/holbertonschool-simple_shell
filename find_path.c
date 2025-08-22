#include "headers.h"

/**
 * find_path - searches for the path of command
 *
 * @command: the command that is passed in from the shell
 * Return: full path name of the command.
 */

char *find_path(char *command)
{
	char *path, *path_copy = NULL, *path_token, *file_path;
	int dir_length, command_length;
	struct stat buf;

	if (command == NULL || *command == '\0')
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &buf) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	command_length = (int)strlen(command);

	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		dir_length = (int)strlen(path_token);
		file_path = malloc(dir_length + command_length + 2);
		if (file_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buf) == 0)
		{
			free(path_copy);
			return (file_path);
		}

			free(file_path);
			path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
