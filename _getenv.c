#include "headers.h"

/**
 * _getenv - gets the PATH environment variable from the environ name.
 *
 * @name: environ variable name.
 * Return: the value of the environ variable.
 */ 

extern char **environ; 
char *_getenv(const char *name)
{
	int i = 0;
	int name_len = strlen(name);
	char *env_value; 
	while (environ[i] != NULL)
	{
		if (environ[i][name_len] == '=' && strncmp(environ[i], name, name_len))
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	} 
	if (environ[i] == NULL)
		return (0);
}
