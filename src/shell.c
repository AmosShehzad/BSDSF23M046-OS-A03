

#include "shell.h"

static char history[MAX_HISTORY][MAX_INPUT];
static int history_count = 0;

/* ----------- Read user input ----------- */
char* get_command(const char* prompt, FILE* stream) {
    printf("%s", prompt);
    fflush(stdout);

    char* line = malloc(MAX_INPUT);
    if (!line) { perror("malloc"); exit(1); }

    int ch, pos = 0;
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (pos < MAX_INPUT - 1)
            line[pos++] = ch;
    }

    if (ch == EOF && pos == 0) {
        free(line);
        return NULL;
    }

    line[pos] = '\0';
    if (strlen(line) > 0)
        save_command_history(line);

    return line;
}

/* ----------- Tokenize input ----------- */
char** parse_input(char* cmdline) {
    if (!cmdline || cmdline[0] == '\0') return NULL;

    char** args = malloc(sizeof(char*) * (MAX_ARGS + 1));
    if (!args) { perror("malloc"); exit(1); }

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

/* ----------- Built-in Commands ----------- */
int handle_builtin(char** argv) {
    if (argv == NULL || argv[0] == NULL)
        return 0;

    if (strcmp(argv[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    }

    if (strcmp(argv[0], "cd") == 0) {
        const char* path = argv[1] ? argv[1] : getenv("HOME");
        if (chdir(path) != 0)
            perror("cd");
        return 1;
    }

    if (strcmp(argv[0], "help") == 0) {
        printf("\n--- myshell help ---\n");
        printf("Built-in commands:\n");
        printf("  cd <dir>\n  help\n  exit\n  history\n  jobs (upcoming)\n");
        printf("---------------------\n\n");
        return 1;
    }

    if (strcmp(argv[0], "history") == 0) {
        print_history();
        return 1;
    }

    if (strcmp(argv[0], "jobs") == 0) {
        printf("Job control not implemented yet.\n");
        return 1;
    }

    return 0;
}

/* ----------- History System ----------- */
void save_command_history(const char* cmd) {
    if (strlen(cmd) == 0) return;

    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count++], cmd, MAX_INPUT);
    } else {
        for (int i = 1; i < MAX_HISTORY; i++)
            strcpy(history[i - 1], history[i]);
        strncpy(history[MAX_HISTORY - 1], cmd, MAX_INPUT);
    }
}

void print_history(void) {
    printf("\n--- Command History ---\n");
    for (int i = 0; i < history_count; i++)
        printf("%d  %s\n", i + 1, history[i]);
    printf("------------------------\n\n");
}

char* get_saved_command(int index) {
    if (index < 1 || index > history_count)
        return NULL;
    return history[index - 1];
}
