#ifndef _BACK_GROUND_H_
#define _BACK_GROUND_H_
#include <easy2d.h>

#include "resource.h"
#include "TypeDefine.h"

using namespace easy2d;

class BackGround : public Sprite
{
public:
    BackGround();
private:
    Text* _spInfoText;
    Text* _spAcknowledge;
};

class PreviewBackGround : public Sprite
{
public:
    PreviewBackGround();
};

#endif
