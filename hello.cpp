#include<fstream>
#include<vector>
#include<algorithm>
#include<iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int* FrameBuffer;
SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Texture* Texture;
static int gDone;
const int WINDOW_WIDTH = 1920 / 2;
const int WINDOW_HEIGHT = 1080 / 2;
std::vector<std::vector<unsigned int>> image;

void putpixel(int x, int y, int color)
{
    if (x < 0 ||
        y < 0 ||
        x >= WINDOW_WIDTH ||
        y >= WINDOW_HEIGHT)
    {
        return;
    }
    FrameBuffer[y * WINDOW_WIDTH + x] = color;
}

bool setMainTexture()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            return false;
        }
        if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
        {
            return false;
        }
    }

    char* pix;
    int pitch;

    SDL_LockTexture(gSDLTexture, NULL, (void**)&pix, &pitch);
    for (int i = 0, sp = 0, dp = 0; i < WINDOW_HEIGHT; i++, dp += WINDOW_WIDTH, sp += pitch)
        memcpy(pix + sp, gFrameBuffer + dp, WINDOW_WIDTH * 4);

    SDL_UnlockTexture(gSDLTexture);
    SDL_RenderTexture(gSDLRenderer, gSDLTexture, NULL, NULL);
    SDL_RenderPresent(gSDLRenderer);
    SDL_Delay(10);
    return true;
}

void render()
{
    /*for (int i = 0, c = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++, c++)
        {
            gFrameBuffer[c] = (int)(0) | 0xff000000;
        }
    }
    for (int i = 0, c = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[i].size(); j++, c++)
        {
            gFrameBuffer[c] = (int)(image[i][j]) | 0xff000000;
        }
    }*/
    SDL_RenderTexture(Renderer, Texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
}

void loop()
{
    if (!update())
    {
        gDone = 1;
        #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
        #endif
    }
    else
    {
        render(SDL_GetTicks());
    }
}

int main(int argc, char** argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        return -1;
    }

    gFrameBuffer = new int[WINDOW_WIDTH * WINDOW_HEIGHT];
    gSDLWindow = SDL_CreateWindow("SDL3 window", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    gSDLRenderer = SDL_CreateRenderer(gSDLWindow, NULL);
    gSDLTexture = SDL_CreateTexture(gSDLRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!gFrameBuffer || !gSDLWindow || !gSDLRenderer || !gSDLTexture)
        return -1;

    std::ifstream file("C:/map.tga", std::ios::binary);
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
    uint8_t* img = new uint8_t[img_binary_size];

    file.read(reinterpret_cast<char*>(img), img_binary_size);

    size_t rwidth = width * bpp;
    size_t offset = 0;
    //size_t base = 0;

    for (size_t i = 0; i < height; ++i)
    {
        image.push_back({});
        for (size_t j = 0; j < width; ++j, offset += bpp)
        {
            image[i].push_back((img[offset + 3] << 6) | img[offset + 2] | (img[offset + 1] << 2) | (img[offset] << 4));
        }
    }
    std::reverse(image.begin(), image.end());
    file.close();

    gDone = 0;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!gDone)
    {
        loop();
    }
#endif

    SDL_DestroyTexture(gSDLTexture);
    SDL_DestroyRenderer(gSDLRenderer);
    SDL_DestroyWindow(gSDLWindow);
    SDL_Quit();

    return 0;
}