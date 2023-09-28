#include <iostream>

#include "webserver.hpp"

namespace emiso {

    WebServer::WebServer(int port, bool secure)
        : _port(port), _secure(secure) {

        // Use builder to define webserver configuration options
        httpserver::create_webserver cw = httpserver::create_webserver(_port);
        if (secure)
            cw.use_ssl().https_mem_key("key.pem").https_mem_cert("cert.pem");

        // Create webserver using the configured options
        _server = new httpserver::webserver(cw);

        // Registration of the different APIs
        _system    = new system::SytemApi(_server);
        _container = new container::ContainerApi(_server);
        _image     = new image::ImageApi(_server);
        _network   = new network::NetworkApi(_server);
        _volume    = new volume::VolumeApi(_server);

        // Create the default path
        _defaultHandler = new DefaultHandler();
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
