#include "user/user.h"

int main() {
    int pid, p[2], stat, input, output;
    if (pipe(p) < 0) exit(1);
    input = p[0];

    for (int i = 2; i<=35; ++i) {
        write(p[1], &i, 4);
    }
    close(p[1]);
    if ((pid = fork()) > 0) {
        wait(0);
        exit(0);
    }
    while (1) {
        int prime, num, newPipe[2];
        read(input, &prime, 4);
        printf("prime %d\n", prime);
        sleep(1);
        pipe(newPipe);
        output = newPipe[1];
        int next = 0;
        while (read(input, &num, 4)) {
            if (num % prime == 0) continue;
            next = 1;
            write(output, &num, 4);
        }
        close(output);
        close(input);
        input = newPipe[0];
        if (!next) exit(0);
        if ((pid = fork()) > 0) {
            wait(&stat);
            exit(0);
        }
    }

}