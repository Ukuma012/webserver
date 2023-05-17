#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

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
struct sockaddr_in client_address;

int main(int argc, char *argv[])
{
    int socketfd;
    int client_socketfd;
    socklen_t len = sizeof(client_address);

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "socket failed\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8000);

    if (bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        fprintf(stderr, "bind failed\n");
        exit(1);
    }

    if (listen(socketfd, backlog) < 0)
    {
        fprintf(stderr, "listen failed\n");
        exit(1);
    }

    while (1)
    {
        if ((client_socketfd = accept(socketfd, (struct sockaddr *)&client_address, &len)) > 0)
        {
            char recvmsg[4096];
            int recvmsg_len = sizeof(recvmsg) - 1;
            int recv_len = recv(client_socketfd, recvmsg, recvmsg_len, 0);

            if (recv_len < 0)
            {
                fprintf(stderr, "recv failed\n");
                exit(1);
            }
            recvmsg[recv_len] = '\0';

            char *request = strdup(recvmsg);
            char *token;

            while ((token = strsep(&request, "\r\n")) != NULL)
            {
                printf("%s\n", token);
                fflush(stdout);
            }

            free(request);
            break;
        }
    }

    int response_fd = open("./public/response.txt", O_RDONLY);
    if (response_fd < 0)
    {
        fprintf(stderr, "open failed\n");
        exit(1);
    }

    char response[4096];
    ssize_t read_bytes;
    read_bytes = read(response_fd, response, sizeof(response) - 1);
    if (read_bytes < 0)
    {
        fprintf(stderr, "read failed\n");
        exit(1);
    }

    response[read_bytes] = '\0';
    printf("%s\n", response);

    int response_len = strlen(response);
    ssize_t total_sent = 0;
    ssize_t sent_bytes;
    while (total_sent < response_len)
    {
        sent_bytes = send(client_socketfd, response + total_sent, response_len - total_sent, 0);
        if (sent_bytes < 0)
        {
            fprintf(stderr, "send failed\n");
            exit(1);
        }
        total_sent += sent_bytes;
    }

    close(response_fd);

    exit(0);
}