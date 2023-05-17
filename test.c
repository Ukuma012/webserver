#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open("./public/response.txt", O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "open failed\n");
        exit(1);
    }

    char response[4096];
    ssize_t read_bytes;
    read_bytes = read(fd, response, sizeof(response) - 1);
    if (read_bytes < 0)
    {
        fprintf(stderr, "read failed\n");
        exit(1);
    }

    response[read_bytes] = '\0';
    printf("%s\n", response);

    close(fd);

    return 0;
}