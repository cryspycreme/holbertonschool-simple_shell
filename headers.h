#ifndef header_file
#define header_file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

char *_getenv(const char *name);
char *find_path(char *command);
char **tokenise(char *line, ssize_t ncread, char **input_copy_ptr);
int exec_cmd(char *full_path, char **command);
void cleanup(char *full_path, char **command, char *input_copy);
int handle_exit(char **command, char *line, char *input_copy, int *exit_code);
void prompt_if_interactive(int interactive);
int handle_env(char **command, char *input_copy);
int read_line_into(char **line, size_t *size, int interactive);
int builtins_flow(char **command, char *line, char *input_copy, int *exit_code);
int execute_flow(char **command, char *progname, int *exit_code);

#endif
