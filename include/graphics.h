#pragma once

#include"text.h"
#include<unordered_map>
#include<memory>
#include <math.h>
#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif


class Graphic
{
public:
    friend class Logic;
    void init(uint16_t screen_height, uint16_t screen_width, uint32_t x, uint32_t y);
    void draw(std::shared_ptr<Object> obj);
    void draw(std::shared_ptr<>)
    void clear(uint32_t color);
    void render();
    void stop();
    ~Graphic();
private:
    void setWindowCoords(uint32_t x, uint32_t y);   
    void putpixel(int x, int y, uint32_t color);
    std::vector<std::vector<uint8_t>> window;
    void setMainTexture();
    int* FrameBuffer;
    SDL_Window* SDLWindow;
    SDL_Renderer* Renderer;
    SDL_Texture* Texture;
    uint16_t height;
    uint16_t width;
    uint8_t background_layer = 3;
    uint16_t win_x;
    uint16_t win_y;
};