#ifndef _PREVIEW_H_
#define _PREVIEW_H_
#include "resource.h"
#include <easy2d.h>
#include "TypeDefine.h"
#include "Building.h"

using namespace easy2d;
using namespace std;
class Board;

class Preview : public Sprite
{
public:
    // rollNum指初始顺时针旋次数（每次90度）
    Preview(Color_t color, Shape_t shape, int rollNum, Pos_t parentAbsPos);
    bool Roll();
    Color_t GetPreviewColor();
    Shape_t GetPreviewShape();
    int GetPreviewRollNum();
private:
    ~Preview();
    Color_t _color;
    Shape_t _shape;
    int _rollNum;
    Brick* _brick[N_BRICK];
    Pos_t _parentAbsPos;
};

#endif