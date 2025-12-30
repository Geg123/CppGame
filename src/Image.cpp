#include"/programming/git/CppGame/include/graphics/Image.h"

Image::Image(size_t height, size_t width, uint8_t bpp, uint8_t* arr)
{
    size_t rwidth = width * bpp;
    size_t offset = 0;
    //size_t base = 0;
    for (size_t i = 0; i < height; ++i)
        {
        image.push_back({});
        for (size_t j = 0; j < width; ++j, offset+=bpp)
        {
            image[i].push_back(sf::Color(arr[offset + 2], arr[offset + 1], arr[offset], arr[offset + 3]));
        }
    }
    std::reverse(image.begin(), image.end());
}

Image Image::createImage(std::string path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file!" << std::endl;
        system("pause");
    }
    uint8_t header[18];
    file.read(reinterpret_cast<char*>(header), 18);
    size_t bpp = (int)header[16] / 8;
    size_t width = header[13] << 8 | header[12];
    size_t height = header[15] << 8 | header[14];
    size_t img_binary_size = bpp * width * height;
    uint8_t* image = new uint8_t[img_binary_size];
    
    file.read(reinterpret_cast<char*>(image), img_binary_size);
    Image img(height, width, bpp, image);
    file.close();
    return img;
}



