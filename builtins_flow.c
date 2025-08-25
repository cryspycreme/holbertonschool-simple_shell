#include "headers.h"
/**
 * builtins_flow - handles built-in commands flow
 *
 * @command: parsed command tokens
 *
 * Return: 1 if empty/env handled, -1 if exit, 0 otherwise
 */

/* handle builtins*/
int builtins_flow(char **command)
{
	if (command[0] == NULL)
	{
		return (1);
	}
	if (handle_exit(command) == -1)
		return (-1);
	if (handle_env(command))
	{
		return (1);
	}
	return (0);
}
