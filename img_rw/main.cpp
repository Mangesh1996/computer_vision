#include <iostream>
#include "img_process.h"

#include <filesystem>

namespace fs = std::filesystem;
int main()
{
    std::string img_path = "source";
    for (const auto &entry : fs::directory_iterator(img_path))
    {
        std::string file_extension = entry.path().extension();
        if (file_extension == ".jpg")
        {
            if (!display_img(entry.path()))
            {
                std::cerr << "Failed to process image\n";
            }
            else if 
                (file_extension == ".mp4")
                {
                    return 0;
                }
        }
    }

    return 0;
}