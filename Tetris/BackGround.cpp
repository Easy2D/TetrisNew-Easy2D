#include "BackGround.h"
#include "resource.h"

using namespace std;
using namespace easy2d;

BackGround::BackGround()
{
    this->open(IDB_PNG1, L"PNG");
    this->setPos(BRICK_WIDTH * WINDOW_WIDTH / 2, BRICK_WIDTH * WINDOW_HEIGHT / 2);
    this->setAnchor(0.5, 0.5);
    this->setWidth(BRICK_WIDTH * WINDOW_WIDTH);
    this->setHeight(BRICK_WIDTH * WINDOW_HEIGHT);

    _spInfoText = gcnew Text(L"按P暂停，按S开始");
    _spInfoText->setAnchor(0, 0);
    _spInfoText->setFontSize(12);
    _spInfoText->setPos((BOARD_WIDTH + 0.2)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 8)*BRICK_WIDTH);
    this->addChild(_spInfoText);

    _spInfoText = gcnew Text(L"按R重新开始");
    _spInfoText->setAnchor(0, 0);
    _spInfoText->setFontSize(12);
    _spInfoText->setPos((BOARD_WIDTH + 0.2)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 9)*BRICK_WIDTH);
    this->addChild(_spInfoText);

    _spAcknowledge = gcnew Text(L"感谢\"不吃芒果\"");
    _spAcknowledge->setAnchor(0, 0);
    _spAcknowledge->setFontSize(12);
    _spAcknowledge->setPos((BOARD_WIDTH + 0.2)*BRICK_WIDTH, (BOARD_HEIGHT / 6 + 10)*BRICK_WIDTH);
    this->addChild(_spAcknowledge);
}

Pos_t previewAbs = Pos_t((int)(BOARD_WIDTH * BRICK_WIDTH + 1.5 *PREVIEW_BRICK_WIDTH) , (int)(BOARD_HEIGHT / 6 * BRICK_WIDTH + 5.5 * PREVIEW_BRICK_WIDTH));

PreviewBackGround::PreviewBackGround()
{
    this->open(IDB_PNG11, L"PNG");
    this->setPos((float)previewAbs.X, (float)previewAbs.Y);
    this->setAnchor(0, 0);

    this->setWidth(PREVIEW_BRICK_WIDTH * PREVIEW_WIDTH);
    this->setHeight(PREVIEW_BRICK_WIDTH * PREVIEW_WIDTH);
}