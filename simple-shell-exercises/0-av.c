#include <stdlib.h>
#include <stdio.h>

/**
* main - Entry point
*
* @ac: argument count
* @av: argument vector
* Return: Always 0 (Success)
*/

int main(int ac, char **av)
{
	int i;
	i = 0;
		
	while (av[i] != NULL)
	{
		printf("%s\n",av[i]);
		i++;		
	}
	(void)ac;
	return (0);
}
