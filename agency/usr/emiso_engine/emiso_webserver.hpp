

#ifndef EMISO_WEBSERVER_H
#define EMISO_WEBSERVER_H

#include <httpserver.hpp>
#include <json/json.h>


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
        auto response = std::make_shared<httpserver::string_response>("Message received!\n");
        return response;
    }
};

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

    	std::cout << "Payload: " << std::endl;
    	std::cout << payload_str << std::endl;
    	std::cout << std::endl;

		auto response = std::make_shared<httpserver::string_response>(payload_str,
                   httpserver::http::http_utils::http_ok, "application/json");
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

	    // Handler for the different routes
	    PingHandler     *_pinghandler;
	    SysInfoHandler  *_sysInfoHandler;
	    DefaultHandler  *_defaultHandler;

	};
}

#endif /* EMISO_WEBSERVER_H */
