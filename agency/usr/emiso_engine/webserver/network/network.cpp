
#include "network.hpp"

namespace emiso {

    namespace network {

        NetworkApi::NetworkApi(httpserver::webserver *server)
            : _server(server) {
                std::string path  = "/networks";

            // Create routes and handlers
            _listHandler = new ListHandler();

            _server->register_resource(path, _listHandler);
            _server->register_resource("/v[1-9]+.[0-9]+" + path, _listHandler);
        }

        NetworkApi::~NetworkApi() {}
    }
}
