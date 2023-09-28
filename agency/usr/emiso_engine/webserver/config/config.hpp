
#ifndef EMISO_CONFIG_H
#define EMISO_CONFIG_H

#include <iostream>

namespace emiso {

    class config {
    public:
        static const std::string plaftrom_name;
        static const std::string comp_name;
        static const std::string version;
        static const std::string api_version;
        static const bool        experimental;
    };
}

#endif // EMISO_CONFIG_H
