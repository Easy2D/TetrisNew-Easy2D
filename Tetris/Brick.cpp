#include "Brick.h"
#include "resource.h"
#include "Board.h"

using namespace std;
using namespace easy2d;

static int brickName[] = {
	(IDB_PNG9),  //    Color_t::RED
	(IDB_PNG7),  //    Color_t::ORANGE
	(IDB_PNG10), //    Color_t::YELLOW
	(IDB_PNG6),  //    Color_t::GREEN
	(IDB_PNG4),  //    Color_t::CYAN
	(IDB_PNG3),  //    Color_t::BLUE
	(IDB_PNG8),  //    Color_t::PURPLE
	(IDB_PNG5),  //    Color_t::GRAY
};

Brick::Brick(Color_t color, Pos_t pos, float size, Pos_t parentAbsPos) : _parentAbsPos(parentAbsPos)
{
    E2D_LOG(L"Brick created");

    this->open(brickName[(int)color], L"PNG");
    this->setAnchor(0, 0);
    this->setWidth(size);
    this->setHeight(size);
    _color = color;
    _pos = pos;
    this->setPos((float)(parentAbsPos.X + size * pos.X), (float)(parentAbsPos.Y + size * pos.Y));
}

Brick::~Brick()
{
    E2D_LOG(L"Brick destroyed");
}

void Brick::SetPos(Pos_t pos)
{
    _pos = pos;
    this->setPos((float)(_parentAbsPos.X + BRICK_WIDTH * pos.X), (float)(_parentAbsPos.Y + BRICK_WIDTH * pos.Y));

}

Pos_t Brick::GetPos()
{
    return _pos;
}

