#ifndef _BRICK_H_
#define _BRICK_H_

#include "resource.h"
#include <easy2d.h>
#include "TypeDefine.h"

using namespace easy2d;

class Board;

class Brick : public Sprite
{
public:
    Brick(Color_t color, Pos_t pos, float size, Pos_t parentAbsPos);
    void SetPos(Pos_t pos);
    Pos_t GetPos();
    ~Brick();
private:
    Color_t _color;
    Pos_t _pos;
    Pos_t _parentAbsPos;
};

#endif