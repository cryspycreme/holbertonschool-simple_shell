#include "headers.h"
/**
 * cleanup - function to free allocated memory
 * @full_path: pointer to the full path of the command
 * @command: pointer to the array of command tokens
 * @input_copy: pointer to the copied input string
 *
 * Return: void
 */
void cleanup(char *full_path, char **command, char *input_copy)
{
		if (full_path)
		{
			free(full_path);
			full_path = NULL;
		}
		if (command)
		{
			free(command);
			command = NULL;
		}
		if (input_copy)
		{
			free(input_copy);
			input_copy = NULL;
		}
}
