#include "headers.h"

/**
 * main - Entry point for shell program
 *
 * Return: 0 (always success).
 */

extern char **environ;

int main(int argc, char *argv[])
{
	size_t size = 0;
	ssize_t ncread;
	char *line = NULL, *input_copy = NULL, **command = NULL, *full_path;
	int exe_code, interactive = isatty(STDIN_FILENO);
	int exit_code = 0;

	if (argc < 1)
		return (0);
	while (1)
	{
		input_copy = NULL;
		command = NULL;
		full_path = NULL;

		if (interactive == 1)
			write(1, "$ ", 2);
		ncread = getline(&line, &size, stdin);
		if (ncread == -1)
		{
			if (interactive == 1)
				write(1, "\n", 1);
			break;
		}
		command = tokenise(line, ncread, &input_copy);
		if (command[0] == NULL)
		{
			cleanup(NULL, command, input_copy);
			continue;
		}

		if (handle_exit(command, line, input_copy))
			break;

		if (handle_env(command, input_copy))
			continue;

		full_path = find_path(command[0]);
		if (full_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], command[0]);
			cleanup(NULL, command, input_copy);
			exit_code = 127;
			continue;
		}
		exe_code = exec_cmd(full_path, command);
		if (exe_code >= 0)
			exit_code = exe_code;
		cleanup(full_path, command, input_copy);
	}
	free(line);
	return (exit_code);
}
