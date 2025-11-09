

#include "shell.h"

int execute_command(char** argv) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        execvp(argv[0], argv);
        perror("myshell");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
