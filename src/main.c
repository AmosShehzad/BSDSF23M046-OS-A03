

#include "shell.h"

int main(void) {
    char* cmdline;
    char** argv;

    while ((cmdline = get_command(PROMPT, stdin)) != NULL) {
        // Handle !n (re-execute from history)
        if (cmdline[0] == '!' && strlen(cmdline) > 1) {
            int index = atoi(cmdline + 1);
            char* recalled = get_saved_command(index);
            if (recalled) {
                printf("Re-executing: %s\n", recalled);
                free(cmdline);
                cmdline = strdup(recalled);
            } else {
                printf("No such command in history.\n");
                free(cmdline);
                continue;
            }
        }

        if ((argv = parse_input(cmdline)) != NULL) {
            if (!handle_builtin(argv))
                execute_command(argv);

            for (int i = 0; argv[i] != NULL; i++)
                free(argv[i]);
            free(argv);
        }

        free(cmdline);
    }

    printf("\nShell exited.\n");
    return 0;
}
