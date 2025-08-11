#include <string.h>
#include <stdio.h>

int main(void)
{
	char s[] = "My name is Crystal";
	char d[] = " ";
	
	char *portion = strtok(s, d);
	
	while (portion != NULL)
	{
		printf("%s\n", portion);
		portion = strtok(NULL, d);
	}
	
	return (0);
}
