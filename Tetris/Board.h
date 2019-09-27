#ifndef _BOARD_H_
#define _BOARD_H_
#include "resource.h"
#include <easy2d.h>
#include "TypeDefine.h"

#include "Brick.h"
#include "Building.h"
#include "Preview.h"


using namespace easy2d;
using namespace std;

class MainScene;
class Board : public Sprite
{
public:
    Board(MainScene* pMainScene);
    void onUpdate() override;

    bool CreateBuilding();
    bool CreatePreview();

    Pos_t GetAbsPos();
    bool IsAvaliable(Pos_t pos);

    bool TakePos(Brick* spBrick);
    void TakePosByForce(Brick* spBrick);
    void Release(Pos_t pos);

    void PullBricks(int pos_Y, int lineNum);
    void ElimBricks(int pos_Y);

    void MoveBuilding(Direction_t d);

    int GetLevel();

    void ResetBoard();

private:

    //mutex _mutex;
    int TryElimBricks();
    void GetReward(int fullLineNum);

    // 被占据的Brick
    Brick* _spBricks[BOARD_HEIGHT][BOARD_WIDTH];

    Building* _spBuilding;
    Preview* _spPreview;

    Pos_t _absPos;

    bool _needCreateBuilding;

    Text* _spScoreText;
    Text* _spLevelText;
    int _level;
    int _score;

    MainScene* _pMainScene;

};
#endif