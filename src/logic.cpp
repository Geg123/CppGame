#include"../include/logic.h"

Logic::Logic()
{
    chars_states['A'] = false;
    chars_states['B'] = false;
    chars_states['C'] = false;
    chars_states['D'] = false;
    chars_states['E'] = false;
    chars_states['F'] = false;
    chars_states['G'] = false;
    chars_states['H'] = false;
    chars_states['I'] = false;
    chars_states['J'] = false;
    chars_states['K'] = false;
    chars_states['L'] = false;
    chars_states['M'] = false;
    chars_states['N'] = false;
    chars_states['O'] = false;
    chars_states['P'] = false;
    chars_states['Q'] = false;
    chars_states['R'] = false;
    chars_states['S'] = false;
    chars_states['T'] = false;
    chars_states['U'] = false;
    chars_states['V'] = false;
    chars_states['W'] = false;
    chars_states['X'] = false;
    chars_states['Y'] = false;
    chars_states['Z'] = false;
    chars_states['0'] = false;
    chars_states['1'] = false;
    chars_states['2'] = false;
    chars_states['3'] = false;
    chars_states['4'] = false;
    chars_states['5'] = false;
    chars_states['6'] = false;
    chars_states['7'] = false;
    chars_states['8'] = false;
    chars_states['9'] = false;
}

bool Logic::update()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            return false;
        }
        else if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
        {
            return false;
        }
        else if(e.type == SDL_EVENT_KEY_UP)
        {
            chars_states[*SDL_GetKeyName(e.key.key)] = false;
        }
        else if(e.type == SDL_EVENT_KEY_DOWN)
        {
            button = *SDL_GetKeyName(e.key.key);
            chars_states[button] = true;
        }
        else
        {
            button = '0';
        }
    }
    SDL_Delay(2);
}

void Logic::initGraphicPtr(Graphic* _gr)
{
    gr = _gr;
}

void Logic::init_map(uint32_t _height, uint32_t _width)
{
    height = _height;
    width = _width;
}

bool Logic::collision(std::shared_ptr<Object> first, std::shared_ptr<Object> second, bool first_call)
{
    uint32_t fx = first->getX();
    uint32_t fy = first->getY();
    uint32_t fh = first->getHeight();
    uint32_t fw = first->getWidth();

    uint32_t sx = second->getX();
    uint32_t sy = second->getY();
    uint32_t sh = second->getHeight();
    uint32_t sw = second->getWidth();
    uint32_t mx = 0;
    uint32_t my = 0;
    uint32_t mw = 0;
    uint32_t mh = 0;
    uint32_t fpicx = 0;
    uint32_t fpicy = 0;
    uint32_t spicx = 0;
    uint32_t spicy = 0;
    uint32_t tmp = 0;
    if(!first->isCollidable() || !second->isCollidable())
        return false;
    if((fw + fx >= sx) && (sx >= fx))
    {
        mx = sx;
        mw = fx + fw - mx;
        mw = sw <= mw ? sw : mw;
        if(fy <= sy && fy + fh >= sy)
        {
            my = sy;
            mh = fy + fh - my;
            mh = sh <= mh ? sh : mh;
            fpicx = mx - fx;
            fpicy = my - fy;
            const std::vector<std::vector<uint32_t>> fpic = first->getImage();
            const std::vector<std::vector<uint32_t>> spic = second->getImage();
            for(uint32_t j = fpicy; j < mh; ++j)
            {
                for(uint32_t i = fpicx; i < mw; ++i)
                {
                    if(uint8_t(fpic[j + fpicy][i + fpicx]) == 0xff && uint8_t(spic[j + spicy][i + spicx]) == 0xff)
                        return true;
                }
            }
        }
    }
    else if(first_call == true)
        return collision(second, first, false);
    else 
        return false;
}

char Logic::getLastButton()
{
    return button;
}

bool Logic::getButtonState(char c)
{
    return chars_states.at(c);
}

bool Logic::isMouseOnObjCollider(std::shared_ptr<Object> obj)
{   
    std::pair<uint32_t, uint32_t> tmp = getMousePosition();
    int64_t x = tmp.first;
    int64_t y = tmp.second;
    if(x >= int64_t(obj->getX()) - gr->win_x && x<= int64_t(obj->getX()) + obj->getWidth() - gr->win_x && y >= int64_t(obj->getY()) - gr->win_y && y <= int64_t(obj->getY()) + obj->getHeight() - gr->win_y)
    {
        return true;
    }
    return false;
}

void Logic::setObjX(std::shared_ptr<Object> obj, uint32_t x)
{
    if(x + obj->getWidth() <= width)
    {
        obj->setX(x);
    }
}

void Logic::setObjY(std::shared_ptr<Object> obj, uint32_t y)
{
    if(y + obj->getHeight() <= height)
    {
        obj->setY(y);
    }
}

void Logic::changeObjX(std::shared_ptr<Object> obj, int64_t x)
{
    uint32_t tmp = obj->getX();
    int64_t newx =  x + tmp;
    if(newx + obj->getHeight() <= width && newx >= 0)
    {
        obj->setX(x + tmp);
    }
}
void Logic::changeObjY(std::shared_ptr<Object> obj, int64_t y)
{
    uint32_t tmp = obj->getY();
    int64_t newy =  y + tmp;
    if(newy + obj->getHeight() <= height && newy >= 0)
    {
        obj->setY(y + tmp);
    }
}

void Logic::changeWindowX(int64_t x)
{
    int64_t newx = gr->win_x + x;
    if (newx >= 0 && newx + gr->width <= width)
    {
        gr->win_x = newx;
    }
}

void Logic::changeWindowY(int64_t y)
{
    int64_t newy = gr->win_y + y;
    if (newy >= 0 && newy + gr->height <= height)
    {
        gr->win_y = newy;
    }
}

std::pair<uint32_t, uint32_t> Logic::getMousePosition()
{
    float x = 0;
    float y = 0;
    SDL_GetMouseState(&x,&y);
    return std::make_pair<uint32_t, uint32_t>(x, y);
}