#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *path = getenv("PATH"); /*get the value of PATH*/
	char *value = path;
	
	char *portion = strtok(value, ":");
	
	while (portion != NULL)
	{
		printf("%s\n", portion);
		portion = strtok(NULL, ":");
	}
	
	return (0);
}
