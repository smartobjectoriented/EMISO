#ifndef EMISO_VOLUME_H
#define EMISO_VOLUME_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

namespace emiso {

    namespace volume {

        class ListHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                std::string payload_str = "[]";

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };

        class VolumeApi {
        public:
            // Constructor
            VolumeApi(httpserver::webserver *server);

            // Destructor
            ~VolumeApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different 'list' routes
            ListHandler *_listHandler;

        };
    }
}

#endif /* EMISO_VOLUME_H */
