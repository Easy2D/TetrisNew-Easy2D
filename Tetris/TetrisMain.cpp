//---------------------------------------------------------
// 程序名称：TetrisNew
// 作者：大猫
// 编译环境：Visual Studio 2019 / Easy2D v2.0.4
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "TypeDefine.h"
#include "MainScene.h"
#include "resource.h"

using namespace easy2d;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (Game::init(L"Tetris", WINDOW_WIDTH * BRICK_WIDTH, WINDOW_HEIGHT * BRICK_WIDTH))
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
