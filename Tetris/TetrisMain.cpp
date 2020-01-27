#include <easy2d/easy2d.h>
#include "TypeDefine.h"
#include "MainScene.h"
#include "resource.h"

using namespace easy2d;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    if (Game::init(L"俄罗斯方块", WINDOW_WIDTH * BRICK_WIDTH, WINDOW_HEIGHT * BRICK_WIDTH))
    {
		// 设置窗口图标
		Window::setIcon(IDI_ICON1);

        auto scene = gcnew MainScene();
        SceneManager::enter(scene);

		Game::start();
    }
	Game::destroy();
    return 0;
}
