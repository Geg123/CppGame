#include"vector"
#include"iostream"
#include"fstream"
#include"geometry.h"

class Sprite
{
private:
    size_t id;
    std::vector<std::vector<uint32_t>> image;
public:
    Sprite(std::string path);
    Sprite(){}
    void initWithMatrix(std::vector<std::vector<uint32_t>> _image);
    void rotate(short degrees);
    size_t getId(){return id;}
    uint32_t getHeight();
    uint32_t getWidth();
    const std::vector<std::vector<uint32_t>>& getImage(){return image;}
};