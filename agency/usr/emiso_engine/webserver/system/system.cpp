
#include "system.hpp"

namespace emiso {
    namespace system {

        SytemApi::SytemApi(httpserver::webserver *server)
            : _server(server) {

            // Create routes and handlers
            _pinghandler    = new PingHandler();
            _sysInfoHandler = new SysInfoHandler();
            _getVersionHandler = new GetVersionHandler();

            _server->register_resource("/_ping", _pinghandler);
            _server->register_resource("/v[1-9]+.[0-9]+/_ping", _pinghandler);
            _server->register_resource("/v[1-9]+.[0-9]+/info",  _sysInfoHandler);
            _server->register_resource("/info",  _sysInfoHandler);
            _server->register_resource("/version", _getVersionHandler);
            _server->register_resource("/v[1-9]+.[0-9]+/version", _getVersionHandler);
        }

        SytemApi::~SytemApi() {}
    }
}
