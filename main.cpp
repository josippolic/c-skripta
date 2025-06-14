#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    std::string target_ip;
    std::cout << "Unesi IP adresu mete: ";
    std::cin >> target_ip;

    for (int port = 1; port <= 1024; ++port) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, target_ip.c_str(), &addr.sin_addr);

        // Timeout opcionalno
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100 ms
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

        int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        if (result == 0) {
            std::cout << "[+] Otvoren port: " << port << std::endl;
        }
        close(sock);
    }

    return 0;
}
