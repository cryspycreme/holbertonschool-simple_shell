#holbertonschool-simple_shell

Welcome to the **holbertonschool-simple_shell** repository!!
This project is part of the Holberton School curiculum and focuses on building a simple UNIX command interpreter in C. 

## Description

This **simple_shell** project aims to help you understand the inner world of a UNIX shell. 
It can read the user input, parses commands and executes in a similar way to standard UNIX shells. The shell supports basic built-in commands and PATH commands.

## Background Context

> “The Gates of Shell”, by Spencer Cheng, featuring Julien Barbier 
This project will help you learn about:
- The history and design of the original UNIX operating system
- The first UNIX shell and its authors (Ken Thompson)
- The B programming language (predecessor to C)
- How shells work, including process creation and management
- The difference between functions and system calls
- Manipulating the environment of the current process
- Using the PATH to find programs
- Executing programs with `execve`
- Handling EOF (“end-of-file”)

## Contents 

You will find files and folders for:
- **simple_shell.c**: Entry point for the shell, main shell, loop, prompt, line reading
- **find_path.c**: Finds executables in the PATH
- **exec.c**: Forks and executes commands
- **builtins.c**: Built-in commands (exit, env)
- **cleanup.c**: Memory management helpr to free allocated buffers
- **README.md**: Project documentation

## Getting Started

To use or run the shell: 
1. **Clone this repository:**
   ```bash
   git clone https://github.com/<your-username>/simple_shell.git
   cd simple_shell
   ``` 
2. **Compile the shell:**
   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ``` 
3. **Run the shell (interactive mode):**
   ```bash
   ./hsh
   ``` 
4. **Run the shell (non-interactive mode):**
   ```bash
   echo "/bin/ls" | ./hsh
   ``` 
5. **Print the parent process ID:**
   ```bash
   chmod +x "0. getppid"
	./0. getppid

## Requirements 
- Allowed editors: vi, vim, emacs
- All files compiled on Ubuntu 20.04 LTS using gcc with flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files end with a new line
- Code follows Betty style (`betty-style.pl` and `betty-doc.pl`)
- No memory leaks
- No more than 5 functions per file
- All header files are include guarded
- Use system calls only when necessary

## Allowed functions 

- All functions from string.h
- access, chdir, close, closedir, execve, exit, _exit, fflush, fork, free, getcwd, getline, getpid, isatty, kill, malloc, open, opendir, perror, printf, fprintf, vfprintf, sprintf, putchar, read, readdir, signal, stat, lstat, fstat, strtok, wait, waitpid, wait3, wait4, write

## Compilation

Your shell will be compiled this way:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Testing

Interactive mode:
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
``` 
Non-interactive mode:
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$
```

## Resources 
- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- [Shell concept page](https://intranet.hbtn.io/concepts/64)

## Authors

- Crystal Chiam
- Chloe Yang
- Karen Andrianaharison 
