#include "headers.h"

/* helper to validate direct path*/
static char *try_direct(char *command, struct stat *buf)
{
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, buf) == 0)
			return (strdup(command));
		return (NULL);
	}
	return (NULL);
}

/* scan path*/
static char *scan_path(char *path_copy, char *command,
		int cmd_len, struct stat *buf)
{
	char *tok = strtok(path_copy, ":"), *file_path;
	int dir_len;

	while (tok != NULL)
	{
		dir_len = (int)strlen(tok);
		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(file_path, tok);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, buf) == 0)
		{
			free(path_copy);
					return (file_path);
		}

		free(file_path);
		tok = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * find_path - searches for the path of command
 *
 * @command: the command that is passed in from the shell
 * Return: full path name of the command.
 */

char *find_path(char *command)
{
	char *path, *path_copy = NULL, *hit;
	int cmd_len;
	struct stat buf;

	if (command == NULL || *command == '\0')
		return (NULL);

	hit = try_direct(command, &buf);
	if (hit != NULL)
		return (hit);

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	cmd_len = (int)strlen(command);
	return (scan_path(path_copy, command, cmd_len, &buf));
}
