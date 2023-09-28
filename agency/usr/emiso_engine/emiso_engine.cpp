#include <iostream>
#include <httpserver.hpp>

#include "webserver/webserver.hpp"

#define SERVER_PORT    2375

int main(int argc, char **argv)
{
    int c;
    bool secure = false;

    // while ((c = getopt(argc, argv, "p:k:c:sv?")) != EOF) {
    while ((c = getopt(argc, argv, "s")) != EOF) {
        switch (c) {
            case 's':
                secure = true;
                break;
            default:
                // usage();
                exit(1);
                break;
        }
    }

    emiso::WebServer server(SERVER_PORT, secure);
    server.start(true);

    return 0;
}
