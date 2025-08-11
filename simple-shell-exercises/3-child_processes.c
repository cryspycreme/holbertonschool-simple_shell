#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int i = 0; /*loop counter*/
	int val, status;
	
	/*Argument list for execve: argv[0] is the program name*/
    char *args[] = {"/bin/ls", "-l", "/tmp", NULL};
	
	while (i < 5)
	{
		pid = fork(); /*creates the child process*/
		
		if (pid == -1) /*CHECK: if child process failed*/
		{
			perror("Error fork");
			return (-1);
		}
		if (pid == 0) /*if child process succeeds*/
		{
			printf("Child %d executing ls -l /tmp\n", i + 1);
			val = execve(args[0],args, NULL); /*execute child program*/
			
			if (val == -1)
			{	
				perror("Error execve");
				exit(EXIT_FAILURE);	
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
            		{
                		printf("Child %d exited with status %d\n", i + 1, WEXITSTATUS(status));
            	}
            	else if (WIFSIGNALED(status))
            	{
                	printf("Child %d killed by signal %d\n", i + 1, WTERMSIG(status));
            	}
		}
	i++;
	}
	return (0);
}
