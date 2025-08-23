#include "headers.h"
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

int execute_flow(char **command, char *progname,
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
