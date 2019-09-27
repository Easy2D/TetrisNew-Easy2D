#include "Board.h"
#include "resource.h"

#include "TypeDefine.h"
#include "MainScene.h"

using namespace std;
using namespace easy2d;

Board::Board(MainScene* pMainScene)
    : _needCreateBuilding(true), _level(1), _score(0), _pMainScene(pMainScene), _spBuilding(nullptr), _spPreview(nullptr)
{
    this->open(IDB_PNG2, L"PNG");

    this->setWidth((float)(BOARD_WIDTH * BRICK_WIDTH));
    this->setHeight((float)(BOARD_HEIGHT * BRICK_WIDTH));

    this->setAnchor(0, 0);
    this->setPos(0, 0);

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            _spBricks[i][j] = nullptr;
        }
    }

    _spLevelText = gcnew Text(L"等级: 1");
    _spLevelText->setAnchor(0, 0);
    _spLevelText->setFontSize(12);
    _spLevelText->setPos((BOARD_WIDTH + 0.8)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 0)*BRICK_WIDTH);
    _pMainScene->addChild(_spLevelText);

    _spScoreText = gcnew Text(L"分数: 0");
    _spScoreText->setAnchor(0, 0);
    _spScoreText->setFontSize(12);
    _spScoreText->setPos((BOARD_WIDTH + 0.8)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 1)*BRICK_WIDTH);
    _pMainScene->addChild(_spScoreText);

    auto text = gcnew Text(L"下一个:");
    text->setAnchor(0, 0);
    text->setFontSize(12);
    text->setPos((BOARD_WIDTH + 0.8)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 2)*BRICK_WIDTH);
    _pMainScene->addChild(text);
}

void Board::ResetBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            _spBricks[i][j] = nullptr;
        }
    }

    if (_spBuilding != nullptr)
    {
        _spBuilding = nullptr;
    }

	if (_spPreview != nullptr)
	{
		_spPreview = nullptr;
	}

	removeAllChildren();

    _needCreateBuilding = true;
    _level = 1;
    _score = 0;

	setAutoUpdate(true);
}

bool Board::IsAvaliable(Pos_t pos)
{
    if ((pos.X >= BOARD_WIDTH) || (pos.Y >= BOARD_HEIGHT))
    {
        return false;
    }
    if ((pos.X < 0) || (pos.Y < 0)) {
        return false;
    }

    if (_spBricks[pos.Y][pos.X] != nullptr)
    {
        return false;
    }

    return true;
}

bool Board::TakePos(Brick* spBrick)
{
    Pos_t pos = spBrick->GetPos();

    if (IsAvaliable(pos))
    {
        _spBricks[pos.Y][pos.X] = spBrick;
        return true;
    }
    return false;
}

void Board::TakePosByForce(Brick* spBrick)
{
    Pos_t pos = spBrick->GetPos();
    Release(pos);
    _spBricks[pos.Y][pos.X] = spBrick;
}

void Board::Release(Pos_t pos)
{
    if (_spBricks[pos.Y][pos.X] != nullptr)
    {
        _spBricks[pos.Y][pos.X]->setVisible(false);
        this->removeChild(_spBricks[pos.Y][pos.X]);
        _spBricks[pos.Y][pos.X] = nullptr;
    }
}

Pos_t Board::GetAbsPos()
{
    return _absPos;
}

int Board::GetLevel()
{
    return _level;
}

bool Board::CreateBuilding()
{
    float speed = 1.0f * pow(1.25f, _level);
    Shape_t shape;
    Color_t color;
    int rollNum;

    if (_spPreview == nullptr)
    {
        shape = (Shape_t)Random::range((int)Shape_t::I_SHAPE, (int)Shape_t::Z_SHAPE);
        color = (Color_t)(int)shape;
        rollNum = Random::range(0, 3);
    }
    else
    {
        shape = _spPreview->GetPreviewShape();
        color = _spPreview->GetPreviewColor();
        rollNum = _spPreview->GetPreviewRollNum();
    }

    static const Pos_t centerPos = Pos_t{ BOARD_WIDTH / 2, 2 };
    _spBuilding = gcnew Building(color, shape, rollNum, centerPos, this, speed);
    this->addChild(_spBuilding);

    if (!_spBuilding->CanTakeBoardPos())
    {
        return false;
    }
    return true;

}

extern Pos_t previewAbs; // 需要修改
bool Board::CreatePreview()
{
    if (_spPreview != nullptr)
    {
        this->removeChild(_spPreview);
    }

    Shape_t shape = (Shape_t)Random::range((int)Shape_t::I_SHAPE, (int)Shape_t::Z_SHAPE);
    Color_t color = (Color_t)(int)shape;
    int rollNum = Random::range(0, 3);

    _spPreview = gcnew Preview(color, shape, rollNum, previewAbs);
    this->addChild(_spPreview);

    return true;
}

void Board::MoveBuilding(Direction_t d)
{
    if (_spBuilding != nullptr)
    {
        _spBuilding->TryMove(d);
    }
    if (d == Direction_t::DROP)
    {
		_pMainScene->PlayMusic(L"BrickCrash");
    }
}

void Board::PullBricks(int pos_Y, int lineNum)
{
    if ((pos_Y + lineNum > BOARD_HEIGHT - 1) || (lineNum == 0))
    {
        return;
    }

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (_spBricks[pos_Y][i] != nullptr)
        {
            Brick* brick = _spBricks[pos_Y][i];
            _spBricks[pos_Y][i] = nullptr;
            Pos_t newPos = brick->GetPos() + Pos_t{ 0, lineNum };
            brick->SetPos(newPos);
            TakePosByForce(brick);
        }
    }
}

void Board::ElimBricks(int pos_Y)
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        Release(Pos_t{ i, pos_Y });
    }
}

int Board::TryElimBricks()
{
    // 检查是否有排数占满
    int fullLineNum = 0;

    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
    {
        bool isLineFull = true;

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (_spBricks[i][j] == nullptr)
            {
                isLineFull = false;
                break;
            }

        }
        if (isLineFull)
        {
            fullLineNum++;
            ElimBricks(i);
        }
        else
        {
            PullBricks(i, fullLineNum);
        }
    }

    return fullLineNum;
}

void Board::GetReward(int fullLineNum)
{
    const static int scorePerLevel = 10000;

    E2D_LOG(L"fullLineNum %d!", fullLineNum);
    if (fullLineNum == 0)
    {
        _score += 10; // 增加分数
        _level = (_score / scorePerLevel) + 1;
        E2D_LOG(L"level:%d score: %d!", _level, _score);
        return;
    }

    E2D_LOG(L"11 fullLineNum %d!", fullLineNum);
    if (fullLineNum == 1)
    {
        _score += 100; // 增加分数
    }
    else if (fullLineNum == 2)
    {
        _score += 200;
    }
    else if (fullLineNum == 3)
    {
        _score += 400;
    }
    else if (fullLineNum == 4)
    {
        _score += 800;
    }
    _level = (_score / scorePerLevel) + 1;

    E2D_LOG(L"level:%d score: %d!", _level, _score);
	_pMainScene->PlayMusic(L"BrickBomb");
}

// 创建Building, 并尝试消除方块
void Board::onUpdate()
{
    static int waitTime = 10; // 1/60s
    int fullLineNum = 0;

    if (_spBuilding == nullptr)
    {
        _needCreateBuilding = true;
    }
    else if (!_spBuilding->Movable())
    {
        this->removeChild(_spBuilding);
        _spBuilding = nullptr;
        _needCreateBuilding = true;

        GetReward(0); // 消除了0行，仅增加分数
    }
    else
    {
        _needCreateBuilding = false;
    }

    fullLineNum = TryElimBricks();

    if (fullLineNum != 0)
    {
        E2D_LOG(L"Eliminate %d lines!", fullLineNum);
        GetReward(fullLineNum); // 消除了1-4行，会增加大量分数
    }

    if (_needCreateBuilding)
    {
        _spLevelText->setText(L"等级: " + to_wstring(_level));
        _spScoreText->setText(L"分数: " + to_wstring(_score));
        if (!CreateBuilding())
        {
            E2D_LOG(L"CreateBuilding!!!!");
            _pMainScene->FailGame();
        }
        else
        {
            E2D_LOG(L"CreatePreview");
            CreatePreview();
        }
        //E2D_LOG(L"CreatePreview");
        //CreatePreview();
    }
}
