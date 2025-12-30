#include"../include/text.h"

Text::Text(std::string _text)
{
    text = _text;
    font = TTF_OpenFont("times.ttf", 24);
    textSurface = TTF_RenderText_Solid(font, text, text.size(), SDLTextColor);
    size_t height = textSurface->h;
    size_t width = textSurface->w;
    size_t pitch = textSurface->pitch;
    int* buffer = (int*)textSurface->pixels;
    std::vector<std::vector<uint32_t>> image;
    size_t offset = 0;
    uint32_t tmp_color = 0;
    for (size_t i = 0; i < height; ++i)
        {
        image.push_back({});
        for (size_t j = 0; j < width; ++j)
        {
            tmp_color = *(buffer + j + i * pitch);
            image[i].push_back(tmp_color);
            tmp_color = 0;
        }
    }
}