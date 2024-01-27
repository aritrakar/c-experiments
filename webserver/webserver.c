#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <unistd.h>

#define BACKLOG 10
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
    // Create a simple TCP socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Default protocol
    if (socket_fd == -1) handle_error("socket");

    // Bind the socket to an address.
    // Using sockaddr_in ("in" for "internet") for IPv4 address
    struct sockaddr_in addr = {
        AF_INET,
        /**
         * NOTE: This is actually port 8080. For some reason the
         * order of the bytes is opposite of the actual value of
         * 8080 in hexadecimal.
        */
        0x901f,
        0
    };
    // int bindfd = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    int bindfd = bind(socket_fd, &addr, sizeof(addr));
    if (bindfd == -1) handle_error("bind");

    // Now we can listen. It initializes a socket for incoming connections
    listen(socket_fd, BACKLOG);

    // Accept a connection
    int client_fd = accept(socket_fd, 0, 0);

    // Receive client data. Gets a HTTP request
    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    // GET /somefile.html
    char* f = buffer + 5; // Skip first 5 bytes to get the file name from the request header
    *strchr(f, ' ') = 0; // Change the first space to a null terminator

    // Open the file
    int opened_fd = open(f, O_RDONLY);

    // And send it
    sendfile(client_fd, opened_fd, 0, 256);

    // Close file descriptors and cleanup
    close(opened_fd);
    close(client_fd);
    close(socket_fd);

    return 0;
}
