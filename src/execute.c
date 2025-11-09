

#include "shell.h"

/* -------------------- Execute External Command -------------------- */
int execute_command(char** argv) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // Child process
        execvp(argv[0], argv);
        perror("myshell");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
