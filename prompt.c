#include "headers.h"

/**
 * prompt_if_interactive - prints shell prompt if in interactive mode
 *
 * @interactive: flag (1 = interactive, 0 = non-interactive)
 *
 * Return: void
 */

/* prompt_if_interactive - prints $ only when interactive */
void prompt_if_interactive(int interactive)
{
	if (interactive == 1)
		write(STDOUT_FILENO, "$ ", 2);
}
