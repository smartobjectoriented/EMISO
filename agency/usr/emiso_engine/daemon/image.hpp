
#ifndef EMISO_DAEMON_IMAGE_H
#define EMISO_DAEMON_IMAGE_H

#include <iostream>
#include <map>
#include <filesystem>


#define EMISO_IMAGE_PATH  "/mnt/ME/"

namespace emiso {
namespace daemon {

    struct ImageInfo {
        std::string name;
        size_t size;
    };

    class Image {

    public:
        Image();
        ~Image();

        // Does not work !
        std::map<std::string, ImageInfo> info();

        // Remove image 'name' from the disk
        void remove(std::string name);
    };
}
}

#endif // EMISO_DAEMON_IMAGE_H
