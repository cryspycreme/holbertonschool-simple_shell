#include "headers.h"

/**
 * main - Entry point for shell program
 *
 * @argc: argument count
 * @argv: argument vector (prog name, etc.)
 *
 * Return: last command’s exit status
 */
int main(int argc, char *argv[])
{
	size_t size = 0;
	ssize_t ncread = 0;
	char *line = NULL, *input_copy = NULL, **command = NULL;
	int interactive = isatty(STDIN_FILENO), exit_code = 0;

	if (argc < 1)
		return (0);
	while (1)
	{
		input_copy = NULL;
		command = NULL;

		prompt_if_interactive(interactive);

		ncread = read_line_into(&line, &size, interactive);
		if (ncread == -1)
			break;

		command = tokenise(line, ncread, &input_copy);
		{
			int b = builtins_flow(command, &exit_code);

			if (b == -1)
			{
				cleanup(NULL, command, input_copy);
				free(line);
				break;
			}
			if (b == 1)
			{
				cleanup(NULL, command, input_copy);
				continue;
			}
		}
		execute_flow(command, argv[0], &exit_code);
		cleanup(NULL, command, input_copy);
	}
	free(line);
	return (exit_code);
}
