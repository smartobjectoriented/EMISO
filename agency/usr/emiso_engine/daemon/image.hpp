
#ifndef EMISO_DAEMON_IMAGE_H
#define EMISO_DAEMON_IMAGE_H

#include <iostream>
#include <map>
#include <filesystem>
#include <string>

namespace emiso {
namespace daemon {

    struct ImageInfo {
        std::string id;
        std::string name;
        size_t size;
        uint64_t date;
    };

    class Image {

    public:
        Image();
        ~Image();

        std::map<std::string, ImageInfo> info();

        // Remove image 'name' from the disk
        void remove(std::string name);
    private:
        // The ID is correspond to the MD5 checksum
        std::string calculateId(const std::string& filePath);

        // Get the date at which the image was create (Unix timestamp)
        int createdTime(const std::string& filePath);

    };
}
}

#endif // EMISO_DAEMON_IMAGE_H
