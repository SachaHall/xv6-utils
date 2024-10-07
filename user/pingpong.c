#include "user/user.h"

int main() {
    int p[2], pid, msg = 0x1234, recv;
    if (pipe(p) < 0) exit(1);
    if ((pid = fork()) > 0) {
        write(p[1], &msg, 1);
        read(p[0], &recv, 1);
        printf("%d: received pong\n", getpid());
    }
    else if (pid == 0){
        read(p[0], &recv, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], &msg, 1);
    }
}