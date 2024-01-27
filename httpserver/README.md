# httpserver

A simple HTTP client-server model implemented in C for a POSIX-based system **for educational purposes**. The client in `client.c` connects to the localhost server in `server.c` at a user-specified port number and sends a message. The server then simply acknowledges receipt of the message by sending back a response.

## How to run it?

1. Clone the repository.
2. First run: `make all`
3. Then run: `./server <port number>`
4. Lasltly, in a separate terminal run: `./client 0.0.0.0 <same port number as before>`. Enter a message when prompted.
