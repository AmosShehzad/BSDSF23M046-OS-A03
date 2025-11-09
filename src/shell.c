

#include "shell.h"

/* -------------------- Read User Input -------------------- */
char* get_command(const char* prompt, FILE* stream) {
    printf("%s", prompt);
    fflush(stdout);

    char* line = malloc(MAX_INPUT);
    if (!line) {
        perror("malloc");
        exit(1);
    }

    int ch, pos = 0;
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (pos < MAX_INPUT - 1)
            line[pos++] = ch;
    }

    if (ch == EOF && pos == 0) {
        free(line);
        return NULL;   // Ctrl+D
    }

    line[pos] = '\0';
    return line;
}

/* -------------------- Tokenize Input -------------------- */
char** parse_input(char* cmdline) {
    if (!cmdline || cmdline[0] == '\0') return NULL;

    char** args = malloc(sizeof(char*) * (MAX_ARGS + 1));
    if (!args) {
        perror("malloc");
        exit(1);
    }

    for (int i = 0; i < MAX_ARGS + 1; i++) {
        args[i] = malloc(ARG_LEN);
        memset(args[i], 0, ARG_LEN);
    }

    int arg_count = 0;
    char* token = strtok(cmdline, " \t");
    while (token != NULL && arg_count < MAX_ARGS) {
        strncpy(args[arg_count++], token, ARG_LEN - 1);
        token = strtok(NULL, " \t");
    }

    if (arg_count == 0) {
        for (int i = 0; i < MAX_ARGS + 1; i++) free(args[i]);
        free(args);
        return NULL;
    }

    args[arg_count] = NULL;
    return args;
}

/* -------------------- Handle Built-in Commands -------------------- */
int handle_builtin(char** argv) {
    if (argv == NULL || argv[0] == NULL)
        return 0;

    // exit
    if (strcmp(argv[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    }

    // cd
    if (strcmp(argv[0], "cd") == 0) {
        const char* path = argv[1] ? argv[1] : getenv("HOME");
        if (chdir(path) != 0)
            perror("cd");
        return 1;
    }

    // help
    if (strcmp(argv[0], "help") == 0) {
        printf("\n--- myshell help ---\n");
        printf("Built-in commands:\n");
        printf("  cd <dir>   - change directory\n");
        printf("  help       - show this message\n");
        printf("  exit       - exit the shell\n");
        printf("  jobs       - list background jobs (coming soon)\n");
        printf("---------------------\n\n");
        return 1;
    }

    // jobs placeholder
    if (strcmp(argv[0], "jobs") == 0) {
        printf("Job control feature not implemented yet.\n");
        return 1;
    }

    return 0;
}
