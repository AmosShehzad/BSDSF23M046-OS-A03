

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 512
#define MAX_ARGS  10
#define ARG_LEN   30
#define PROMPT "FCIT> "

/* Function prototypes */
char* get_command(const char* prompt, FILE* stream);
char** parse_input(char* cmdline);
int execute_command(char** argv);
int handle_builtin(char** argv);

#endif
