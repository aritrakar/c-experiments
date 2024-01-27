# webserver

A simple webserver implemented in C for a POSIX-based system **for educational purposes**. The server listens for file requests and returns a requested file, if found. The user acts as the client here instead of another machine or process.

## How to run it?

1. Clone the repository.
2. Run the following in one terminal: `make server && ./server`

3. In a separate directory, run `wget localhost:8080/<filename>.html`. Note that you'll only get the file with `filename.html` back if it is defined in the `webserver` directory.
