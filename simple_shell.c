#include "headers.h"

/**
 * main - Entry point for shell program
 *
 * Return: 0 (always success).
 */

extern char **environ;
int main(int argc, char *argv[])
{
    size_t size = 0;
    ssize_t ncread;
    char *line = NULL, *input_copy, *token, **command, *full_path;
    pid_t child;
    int i, status, execute, interactive = isatty(STDIN_FILENO);
    int should_exit = 0;
    int exit_code = 0;
    if (argc < 1)
        return (0);
    while (1)
    {
        input_copy = NULL;
        command = NULL;
        full_path = NULL;

        /*PRINT PROMPT*/
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

       command = tokenise(line, ncread, &input_copy);
        
        if (command[0] == NULL)
            goto cleanup;

        /*BUILT IN COMMANDS*/
        if (strcmp(command[0], "exit") == 0)
        {
            should_exit = 1;
            goto cleanup;
        }
        if (strcmp(command[0], "env") == 0)
        {
            int j = 0;
            while (environ[j] != NULL)
            {
                printf("%s\n", environ[j]);
                j++;
            }
            goto cleanup;
        }

        /*FIND PATH*/
        full_path = find_path(command[0]);
        if (full_path == NULL)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", argv[0], command[0]);
            exit_code = 127;
            goto cleanup;
        }

        /*EXECUTE*/
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
            else
            {
                if (WIFEXITED(status))
                    exit_code = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                    exit_code = 128 + WTERMSIG(status);
            }
        }
    /*CLEANUP*/
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
    return (exit_code);
}
