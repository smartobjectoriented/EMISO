#include <iostream>
#include <httpserver.hpp>

#include "webserver/webserver.hpp"
#include "cli/cli.hpp"

#define SERVER_PORT    2375

int main(int argc, char **argv)
{
    int c;
    bool secure = false;
    bool interactive = false;

    while ((c = getopt(argc, argv, "is")) != EOF) {
        switch (c) {
            case 'i':
                interactive = true;
                break;
            case 's':
                secure = true;
                break;
            default:
                // usage();
                exit(1);
                break;
        }
    }

    if (interactive) {
        emiso::Cli cli;
        cli.start();

    } else {
        // TODO - in interactive mode, also start the webserver !
        emiso::WebServer server(SERVER_PORT, secure);
        server.start(true);
    }

    return 0;
}
