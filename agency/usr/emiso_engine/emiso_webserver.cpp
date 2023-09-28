#include <iostream>

#include "emiso_webserver.hpp"

namespace emiso {

    WebServer::WebServer(int port, bool secure)
        : _port(port), _secure(secure) {

        // Use builder to define webserver configuration options
        httpserver::create_webserver cw = httpserver::create_webserver(_port);
        if (secure)
            cw.use_ssl().https_mem_key("key.pem").https_mem_cert("cert.pem");

        // Create webserver using the configured options
        _server = new httpserver::webserver(cw);

        // Create routes and handlers
        _pinghandler    = new PingHandler();
        _defaultHandler = new DefaultHandler();
        _sysInfoHandler = new SysInfoHandler();

        _server->register_resource("/_ping", _pinghandler);
        _server->register_resource("/info",  _sysInfoHandler);
        _server->register_resource("^/.*$",  _defaultHandler);
    }

    WebServer:: ~WebServer() {}

    void WebServer::start(bool blocking)
    {
        // Start the server
        std::cout << "Server started on port " << _port;
        if (_secure)
                std::cout << " (HTTPS/TLS mode ON)";
        std::cout << std::endl;

        _server->start(blocking);
    }
}
