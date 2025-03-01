#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *receive_messages(void *socket_desc);

int main() {
    int sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], server_reply[BUFFER_SIZE];
    pthread_t recv_thread;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        return 1;
    }
    printf("Connected to server. Start chatting!\n");

    pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock);

    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        send(sock, message, strlen(message), 0);
    }

    close(sock);
    return 0;
}

void *receive_messages(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char server_reply[BUFFER_SIZE];

    while (1) {
        int recv_size = recv(sock, server_reply, BUFFER_SIZE, 0);
        if (recv_size > 0) {
            server_reply[recv_size] = '\0';
            printf("Server: %s", server_reply);
        }
    }
    return NULL;
}
