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
char *line = NULL, *input_copy, *token, **command, *full_path;
pid_t child;
int i, status, execute, interactive = isatty(STDIN_FILENO);

	while (1)
	{
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
			continue;
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
			exit(EXIT_FAILURE);
		}

		while (token != NULL)
		{
			command[i] = token;
			token = strtok(NULL, " \t\n\r");
			i++;
		}
		command[i] = NULL;

		if (command[0] == NULL)
		{
			free(command);
			free(input_copy);
			continue;
		}

		if (strcmp(command[0], "exit") == 0)
		{
			free(command);
			free(input_copy);
			exit(0);
		}
		else if (strcmp(command[0], "env") == 0)
		{
			char **env = environ;
			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		}

		full_path = find_path(command[0]);

		if (full_path == NULL)
		{
			dprintf(STDERR_FILENO, "Command not found: %s\n", command[0]);
			free(full_path);
		}

		child = fork();

		if (child < 0)
		{
			perror("fork");
			return (EXIT_FAILURE);
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
		free(input_copy);
	}
	free(line);
	return (0);
}
