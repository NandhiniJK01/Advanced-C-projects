#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024
#define MAX_PATTERNS 3

const char *attack_patterns[MAX_PATTERNS] = {"malware", "hacking", "attack"};

void analyze_packet(const char *packet) {
    for (int i = 0; i < MAX_PATTERNS; i++) {
        if (strstr(packet, attack_patterns[i]) != NULL) {
            printf("[ALERT] Intrusion detected: %s\n", attack_patterns[i]);
            return;
        }
    }
    printf("Packet is safe.\n");
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    printf("Intrusion Detection System is running on port %d...\n", PORT);

    while (1) {
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len > 0) {
            buffer[recv_len] = '\0';
            printf("Received Packet: %s\n", buffer);
            analyze_packet(buffer);
        }
    }

    close(sockfd);
    return 0;
}
