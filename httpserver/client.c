#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
    // Hostname and port number need to be provided as a command-line argument
    if (argc < 3) handle_error("args");

    int port = atoi(argv[2]);
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) handle_error("socket");

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        handle_error("Invalid address/ Address not supported");
    }

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_error("Connection Failed");
    }

    char buffer[256] = {0};
    printf("Please enter the message: ");
    memset(buffer, 0, 256);
    fgets(buffer, 255, stdin);

    if (write(socketfd, buffer, strlen(buffer)) < 0) {
        handle_error("write");
    }

    memset(buffer, 0, 256);
    if (read(socketfd, buffer, 255) < 0) {
        handle_error("read");
    }

    printf("%s\n", buffer);
    close(socketfd);

    return 0;
}
