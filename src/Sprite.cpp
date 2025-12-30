#include"../include/Sprite.h"

Sprite::Sprite(std::string path)
{
    static size_t id_iter = 0;
    id = id_iter++;
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
    uint8_t* raw_image = new uint8_t[img_binary_size];
    
    file.read(reinterpret_cast<char*>(raw_image), img_binary_size);
    size_t offset = 0;
    uint32_t tmp = 0;
    for (size_t i = 0; i < height; ++i)
        {
        image.push_back({});
        for (size_t j = 0; j < width; ++j, offset+=4)
        {
            uint32_t b = raw_image[offset];
            uint32_t g = raw_image[offset + 1];
            uint32_t r = raw_image[offset + 2];
            uint32_t a = raw_image[offset + 3];
            tmp = (b << 24) | (g << 16) | (r << 8) | a;
            image[i].push_back(tmp);
            tmp = 0;
        }
    }
    std::reverse(image.begin(), image.end());
    file.close();
}

void Sprite::rotate(short degrees)
{
    std::vector<std::vector<uint32_t>> tmp_image = image;
    double rads = degToRads(degrees);
    
    
}

uint32_t Sprite::getHeight()
{
    return image.size();
}

uint32_t Sprite::getWidth()
{
    return image[0].size();
}

void Sprite::initWithMatrix(std::vector<std::vector<uint32_t>> _image)
{
    image = _image;
}