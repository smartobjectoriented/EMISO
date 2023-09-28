#ifndef EMISO_SYSTEM_H
#define EMISO_SYSTEM_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

namespace emiso {
    namespace system {

        class PingHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                // Respond is a simple 'OK'
                auto response = std::make_shared<httpserver::string_response>("OK");
                return response;
            }

            const std::shared_ptr<httpserver::http_response> render_HEAD(const httpserver::http_request &req) {
                auto response = std::shared_ptr<httpserver::http_response>(new httpserver::string_response(""));

                response->with_header("Api-Version",         "1.43");
                response->with_header("Builder-Version",     "1.0");
                response->with_header("Docker-Experimental", "false");
                response->with_header("Swarm",               "inactive");
                response->with_header("Cache-Control",       "no-cache, no-store, must-revalidate");
                response->with_header("Pragma",              "no-cache");

                return response;
            }
        };

        class SysInfoHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {

                std::string payload_str = "";
                Json::Value payload_json;

                payload_json["ID"]         = "2ff11d3f-c408-493e-b170-908919f68044";
                payload_json["Containers"] = 2;

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };

        class GetVersionHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {

                std::string payload_str = "";
                Json::Value payload_json;

                payload_json["Platform"]["name"]  = "emiso";
                payload_json["Version"] =         1;

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };


        class SytemApi {
        public:
            // Constructor
            SytemApi(httpserver::webserver *server);

            // Destructor
            ~SytemApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different routes
            PingHandler     *_pinghandler;
            SysInfoHandler  *_sysInfoHandler;
            GetVersionHandler *_getVersionHandler;
        };
    }
}

#endif /* EMISO_SYSTEM_H */