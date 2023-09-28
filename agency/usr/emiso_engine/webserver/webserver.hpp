

#ifndef EMISO_WEBSERVER_H
#define EMISO_WEBSERVER_H

#include <httpserver.hpp>

#include "system/system.hpp"
#include "container/container.hpp"
#include "image/image.hpp"
#include "network/network.hpp"
#include "volume/volume.hpp"

class DefaultHandler : public httpserver::http_resource {
public:
    const std::shared_ptr<httpserver::http_response> render(const httpserver::http_request& req) {
        std::cout << "Received message on port " << 2375 << ":" << std::endl;
        std::cout << "Method: " << req.get_method() << std::endl;
        std::cout << "Path: " << req.get_path() << std::endl;
        std::cout << "Headers:" << std::endl;
        for (const auto& header : req.get_headers()) {
            std::cout << "    " << header.first << ": " << header.second << std::endl;
        }
        std::cout << "Body: " << req.get_content() << std::endl;

        // Respond with a simple message
        auto response = std::make_shared<httpserver::string_response>("Path '%s' not implemented\n", req.get_path());
        return response;
    }
};

namespace emiso {

    class WebServer {
    public:
        // Constructor
        WebServer(int port, bool secure);

        // Destructor
        ~WebServer();

        // Member function to start the server
        void start(bool blocking = false);

        // Member function to stop the server
        // void stop();

    private:
        int _port;
        bool _secure;
        httpserver::webserver *_server;

        // Different services
        system::SytemApi *_system;
        container::ContainerApi *_container;
        image::ImageApi *_image;
        network::NetworkApi *_network;
        volume::VolumeApi *_volume;

        // Default handler - not registered routes
        DefaultHandler  *_defaultHandler;

    };
}

#endif /* EMISO_WEBSERVER_H */
