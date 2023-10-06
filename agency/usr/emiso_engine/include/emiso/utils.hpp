#ifndef EMISO_UTILS_H
#define EMISO_UTILS_H

#include <iostream>

namespace emiso {

    struct SystemInfo {
        std::string kernel_version;
        std::string os;
        std::string os_version;
        std::string os_type;
        std::string arch;
    };

    class Utils {

    public:
        static Utils& getInstance() {
            // Create the instance if it doesn't exist
            static Utils instance;
            return instance;
        }

        SystemInfo getInfo();

        // Return the current system time, n  RFC 3339 format with nano-seconds
        std::string getSystemTime();

    private:
        SystemInfo _info;

        Utils();
        ~Utils();

        // Make copy constructor and assignment operator private to prevent copying
        Utils(const Utils&) = delete;
        Utils& operator=(const Utils&) = delete;
    };

} // emiso

#endif // EMISO_UTILS_H




