#include "Building.h"
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

Building::Building(Color_t color, Shape_t shape, int rollNum, Pos_t centerPos, Board* pBoard, float dropSpeed)
	: _color(color), _shape(shape), _centerPos(centerPos), _pBoard(pBoard), _movable(true), _frameNum(0), _dropSpeed(dropSpeed)
{
	for (int i = 0; i < N_BRICK; i++)
	{
		Pos_t pos = centerPos + brickPos[(int)shape][i];
		Brick* brick = gcnew Brick(color, pos, BRICK_WIDTH, pBoard->GetAbsPos());
		pBoard->addChild(brick);
		_brick[i] = brick;
	}

	// 随机顺时针旋转 （0 - 3） * 90度
	for (int i = 0; i < rollNum; i++)
	{
		this->Roll();
	}
	E2D_LOG(L"Building Created with color:%d, shape:%d, direction:%d", _color, _shape, rollNum);
}

Building::~Building()
{
	E2D_LOG(L"Building Destroyed with color:%d, shape:%d", _color, _shape);
}

bool Building::Roll()
{
	if (_shape == Shape_t::O_SHAPE)
	{
		return true;
	}

	// 变换后的位置
	Pos_t newPos[N_BRICK];
	int distance2Wall = 0;

	for (int i = 0; i < N_BRICK; i++)
	{
		Pos_t relPosBefore = _brick[i]->GetPos() - _brick[0]->GetPos();
		Pos_t relPosAfter = RotatePos(relPosBefore);
		newPos[i] = _brick[0]->GetPos() + relPosAfter;
		if ((newPos[i].X < 0) && ((-newPos[i].X) > distance2Wall))
		{
			// 变换后撞到左墙，需要平移distance2Wall（向右）
			distance2Wall = -newPos[i].X;
		}
		else if ((newPos[i].X > BOARD_WIDTH - 1) && (BOARD_WIDTH - 1 - newPos[i].X < distance2Wall))
		{
			// 变换后撞到左墙，需要平移distance2Wall（向左）
			distance2Wall = BOARD_WIDTH - 1 - newPos[i].X;
		}
	}

	// 检测位置是否被占用
	bool ret = true;
	for (int i = 0; i < N_BRICK; i++)
	{
		newPos[i].X += distance2Wall;
		if (!_pBoard->IsAvaliable(newPos[i]))
		{
			ret = false;
			break;
		}
	}

	if (ret == false)
	{
		return ret;
	}

	// 设成新的位置
	for (int i = 0; i < N_BRICK; i++)
	{
		_brick[i]->SetPos(newPos[i]);
		_brick[i]->setPos((float)(_pBoard->GetAbsPos().X + BRICK_WIDTH * newPos[i].X), (float)(_pBoard->GetAbsPos().Y + BRICK_WIDTH * newPos[i].Y));
	}

	return true;
}


static Pos_t deltaPos[] = {
	{0, -1}, // UP
	{0,  1}, // DOWN
	{-1, 0}, // LEFT
	{1, 0} // RIGHT
};

bool Building::TryMove(Direction_t d)
{

	//_mut.lock();
	if (d == Direction_t::UP)
	{
		return Roll();
	}

	if (d == Direction_t::DROP)
	{
		bool ret = false;
		while (TryMove(Direction_t::DOWN))
		{
			ret = true;
		}
		// 直接掉落后，不许再左右移动
		for (int i = 0; i < N_BRICK; i++)
		{
			_pBoard->TakePos(_brick[i]);
		}
		_movable = false;

		return ret;
	}

	if (CanMove(d))
	{
		//_mut.lock();
		for (int i = 0; i < N_BRICK; i++)
		{
			Pos_t newPos = _brick[i]->GetPos() + deltaPos[(int)d];
			_brick[i]->SetPos(newPos);
		}
		//_mut.unlock();
		return true;
	}

	//_mut.unlock();
	return false;
}

bool Building::CanMove(Direction_t d)
{
	bool ret = true;
	// 移动后的位置
	if (d == Direction_t::UP)
	{
		return ret;
	}

	Pos_t newPos[N_BRICK];
	for (int i = 0; i < N_BRICK; i++)
	{

		newPos[i] = _brick[i]->GetPos() + deltaPos[(int)d];
		if (!_pBoard->IsAvaliable(newPos[i]))
		{
			ret = false;
			break;
		}
	}
	return ret;
}


bool Building::CanTakeBoardPos()
{
	if (_movable == false)
	{
		return false;
	}

	for (int i = 0; i < N_BRICK; i++)
	{
		if (!_pBoard->IsAvaliable(_brick[i]->GetPos()))
		{
			_movable = false; // 不应在这里设 fix it
			break;
		}
	}
	return _movable;
}

bool Building::Movable()
{
	return _movable;
}

// _brick名称统一下，要不要加p
void Building::onUpdate()
{
	if (_movable == false)
	{
		return;
	}

	int frameInterval = (int)(60.0 / _dropSpeed) + 1;

	_frameNum++;
	if (_frameNum >= frameInterval * 100)
	{
		_frameNum = 0;
	}
	if (_frameNum % frameInterval != 0)
	{
		return;
	}

	if (!TryMove(Direction_t::DOWN))
	{
		for (int i = 0; i < N_BRICK; i++)
		{
			_pBoard->TakePos(_brick[i]);
		}
		_movable = false;
	}
}