#include "headers.h"
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
int builtins_flow(char **command, char *line, char *input_copy, int *exit_code)
{
	if (command[0] == NULL)
	{
		cleanup(NULL, command, input_copy);
		return (1);
	}
	if (handle_exit(command, line, input_copy, exit_code))
		return (-1);
	if (handle_env(command, input_copy))
	{
		cleanup(NULL, command, input_copy);
		return (1);
	}
	return (0);
}
