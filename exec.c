#include "headers.h"

extern char **environ;

int exec_cmd(char *full_path, char **command)
{
    pid_t child;
    int execute, status;
    
    child = fork();
	if (child < 0)
	{
		perror("fork");
		return (-1);
	}		
    if (child == 0)
	{	
        execute = execve(full_path, command, environ);
		if (execute == -1)
		{
        	perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(child, &status, 0) == -1)
		{
			perror("waitpid");
		}
	}
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-1);
}