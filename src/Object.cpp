#include"../include/Object.h"

Object::Object(std::string _name) : id(id_iter), name(_name)
{
    static size_t _id_ = 0;
    ++_id_;
}

bool Object::isVisible()
{
    return visible;
}

bool Object::isCollidable()
{
    return collidable;
}

void Object::setCollidablity(bool state)
{
    collidable = state;
}

void Object::setLayer(uint8_t _layer)
{
    layer = _layer;
}

uint32_t Object::getX()
{
    return left_top_corner.getX();
}

uint32_t Object::getY()
{
    return left_top_corner.getY();
}

uint32_t Object::getHeight()
{
    return sprite.getHeight();
}

uint32_t Object::getWidth()
{
    return sprite.getWidth();
}

uint8_t Object::getLayer()
{
    return layer;
}

void Object::setX(uint32_t _x)
{
    left_top_corner.setX(_x);
}

void Object::setY(uint32_t _y)
{
    left_top_corner.setY(_y);
}

const std::vector<std::vector<uint32_t>>& Object::getImage()
{
    return sprite.getImage();
}

void Object::setSprite(Sprite& spr)
{
    sprite = spr;
}

void Object::setVisibility(bool state)
{   
    visible = state;
}