
#include "image.hpp"

namespace emiso {
namespace daemon {

Image::Image() {};

Image::~Image() {};

std::map<std::string, ImageInfo> Image::info()
{
    std::map<std::string, ImageInfo> imagesList;

    // Check if the folder exists
    if (std::filesystem::exists(EMISO_IMAGE_PATH) && std::filesystem::is_directory(EMISO_IMAGE_PATH)) {
        // Iterate through the files in the folder
        for (const auto& entry : std::filesystem::directory_iterator(EMISO_IMAGE_PATH)) {
            if (std::filesystem::is_regular_file(entry)) {
                ImageInfo info;

                info.name = entry.path().filename();
                info.size = std::filesystem::file_size(entry);

                imagesList[info.name] = info;
            }
        }
    } else {
        std::cerr << "Folder '" << EMISO_IMAGE_PATH << "' does not exist or is not a directory." << std::endl;
    }

    return imagesList;
}

void Image::remove(std::string name)
{
    std::filesystem::path filePath = EMISO_IMAGE_PATH + name;

    if (std::filesystem::exists(filePath)) {
        try {
            // Remove the file
            std::filesystem::remove(filePath);

            std::cout << "File removed successfully." << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error removing file: " << e.what() << std::endl;

        }
    } else {
        std::cout << "[WARNING] File '" << filePath << "' does not exists" << std::endl;
    }
}


} // daemon
} // emiso
