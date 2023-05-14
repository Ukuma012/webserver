#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define backlog 3

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

struct sockaddr_in server_address;

int main(int argc, char *argv[]) {
    int socketfd;
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket failed\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8000);

    if(bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        fprintf(stderr, "bind failed\n");
        exit(1);
    }

    if(listen(socketfd, backlog) < 0) {
        fprintf(stderr, "listen failed\n");
        exit(1);
    }

    printf("%s", "Socket is listening\n");

    printf("Socket bound to address %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
    exit(0);
}