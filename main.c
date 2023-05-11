#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// struct in_addr
// {
//         ip_addr_t s_addr;
// };

//  struct sockaddr_in {
//      unsigned char  sin_len;
//      unsigned char  sin_family;
//      unsigned short sin_port;
//      struct in_addr sin_addr;
//      unsigned char  sin_zero[8];

// };

struct sockaddr_in socketaddress;

int main(int argc, char *argv[]) {
    int socketfd;
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket failed\n");
        exit(1);
    }

    memset(&socketaddress, 0, sizeof(socketaddress));
    socketaddress.sin_family = AF_INET;

    printf("%d\n", socketfd);
    exit(0);
}