#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main() {
    // Creating a TCP socket, one side of the communication
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify another socket to connect to
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to another socket
    int connection_status = connect(network_socket, (struct sockaddr *) &client_address, sizeof(client_address));
    if (connection_status == -1){
        printf("There was an error making a connection to the remote socket\n");
    }
    
    // receive data from the socket and print it out
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    printf("The server sends %s\n", server_response);

    // close socket afterwards https://www.gnu.org/software/libc/manual/html_node/Closing-a-Socket.html
    shutdown(network_socket, 0);
    if (connection_status == -1){
        printf("There was an error closing the connection\n");
    } else if (connection_status == 0) {
        printf("Connection closed\n");
    }

    return 0;
}
