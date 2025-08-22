#include "headers.h"

void cleanup(char *full_path, char **command, char *input_copy)
{
		if (full_path)
		{
			free(full_path);
		}
		if (command)
		{
			free(command);
		}
		if (input_copy)
		{
			free(input_copy);
		}
    }