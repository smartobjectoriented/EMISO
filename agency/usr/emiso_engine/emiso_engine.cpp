#include <httpserver.hpp>

using namespace httpserver;

class hello_world_resource : public http_resource {
 public:
    const std::shared_ptr<http_response> render(const http_request&) {
         return std::shared_ptr<http_response>(new string_response("Hello, World!"));
     }
};

int main() {
    webserver ws = create_webserver(8080)
        .use_ssl()
        .https_mem_key("key.pem")
        .https_mem_cert("cert.pem");

    hello_world_resource hwr;
    ws.register_resource("/hello", &hwr);
    ws.start(true);

    return 0;
}
