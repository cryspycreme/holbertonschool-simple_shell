#include <stdio.h>
#include <string.h>

char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0;
	size_t len = strlen(name); /*this stores the no. of characters in name*/
	
	while (environ[i] != NULL)
	{
		if ((environ[i][len] == '=') && (strncmp(environ[i], name, len) == 0))
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	
	if (environ[i] == NULL)
		return (NULL);
}

int main(void)
{
	char *address = _getenv("PATH");
	if (address)
	{
		printf("PATH = %s\n", address);
	}
	else
	{
		printf("PATH not found\n");
	}
	return (0);
}
