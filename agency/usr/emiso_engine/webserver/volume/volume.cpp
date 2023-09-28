
#include "volume.hpp"

namespace emiso {

    namespace volume {

        VolumeApi::VolumeApi(httpserver::webserver *server)
            : _server(server) {
                std::string path  = "/volumes";

            // Create routes and handlers
            _listHandler = new ListHandler();

            _server->register_resource(path, _listHandler);
        }

        VolumeApi::~VolumeApi() {}
    }
}
