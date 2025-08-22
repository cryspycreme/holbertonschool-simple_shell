#ifndef header_file
#define header_file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

char *_getenv(const char *name);
char *find_path(char *command);
char *_getenv(const char *name);

int handle_builtin(char **command, int *should_exit);
#endif
