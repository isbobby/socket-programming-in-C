/**
 * The server has the following socket workflow
 * 1. socket() 
 * 2. bind() - bind the IP and port
 * 3. listen()
 * 4. accept()
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    // define a simple server return message
    char server_message[256] = "You have reached the server";

    // Creating a TCP socket, one side of the communication
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to this port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen to this port
    listen(server_socket, 5);

    // accept incoming, client socket is the result of listen function
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    shutdown(server_socket, 0);
    return 0;
}