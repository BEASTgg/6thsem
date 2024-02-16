#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int is_prime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void handle_client(int client_socket) {
    char buffer[1024];
    int num;

    read(client_socket, buffer, sizeof(buffer));
    num = atoi(buffer);

    int result = is_prime(num);

    sprintf(buffer, "%d", result);
    write(client_socket, buffer, sizeof(buffer));

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(12345);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error listening on server socket");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 12345...\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        printf("Accepted connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        handle_client(client_socket);
    }

    close(server_socket);

    return 0;
}