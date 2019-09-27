#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <easy2d.h>
#include "resource.h"
#include "TypeDefine.h"
#include "Brick.h"

using namespace easy2d;
using namespace std;
class Board;

class Building : public Sprite
{
public:
    // rollNum指初始顺时针旋次数（每次90度）
    Building(Color_t color, Shape_t shape, int rollNum, Pos_t centerPos, Board* pBoard, float dropSpeed);
    void onUpdate() override;
    bool Roll();
    bool TryMove(Direction_t d);
    bool CanMove(Direction_t d);

    bool CanTakeBoardPos();
    bool Movable();

private:
    ~Building();
    Color_t _color;
    Shape_t _shape;
    Pos_t _centerPos;
    Board* _pBoard;
    Brick* _brick[N_BRICK];
    bool _movable;
    int _frameNum;
    float _dropSpeed;
};

#endif