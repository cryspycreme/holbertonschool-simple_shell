#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
 
 int main(void)
{
	extern char **environ;
	
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
	
	return (0);
}
