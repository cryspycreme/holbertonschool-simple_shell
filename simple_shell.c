#include "headers.h"

/**
 * main - Entry point for shell program
 *
 * Return: 0 (always success).
 */

#define MAX_ARGS 100
extern char **environ;

int main(void)
{
size_t size = 0;
ssize_t ncread;
char *line = NULL, *input_copy = NULL, *token, **command = NULL, *full_path;
pid_t child;
int i, status, execute, interactive = isatty(STDIN_FILENO);
int should_exit = 0;

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
			{
				write(1, "\n", 1);
			}
			break;
		}

		input_copy = strdup(line);

		if (input_copy == NULL)
		{
			perror("strdup");
			goto cleanup;
		}

		if (ncread > 0 && input_copy[ncread - 1] == '\n')
		{
			input_copy[ncread - 1] = '\0';
		}

		i = 0;

		token = strtok(input_copy, " \t\n\r");

		command = malloc(sizeof(char *) * MAX_ARGS);
		if (command == NULL)
		{
			perror("malloc");
			goto cleanup;
		}

		while (token != NULL && i < MAX_ARGS - 1)
		{
			command[i] = token;
			token = strtok(NULL, " \t\n\r");
			i++;
		}
		command[i] = NULL;

		if (command[0] == NULL)
		{
			goto cleanup;
		}
		if (strcmp(command[0], "exit") == 0)
		{
			should_exit = 1;
			goto cleanup;
		}

		full_path = find_path(command[0]);

		if (full_path == NULL)
		{
			dprintf(STDERR_FILENO, "Command not found: %s\n", command[0]);
			goto cleanup;
		}

		child = fork();

		if (child < 0)
		{
			perror("fork");
			goto cleanup;
		}

		if (child == 0)
		{
			execute = execve(full_path, command, environ);
			if (execute == -1)
			{
				perror("execve");
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (waitpid(child, &status, 0) == -1)
			{
				perror("waitpid");
			}
		}
	cleanup:
		if (full_path)
		{
			free(full_path);
			full_path = NULL;
		}
		if (command)
		{
			free(command);
			command = NULL;
		}
		if (input_copy)
		{
			free(input_copy);
			input_copy = NULL;
		}
		if (should_exit)
			break;
	}
	free(line);
	return (0);
}
