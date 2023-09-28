#ifndef EMISO_IMAGE_H
#define EMISO_IMAGE_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

namespace emiso {

    namespace image {

        class ListHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                std::string payload_str = "";
                Json::Value payload_json;

                payload_json["ID"]       = "2ff11d3f-c408-493e-b170-908919f68044";
                payload_json["ParentId"] = "";

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };

        class ImageApi {
        public:
            // Constructor
            ImageApi(httpserver::webserver *server);

            // Destructor
            ~ImageApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different 'list' routes
            ListHandler *_listHandler;

        };
    }
}

#endif /* EMISO_IMAGE_H */
