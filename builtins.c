#include "headers.h"

extern char **environ;

void print_env(void)
{
	int i = 0;

	for (;  environ[i]; i++)
		printf("%s\n", environ[i]);
}

int handle_builtin(char **command, int *should_exit)
{
	if (!command || !command[0])
		return (0);

	if (strcmp(command[0], "exit") == 0)
	{
		*should_exit = 1;
		return (1);
	}

	if (strcmp(command[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
