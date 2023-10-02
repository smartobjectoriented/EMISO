
#include "image.hpp"

namespace emiso {

    namespace image {

        ImageApi::ImageApi(httpserver::webserver *server)
            : _server(server) {
                std::string path  = "/images";

            // Create routes and handlers
            _listHandler = new ListHandler();

            _server->register_resource(path + "/json", _listHandler);
            _server->register_resource("/v[1-9]+.[0-9]+" + path + "/json", _listHandler);
        }

        ImageApi::~ImageApi() {}
    }
}
