#include"Sprite.h"
//#include"lineal_alg.h"

class Logic;

class Object
{
public:
    friend class Logic;
    Object(std::string _name);
    uint8_t getLayer();
    Point2D getPoint2D();
    void setPoint2D(Point2D& point);
    void moveOnVector2D(Vector2D& vector);
    void setLayer(uint8_t layer);
    bool isVisible();
    bool isCollidable();
    void setCollidablity(bool state);
    void setSprite(Sprite& spr);
    void setVisibility(bool state);
    uint32_t getX();
    uint32_t getY();
    const std::string& getName();
    const size_t& getId();
    uint32_t getHeight();
    uint32_t getWidth();
    const std::vector<std::vector<uint32_t>>& getImage();
protected:
    static inline size_t id_iter = 0;
    const size_t id;
    std::string name;
    bool visible = true;
    bool collidable = true;
    Sprite sprite;
    uint8_t layer;
    Point2D left_top_corner;
    void setX(uint32_t _x);
    void setY(uint32_t _y);
    std::string text;
};

