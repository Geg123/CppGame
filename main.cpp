#include"logic.h"
#include<thread>

int main(int argc, char** argv)
{
    Graphic m;
    Logic logic;
    Audio a;

    logic.initGraphicPtr(&m);
    logic.init_map(600, 480);
    m.init(500, 400, 0, 0);
    Sound shot;
    shot.set("C:/programming/shot.wav");
    Sprite spr("C:/test2.tga");
    //spr.rotateOn90Degrees(false);
    Sprite spr2("C:/test.tga");
    Sprite wer("C:/wer.tga");
    Sprite sec("C:/sec.tga");
    Object obj("afd");
    Object obj2("fgh");
    obj.setSprite(spr);
    obj2.setSprite(spr2);
    //m.setWindowCoords(80, 80);
    obj.setLayer(1);
    obj2.setLayer(1);
    obj.setCollidablity(true);
    obj2.setCollidablity(true);
    std::shared_ptr<Object> o1 = std::make_shared<Object>(obj);
    std::shared_ptr<Object> o2 = std::make_shared<Object>(obj2);
    logic.setObjX(o1, 100);
    logic.setObjY(o1, 100);
    logic.setObjX(o2, 10);
    logic.setObjY(o2, 10);
    char tmp = '0';
    std::pair<uint32_t, uint32_t> coords;
    uint32_t x = 0;
    uint32_t y = 0;

    bool d = true;
    char fase = 0;
    while(logic.update())
    {
          m.clear(0xffffffff);
          m.draw(o1);
          m.draw(o2);
          m.render();
          SDL_Delay(1);
          tmp = logic.getLastButton();
        if (logic.getButtonState('D'))
            logic.changeObjX(o2, 2);

        if (logic.getButtonState('A'))
            logic.changeObjX(o2, -2);

        if (logic.getButtonState('W'))
            logic.changeObjY(o2, -2);

        if (logic.getButtonState('S'))
            logic.changeObjY(o2, 2);

        if (logic.getButtonState('F'))
            logic.changeWindowX(-2);

        if (logic.getButtonState('G'))
            logic.changeWindowX(2);

        if (fase == 0 || fase == 3) {
            if (logic.isMouseOnObjCollider(o2))
            {
                if (d)
                {
                    shot.play();
                    o2->setSprite(wer);
                    d = false;
                }
            }
            else {
                if (!d)
                {
                    o2->setSprite(spr2);
                    d = true;
                }
            }
            fase = false;
            fase = 1;
        }
        else
        {
            ++fase;
        }
    }
    
    return 0;
}