#ifndef EMISO_CONTAINER_H
#define EMISO_CONTAINER_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>


namespace emiso {

    namespace container {

        class ListHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                std::string payload_str = "";
                Json::Value payload_json;

                payload_json["ID"]    = "2ff11d3f-c408-493e-b170-908919f68044";
                payload_json["Image"] = "soo.refSO3";

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };

        class ContainerApi {
        public:
            // Constructor
            ContainerApi(httpserver::webserver *server);

            // Destructor
            ~ContainerApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different 'container' routes
            ListHandler *_listHandler;

        };

    }

}

#endif /* EMISO_CONTAINER_H */