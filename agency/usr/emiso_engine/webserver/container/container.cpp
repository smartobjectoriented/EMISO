
#include "container.hpp"

namespace emiso {

    namespace container {

        ContainerApi::ContainerApi(httpserver::webserver *server)
            : _server(server) {
                std::string path  = "/containers";

            // Create routes and handlers
            _listHandler = new ListHandler();

            _server->register_resource(path + "/json", _listHandler);
        }

        ContainerApi::~ContainerApi() {}

    }
}
