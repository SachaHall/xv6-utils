#include "user/user.h"
int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("ERROR: not enough parameters\n");
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}
