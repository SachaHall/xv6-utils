#include "user/user.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

char* readline() {
    char* buf = malloc(1024), *p;
    p = buf;
    char c;
    int read_something = 0;
    while (read(0, &c, 1) > 0) {
        read_something = 1;
        if (c == '\n') {
            *p = 0;
            return buf;
        }
        *p++ = c;
    }
    *p = 0; // add null terminator
    if (!read_something) {
        buf = 0;
    }
    return buf;
}
void run_command(char *command, char *params, char *stdin_params) {
    int pid, stat;
    if ((pid = fork()) < 0) {
        printf("xargs: fork failed");
        return;
    }
    if (!pid) {
        char *args[4] = {command, params, stdin_params, 0};
        exec(command, args);
    }
    else {
        wait(&stat);
    }
}
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("ERROR: incorrect number of parameters\n");
        exit(0);
    }
    char *line;
    while ((line = readline()) != 0) {
        run_command(argv[1], argv[2], line);
    }
}

