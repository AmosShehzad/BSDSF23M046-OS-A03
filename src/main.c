

#include "shell.h"

int main(void) {
    char* cmdline;
    char** argv;

    while ((cmdline = get_command(PROMPT, stdin)) != NULL) {
        if ((argv = parse_input(cmdline)) != NULL) {
            // Check if built-in command
            if (!handle_builtin(argv))
                execute_command(argv);

            // Free memory
            for (int i = 0; argv[i] != NULL; i++)
                free(argv[i]);
            free(argv);
        }
        free(cmdline);
    }

    printf("\nShell exited.\n");
    return 0;
}
