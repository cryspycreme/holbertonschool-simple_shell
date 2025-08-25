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
int builtins_flow(char **command, int *exit_code)
{
	if (command[0] == NULL)
	{
		return (1);
	}
	
	if (handle_exit(command,exit_code))
		return (-1);
	
	if (handle_env(command))
	{
		return (1);
	}
	return (0);
}
