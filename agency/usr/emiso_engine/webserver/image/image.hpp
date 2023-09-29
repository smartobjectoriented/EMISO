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

                // ID / Definition of a image ID should be performed. It depends on how portainer uses it !
                payload_json[0]["ID"]       = "sha256:9c7a54a9a43cca047013b82af109fe963fde787f63f9e016fdc3384500c2823d";
                payload_json[0]["ParentId"] = "";
                payload_json[0]["RepoTags"][0] = "SOO.refso3"; // Define a name convention for the 'SO3 Container '
                payload_json[0]["Created"] = 1644009612;  // Created time as returned by ls (number of seconds sinds EPOCH)
                payload_json[0]["Size"] = 13256;  // // get size returned by ls
                payload_json[0]["SharedSize"] = -1;  // Value not set or calculated
                payload_json[0]["VirtualSize"] = 13256;
                payload_json[0]["Containers"] = -1; // Value not set or calculated
                payload_json[0]["Labels"][0] = Json::objectValue;

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
