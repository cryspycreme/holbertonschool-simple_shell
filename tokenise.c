#include "headers.h"

#define MAX_ARGS 100

/**
 * tokenise - splits the command line arguments into tokens
 *
 * @line: buffer that stores stdin from main.c 
 * @ncread: no. characters read from getline() in main.c
 * @input_copy_ptr: output, returns a pointer to input_copy so main.c can safely free.
 * Return: pointer to an arraty of strings (ie. command)
 */

char **tokenise(char *line, ssize_t ncread, char **input_copy_ptr)
{
    char *token, **command, *input_copy, *input_copy_ptr;
    int i;

    input_copy = strdup(line);
    if (input_copy == NULL)
    {
        perror("strdup");
        return (NULL);
    }
    if (ncread > 0 && input_copy[ncread - 1] == '\n')
    {
        input_copy[ncread - 1] = '\0';
    }

    token = strtok(input_copy, " \t\n\r");
    command = malloc(sizeof(char *) * MAX_ARGS);
    if (command == NULL)
    {
        perror("malloc");
        free(input_copy);
        return (NULL);
    }

    i = 0;
    while (token != NULL && i < MAX_ARGS - 1)
    {
        command[i] = token;
        token = strtok(NULL, " \t\n\r");
        i++;
    }

    command[i] = NULL;

    *input_copy_ptr = input_copy;

    return (command);
}
