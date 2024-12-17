#include  <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/un.h>
#include <unistd.h>


#include <sys/socket.h>
#include <ctype.h>

#define SOCKET_PATH "socket_path"
#define BUFFER_SIZE 1024


int main()
{
    int server_fd, client_fd;
    struct sockaddr_un address;
    char buffer[BUFFER_SIZE];

    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Error in creating");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    unlink(SOCKET_PATH);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) == -1)
    {
        perror("Error in accepting");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("...\n");

    if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
        perror("Error in connection");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("> connected OK\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            break;
        }
        for (int i = 0; i < bytes_read; i++) {
            buffer[i] = toupper(buffer[i]);
        }

        printf("> %s\n", buffer);
    }

    printf("> Exited OK\n");

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}
