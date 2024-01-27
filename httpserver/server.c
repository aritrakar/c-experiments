#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG 5
#define BUFFER_SIZE 256
#define RESPONSE "Received message"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
    if (argc < 2) handle_error("port");

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) handle_error("socket");

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(atoi(argv[1])),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        handle_error("bind");

    if (listen(socket_fd, BACKLOG) == -1)
        handle_error("listen");

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_fd < 0) handle_error("client connection");

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if (read(client_fd, buffer, BUFFER_SIZE - 1) < 0)
        handle_error("reading");

    if (write(client_fd, RESPONSE, strlen(RESPONSE)) < 0)
        handle_error("writing");

    close(client_fd);
    close(socket_fd);

    return 0;
}
