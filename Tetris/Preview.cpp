#include "Preview.h"
#include "resource.h"
#include "Board.h"

using namespace std;
using namespace easy2d;

static Pos_t brickPos[][N_BRICK] = {
    {{0, 0}, {-1, 0}, { 1,  0}, { 2,  0}}, // I_SHAPE
    {{0, 0}, {-1, 0}, {-1, -1}, { 1,  0}}, // J_SHAPE
    {{0, 0}, {-1, 0}, {-1,  1}, { 1,  0}}, // L_SHAPE
    {{0, 0}, { 1, 0}, { 0,  1}, { 1,  1}}, // O_SHAPE
    {{0, 0}, { 1, 0}, { 0,  1}, {-1,  1}}, // S_SHAPE
    {{0, 0}, {-1, 0}, { 1,  0}, { 0,  1}}, // T_SHAPE
    {{0, 0}, {-1, 0}, { 0,  1}, { 1,  1}}, // Z_SHAPE
};

static Pos_t RotatePos(const Pos_t& pos)
{
    Pos_t ret;
    ret.X = -pos.Y;
    ret.Y = pos.X;
    return ret;
}

Preview::Preview(Color_t color, Shape_t shape, int rollNum, Pos_t parentAbsPos)
    : _color(color), _shape(shape), _rollNum(rollNum)
{
    _parentAbsPos = parentAbsPos + Pos_t(2 * PREVIEW_BRICK_WIDTH, 2 * PREVIEW_BRICK_WIDTH);
    for (int i = 0; i < N_BRICK; i++)
    {
        Pos_t pos = brickPos[(int)shape][i];
        Brick* brick = gcnew Brick(color, pos, PREVIEW_BRICK_WIDTH, _parentAbsPos);
        this->addChild(brick);
        _brick[i] = brick;
    }

    // ���˳ʱ����ת ��0 - 3�� * 90��
    for (int i = 0; i < rollNum; i++)
    {
        this->Roll();
    }
    E2D_LOG(L"Preview Created with color:%d, shape:%d, direction:%d", _color, _shape, rollNum);
}

Preview::~Preview()
{
    E2D_LOG(L"Preview Destroyed with color:%d, shape:%d", _color, _shape);
}

Color_t Preview::GetPreviewColor()
{
    return _color;
}
Shape_t Preview::GetPreviewShape()
{
    return _shape;
}
int Preview::GetPreviewRollNum()
{
    return _rollNum;
}


bool Preview::Roll()
{
    if (_shape == Shape_t::O_SHAPE)
    {
        return true;
    }

    // �任���λ��
    Pos_t newPos[N_BRICK];

    for (int i = 0; i < N_BRICK; i++)
    {
        Pos_t relPosBefore = _brick[i]->GetPos() - _brick[0]->GetPos();
        Pos_t relPosAfter = RotatePos(relPosBefore);
        newPos[i] = _brick[0]->GetPos() + relPosAfter;
    }

    // ����µ�λ��
    for (int i = 0; i < N_BRICK; i++) {
        _brick[i]->SetPos(newPos[i]);
        _brick[i]->setPos((float)(_parentAbsPos.X + PREVIEW_BRICK_WIDTH * newPos[i].X),
            (float)(_parentAbsPos.Y + PREVIEW_BRICK_WIDTH * newPos[i].Y));
    }
    return true;
}
