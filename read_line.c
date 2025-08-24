#include "headers.h"
/**
 * read_line_into - reads a line from stdin
 *
 * @line: buffer to store input
 * @size: buffer size
 * @interactive: flag (1 = interactive, 0 = non-interactive)
 *
 * Return: number of chars read, -1 on EOF/error
 */

/* read_line_into - wrap getline */
int read_line_into(char **line, size_t *size, int interactive)
{
	ssize_t n = getline(line, size, stdin);

	if (n == -1)
	{
		if (interactive == 1)
			write(STDOUT_FILENO, "\n", 1);
		return (-1);
	}
	return ((int)n);
}
