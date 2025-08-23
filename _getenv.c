#include "headers.h"
#include <stdio.h>  /*printf*/
#include <string.h> /*strtok()*/

/**
 * _getenv - gets the PATH environment variable from the environ name.
 *
 * @name: environ variable name.
 * Return: Pointer to the content of a variable, or NULL if fails.
 */

char *_getenv(const char *name)
{
	int i = 0;
	int name_len = strlen(name);

	while (environ[i] != NULL)
	{
		if (environ[i][name_len] == '=' && strncmp(environ[i], name, name_len) == 0)
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}
