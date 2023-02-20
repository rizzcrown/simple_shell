#include "main.h"

void exit_shell() {
    exit(0);
}

void env_shell() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}