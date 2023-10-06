#ifndef EMISO_IMAGE_H
#define EMISO_IMAGE_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

#include "../../daemon/image.hpp"

namespace emiso {
namespace image {

    class ListHandler : public httpserver::http_resource {
    public:

        const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
            std::string payload_str = "";
            Json::Value payload_json;

            // Retrive image info
            auto info = _image.info();

            unsigned idx = 0;
            for (auto it = info.begin(); it != info.end(); ++it) {

                payload_json[idx]["ID"]          = it->second.id;
                payload_json[idx]["ParentId"]    = "";
                payload_json[idx]["RepoTags"][0] = it->second.name;
                payload_json[idx]["Created"]     = it->second.date;
                payload_json[idx]["Size"]        = it->second.size;
                payload_json[idx]["SharedSize"]  = -1;  // Value not set or calculated
                payload_json[idx]["Containers"]  = -1; // Value not set or calculated
                payload_json[idx]["Labels"][0][it->second.name]   = it->second.name;

                idx++;
            }

            Json::StreamWriterBuilder builder;
            payload_str = Json::writeString(builder, payload_json);

            auto response = std::make_shared<httpserver::string_response>(payload_str,
                       httpserver::http::http_utils::http_ok, "application/json");
            return response;
        }

    private:
        daemon::Image _image;

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
