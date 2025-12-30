#include"../include/graphics.h"



#define Black 0x000000ff
#define White 0xffffffff

void Graphic::setWindowCoords(uint32_t x, uint32_t y)
{
    win_x = x;
    win_y = y;
}

void Graphic::clear(uint32_t color)
{
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            FrameBuffer[y * width + x] = color;
            window[y][x] = background_layer;
        }
    }
}

void Graphic::setMainTexture()
{
    char* pix;
    int pitch;
    SDL_LockTexture(Texture, NULL, (void**)&pix, &pitch);
    for (int i = 0, sp = 0, dp = 0; i < height; i++, dp += width, sp += pitch)
        memcpy(pix + sp, FrameBuffer + dp, width * 4);
    SDL_UnlockTexture(Texture);
}

void Graphic::init(uint16_t screen_height, uint16_t screen_width, uint32_t x, uint32_t y)
{
    TTF_Init();
    win_x = x;
    win_y = y;
    height = screen_height;
    width = screen_width;
    FrameBuffer = new int[width * height];
    SDLWindow = SDL_CreateWindow("SDL3 window", width, height, 0);
    Renderer = SDL_CreateRenderer(SDLWindow, NULL);
    Texture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO))
    {
        std::cout << "SDL does not work!\n";
        system("pause");
    }
    for(uint16_t i = 0; i < screen_height; ++i)
    {
        window.push_back({});
        for(uint16_t j = 0; j < screen_width; ++j)
        {
            window[i].push_back({255});
        }
    }
    //clear(White);
    //TTF_Font* 
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    //SDL_Surface* 
    textSurface = TTF_RenderText_Solid(font, "Hello SDL3!",11 , textColor);
    //SDL_Texture* 
    textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
    textRect.x = 100.0f;
    textRect.y = 100.0f;
    textRect.w = (float)textSurface->w;
    textRect.h = (float)textSurface->h;
    SDL_RenderClear(Renderer);
        
        // Отрисовка текста
        
        // Обновление экрана
    SDL_RenderPresent(Renderer);
    //SDL_Delay(5000);
}

void Graphic::stop()
{
    SDL_DestroyTexture(Texture);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
}

Graphic::~Graphic()
{
    stop();
}

void Graphic::render()
{
    setMainTexture();
    SDL_RenderTexture(Renderer, Texture, NULL, NULL);
    SDL_RenderTexture(Renderer, textTexture, nullptr, &textRect);
    SDL_RenderPresent(Renderer);
}

void Graphic::putpixel(int x, int y, uint32_t color)
{
    if (x < 0 ||
        y < 0 ||
        x >= width ||
        y >= height)
    {
        return;
    }
    FrameBuffer[y * width + x] = color;
}

void Graphic::draw(std::shared_ptr<Object> obj)
{
    if (obj->isVisible()) {
        uint32_t x = obj->getX();
        uint32_t y = obj->getY();
        uint32_t img_x = 0;
        uint32_t img_y = 0;
        uint32_t _height = obj->getHeight();
        uint32_t _width = obj->getWidth();
        uint32_t x_vector_shift = 0;
        uint32_t y_vector_shift = 0;
        if(x <= win_x)
        {
            if(x + _width >= win_x)
            {
                img_x = win_x - x;
                x = 0;
            }
        }
        else if (x + _width > win_x + width)
        {
            img_x = x + _width - (win_x + width);
            x -= win_x;
        }
        else 
        {
            x -= win_x;
        }

        if(y < win_y)
        {
            if(y + _height > win_y)
            {
                img_y = win_y - y;
                y = 0;
            }
        }
        else if (y + _height > win_y + height)
        {
            img_y = y + _height - (win_y + height);
            y -= win_y;
        }
        else 
        {
            y -= win_y;
        }
        
        uint32_t bpp = 4;
        const std::vector<std::vector<uint32_t>>& img = obj->getImage();
        uint8_t layer = obj->getLayer();
        for (uint32_t j = 0; j < _height - img_y; ++j)
        {
            for (uint32_t i = 0; i < _width - img_x; ++i)
            {
                if (layer <= window[j + y][i + x])
                {
                    if(uint8_t(img[j + img_y][i + img_x]) != 0)
                    {
                        FrameBuffer[i + x + (y + j) * width] = img[j + img_y][i + img_x];
                        window[j + y][i + x] = layer;
                    }
                }
            }
        }
    }
}