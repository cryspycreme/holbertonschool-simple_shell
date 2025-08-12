#include <stdio.h>

/**
 * main - prints the address of the environment variable
 *
 * Return: Always 0.
 */
 
 int main(int ac, char **av, char **env)
 {
	 extern char **environ;
	 
	 printf("%p\n", &env);
	 printf("%p\n", &environ);
	 
	 return (0);
 }
