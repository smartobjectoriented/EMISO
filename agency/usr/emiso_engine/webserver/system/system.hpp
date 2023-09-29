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

                response->with_header("Api-Version",         config::api_version);
                response->with_header("Builder-Version",     config::version);
                if (config::experimental)
                    response->with_header("Docker-Experimental", "true");
                else
                    response->with_header("Docker-Experimental", "false");
                response->with_header("Swarm",               config::swarm);
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

                payload_json["ID"]         = "2ff11d3f-c408-493e-b170-908919f68044"; // WARNING - should be unique
                payload_json["Containers"] = 2;
                payload_json["ContainersRunning"] = 1;
                payload_json["ContainersPaused"] = 0;
                payload_json["ContainersStopped"] = 0;
                payload_json["Images"] = 3;

                // WARNING - hardcoded values got from Docker answer of JMI PC
                payload_json["Driver"] = "overlay2";
                payload_json["DriverStatus"][0].append("Backing Filesystem");
                payload_json["DriverStatus"][0].append("extfs");
                payload_json["DriverStatus"][1].append("Supports d_type");
                payload_json["DriverStatus"][1].append("true");
                payload_json["DriverStatus"][2].append("Using metacopy");
                payload_json["DriverStatus"][2].append("false");
                payload_json["DriverStatus"][3].append("Native Overlay Diff");
                payload_json["DriverStatus"][3].append("true");
                payload_json["DriverStatus"][4].append("userxattr");
                payload_json["DriverStatus"][4].append("false");

                payload_json["DockerRootDir"] = "/var/lib/docker"; // default value on Linux
                payload_json["Plugins"] = Json::objectValue;

                // Set these values to false as not supported/handled by emiso
                payload_json["MemoryLimit"] = "false";
                payload_json["SwapLimit"] = "false";
                payload_json["CpuCfsPeriod"] = "false";
                payload_json["CpuCfsQuota"] = "false";
                payload_json["CPUShares"] = "false";
                payload_json["CPUSet"] = "false";
                payload_json["PidsLimit"] = "false";
                payload_json["OomKillDisable"] = "false";
                payload_json["IPv4Forwarding"] = "false";
                payload_json["BridgeNfIptables"] = "false";
                payload_json["BridgeNfIp6tables"] = "false";
                payload_json["Debug"] = "false";

                payload_json["SystemTime"] = "2017-08-08T20:28:29.06202363Z"; // GET REAL/current system time
                payload_json["LoggingDriver"] = "json-file"; // WARNING - hardcoded values got from Docker answer of JMI PC
                payload_json["CgroupDriver"] = "none";
                payload_json["CgroupVersion"] = 1; // Default docker value
                payload_json["NEventsListener"] = 0;

                // Get these information for system !!!!!!
                payload_json["KernelVersion"] = "5.10";
                payload_json["OperatingSystem"] = "Buildroot 2022.02.5";
                payload_json["OSVersion"]    = "-gd5d03f1ce-dirty";
                payload_json["OSType"] = "linux";
                payload_json["Architecture"] = "aarch64";

                payload_json["NCPU"] = 1;
                payload_json["MemTotal"] = 536870912; // To check !
                payload_json["IndexServerAddress"] = "https://index.docker.io/v1/";
                payload_json["RegistryConfig"] = Json::objectValue;
                payload_json["GenericResources"] = Json::arrayValue;

                payload_json["HttpProxy"] =  "";    // use  'HTTP_PROXY' env variable
                payload_json["HttpsProxy"] =  "";  // use 'HTTPS_PROXY' env variable
                payload_json["NoProxy"] =  "";   // use 'NO_PROXY' env variable
                payload_json["Name"] =  "agency";   // Host name
                payload_json["Labels"] = Json::arrayValue;
                payload_json["ExperimentalBuild"] = config::experimental;
                payload_json["ServerVersion"] = "24.0.5";
                payload_json["ServerVersion"] = Json::objectValue;
                payload_json["DefaultRuntime"] = "";

                payload_json["Swarm"]["NodeID"] = "";
                payload_json["Swarm"]["NodeAddr"] = "";
                payload_json["Swarm"]["LocalNodeState"] = "inactive";
                payload_json["Swarm"]["ControlAvailable"] = "false";
                payload_json["Swarm"]["Error"] = "";
                payload_json["Swarm"]["RemoteManagers"] = Json::objectValue;

                payload_json["LiveRestoreEnabled"] = false;
                payload_json["Isolation"] = "VT";  // TODO - platform specific
                payload_json["SecurityOptions"] = Json::arrayValue;

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