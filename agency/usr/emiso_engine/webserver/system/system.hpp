#ifndef EMISO_SYSTEM_H
#define EMISO_SYSTEM_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>
#include <sys/utsname.h>

#include "../config/config.hpp"

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
                struct utsname unameData;
                int response_code = httpserver::http::http_utils::http_ok;

                if (uname(&unameData) != -1) {

                    payload_json["Platform"]["name"] = config::plaftrom_name;
                    payload_json["Components"][0]["name"]    = config::comp_name;
                    payload_json["Components"][0]["version"] = config::version;
                    payload_json["Version"]       = config::version;
                    payload_json["ApiVersion"]    = config::api_version;
                    payload_json["MinAPIVersion"] = config::api_version;

                    // Get info directly from the system
                    payload_json["Os"]   = unameData.sysname;
                    payload_json["Arch"] = unameData.machine;
                    payload_json["KernelVersion"] = unameData.release;

                    payload_json["Experimental"] = config::experimental;

                    // not implemented yet !
                    // payload_json["GitCommit"]
                    // payload_json["GoVersion"]
                    // payload_json["BuildTime"]

                } else {
                    response_code = httpserver::http::http_utils::http_internal_server_error;
                    payload_json["message"] = "Something went wrong";
                }

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                                                  response_code, "application/json");
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