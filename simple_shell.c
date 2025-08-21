#include "headers.h"

/**
 * main - Entry point for shell program
 *
 * Return: 0 (always success).
 */

#define MAX_ARGS 100
extern char **environ;

int main(int argc, char **argv)
{
    size_t size = 0;
    ssize_t ncread;
    char *line = NULL, *input_copy, *token, **command;
    pid_t child;
    int i, status, execute, interactive = isatty(STDIN_FILENO);

	(void)argc;
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

        child = fork();
        if (child < 0)
        {
            perror("fork");
            return (EXIT_FAILURE);
        }
        if (child == 0)
        {
            execute = execve(command[0], command, environ);
            if (execute == -1)
            {
                dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", argv[0], command[0]);
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
        free(command);
        free(input_copy);
    }
    free(line);
    return (0);
}
