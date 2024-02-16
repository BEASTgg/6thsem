#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(12345);

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int number;

    printf("Enter a number to check if it's prime: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(client_socket, buffer, sizeof(buffer));

    read(client_socket, buffer, sizeof(buffer));
    int result = atoi(buffer);

    printf("The result is: %d\n", result);

    close(client_socket);

    return 0;
}