#include"memory"

double degToRads(short degrees);

const double PI = 3.14159265;

class Vector2D;

class Point2D
{
public:
    uint32_t getX();
    uint32_t getY();
    void setX(uint32_t _x);
    void setY(uint32_t _y);
    void moveOnVector2D(Vector2D& vector);
private:
    uint32_t x;
    uint32_t y;
};

class Vector2D
{
public:
    Point2D getFirstPoint();
    Point2D getSecondPoint();
    void setFirstPoint();
    void setSecondPoint();
private:
    Point2D first;
    Point2D second;
};