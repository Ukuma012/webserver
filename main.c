#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    int socketfd;
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf(stderr, "socket failed\n");
        exit(1);
    }
    fprintf("%s", "Hello World\n");
    exit(0);
}