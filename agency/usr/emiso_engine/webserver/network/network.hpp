#ifndef EMISO_NETWORK_H
#define EMISO_NETWORK_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

namespace emiso {

    namespace network {

        class ListHandler : public httpserver::http_resource {
        public:

            // In emiso, network is not supported --> return an empty list !
            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                std::string payload_str = "[]";

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };

        class NetworkApi {
        public:
            // Constructor
            NetworkApi(httpserver::webserver *server);

            // Destructor
            ~NetworkApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different 'list' routes
            ListHandler *_listHandler;

        };
    }
}

#endif /* EMISO_NETWORK_H */
