#include"audio.h"
class Logic
{
public:
    class Button{};
    Logic();
    void init_map(uint32_t height, uint32_t width);
    void initGraphicPtr(Graphic* gr);
    bool update();
    bool collision(std::shared_ptr<Object> first, std::shared_ptr<Object> second, bool first_call = true);
    char getLastButton();
    bool getButtonState(char c);
    void setObjX(std::shared_ptr<Object> obj, uint32_t x);
    void setObjY(std::shared_ptr<Object> obj, uint32_t y);
    void changeObjX(std::shared_ptr<Object> obj, int64_t x);
    void changeObjY(std::shared_ptr<Object> obj, int64_t y);
    void setWindowCoords(uint32_t x, uint32_t y);
    void changeWindowX(int64_t x);
    void changeWindowY(int64_t y);
    //light function
    bool isMouseOnObjCollider(std::shared_ptr<Object> obj);
    //costly function
    bool isMouseOnObjSprite(std::shared_ptr<Object> obj);
private:
    std::pair<uint32_t, uint32_t> getMousePosition();
    size_t width = 0;
    size_t height = 0;
    Graphic* gr;
    char button = '0';
    std::unordered_map<char, bool> chars_states;
};