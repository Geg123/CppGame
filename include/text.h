#include"Object.h"
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

class Text : public Object
{
public:
    Text(std::string _text);
    Text(std::string _text, uint32_t color);
    Text(std::string _text, uint32_t color, std::string path, uint8_t size);
    void setFont(std::string path, uint8_t size);
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void serColor(uint32_t _color);
    void setText(std::string _text);
protected:
    bool fast_render = true;
    std::string text;
    TTF_Font* font;
    //technical stuff:
    SDL_Color SDLTextColor;
    uint32_t color32;
    SDL_FRect textRect;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
}