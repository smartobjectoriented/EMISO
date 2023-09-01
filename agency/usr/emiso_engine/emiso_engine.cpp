
#if 1 // HTTP server

#include <iostream>
#include <httpserver.hpp>

class MyHandler : public httpserver::http_resource {
public:
    const std::shared_ptr<httpserver::http_response> render(const httpserver::http_request& req) {
        std::cout << "Received message on port 8080:" << std::endl;
        std::cout << "Method: " << req.get_method() << std::endl;
        std::cout << "Path: " << req.get_path() << std::endl;
        std::cout << "Headers:" << std::endl;
        for (const auto& header : req.get_headers()) {
            std::cout << "    " << header.first << ": " << header.second << std::endl;
        }
        std::cout << "Body: " << req.get_content() << std::endl;

        // Respond with a simple message
        auto response = std::make_shared<httpserver::string_response>("Message received!");
        return response;
    }
};


int main() {
    httpserver::webserver server = httpserver::create_webserver(8080)
        .use_ssl()
        .https_mem_key("key.pem")
        .https_mem_cert("cert.pem");

    // Create and add the handler
    MyHandler  handler;
    server.register_resource("^/.*$", &handler);

    std::cout << "Server started on port 8080." << std::endl;

    // Start the server
    server.start(true);

    return 0;
}
#else // tcp/socket version

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket to address." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    listen(serverSocket, 5);

    std::cout << "Server started on port 8080." << std::endl;

    while (true) {
        // Accept incoming connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        // Read data from client
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            std::cerr << "Error reading from client." << std::endl;
        } else {
            // Print received message
            std::cout << "Received message from client:" << std::endl;
            std::cout.write(buffer, bytesRead) << std::endl;

            // Send response back to client
            const char* response = "Message received!";
            send(clientSocket, response, strlen(response), 0);
        }

        // Close client socket
        close(clientSocket);
    }

    // Close server socket
    close(serverSocket);

    return 0;
}
#endif
