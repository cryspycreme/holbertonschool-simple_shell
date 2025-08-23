#include "headers.h"

/**
 * prompt_if_interactive - prints shell prompt if in interactive mode
 *
 * @interactive: flag (1 = interactive, 0 = non-interactive)
 *
 * Return: void
 */

/* prompt_if_interactive - prints $ only when interactive */
static void prompt_if_interactive(int interactive)
{
	if (interactive == 1)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_line_into - reads a line from stdin
 *
 * @line: buffer to store input
 * @size: buffer size
 * @interactive: flag (1 = interactive, 0 = non-interactive)
 *
 * Return: number of chars read, -1 on EOF/error
 */

/* read_line_into - wrap getline */
static int read_line_into(char **line, size_t *size, int interactive)
{
	ssize_t n = getline(line, size, stdin);

	if (n == -1)
	{
		if (interactive == 1)
			write(STDOUT_FILENO, "\n", 1);
		return (-1);
	}
	return ((int)n);
}

/**
 * builtins_flow - handles built-in commands flow
 *
 * @command: parsed command tokens
 * @line: input line buffer
 * @input_copy: duplicate of input for tokenization
 *
 * Return: 1 if empty/env handled, -1 if exit, 0 otherwise
 */

/* handle builtins*/
static int builtins_flow(char **command, char *line, char *input_copy)
{
	if (command[0] == NULL)
	{
		cleanup(NULL, command, input_copy);
		return (1);
	}
	if (handle_exit(command, line, input_copy))
		return (-1);
	if (handle_env(command, input_copy))
	{
		cleanup(NULL, command, input_copy);
		return (1);
	}
	return (0);
}

/**
 * execute_flow - resolves and runs external commands
 *
 * @command: parsed command tokens
 * @progname: program name for error messages
 * @input_copy: duplicate of input for tokenization
 * @exit_code: pointer to store exit status
 *
 * Return: 0 always
 */

static int execute_flow(char **command, char *progname,
		char *input_copy, int *exit_code)
{
	char *full_path = find_path(command[0]);

	if (full_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, command[0]);
		cleanup(NULL, command, input_copy);
		*exit_code = 127;
		return (0);
	}
	{
		int ec = exec_cmd(full_path, command);

		if (ec >= 0)
			*exit_code = ec;
	}
	cleanup(full_path, command, input_copy);
	return (0);
}

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
			int b = builtins_flow(command, line, input_copy);

			if (b == -1)
				break;
			if (b == 1)
				continue;
		}

		execute_flow(command, argv[0], input_copy, &exit_code);
	}

	free(line);
	return (exit_code);
}
