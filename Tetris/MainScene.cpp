#include "MainScene.h"
#include "resource.h"

#include "BackGround.h"
#include "Board.h"

using namespace std;
using namespace std::placeholders;
using namespace easy2d;

MainScene::MainScene() : _spBackGround(nullptr), _spBoard(nullptr), _spStartText(nullptr), _spPauseText(nullptr), _spFailText(nullptr)
{
	// 添加音效
	_MusicPlayer.preload(IDR_WAVE1, L"WAVE");  // BackGround
	_MusicPlayer.preload(IDR_WAVE2, L"WAVE");  // BrickBomb
	_MusicPlayer.preload(IDR_WAVE3, L"WAVE");  // BrickCrash
	_MusicPlayer.preload(IDR_WAVE4, L"WAVE");  // Fail
}

MainScene::~MainScene()
{
}

Text* MainScene::GetStartText()
{
	return _spStartText;
}
Text* MainScene::GetPauseText()
{
	return _spPauseText;
}
Text* MainScene::GetFailText()
{
	return _spFailText;
}

void MainScene::PlayMusic(const String& music, int count)
{
	_MusicPlayer.play(GetMusicResID(music), L"WAVE", count);
}

void MainScene::PauseMusic(const String& music)
{
	_MusicPlayer.pause(GetMusicResID(music), L"WAVE");
}

void MainScene::ResumeMusic(const String& music)
{
	_MusicPlayer.resume(GetMusicResID(music), L"WAVE");
}

int MainScene::GetMusicResID(const String& music)
{
	if (music == L"BackGround")
	{
		return (IDR_WAVE1);
	}
	else if (music == L"BrickBomb")
	{
		return (IDR_WAVE2);
	}
	else if (music == L"BrickCrash")
	{
		return (IDR_WAVE3);
	}
	else if (music == L"Fail")
	{
		return (IDR_WAVE4);
	}
	return 0;
}

void MainScene::onEnter()
{
	_spBackGround = gcnew BackGround();
	if (_spBackGround != nullptr)
	{
		this->addChild(_spBackGround);
	}

	_spPreviewBackGround = gcnew PreviewBackGround();
	if (_spPreviewBackGround != nullptr)
	{
		this->addChild(_spPreviewBackGround);
	}

	_spBoard = gcnew Board(this);
	if (_spBoard != nullptr)
	{
		this->addChild(_spBoard);
	}

	_spPauseText = gcnew Text(L"暂停中");
	if (_spPauseText != nullptr)
	{
		_spPauseText->setFontSize(36);
		_spPauseText->setAnchor(0.5, 0.5);
		_spPauseText->setPos(BOARD_WIDTH * BRICK_WIDTH / 2, BOARD_WIDTH * BRICK_WIDTH / 2);
		_spPauseText->setVisible(false);
		_spPauseText->setOrder(1);
		this->addChild(_spPauseText);
	}

	_spFailText = gcnew Text(L"失败！");
	if (_spFailText != nullptr)
	{
		_spFailText->setFontSize(36);
		_spFailText->setAnchor(0.5, 0.5);
		_spFailText->setPos(BOARD_WIDTH * BRICK_WIDTH / 2, BOARD_WIDTH * BRICK_WIDTH / 2);
		_spFailText->setVisible(false);
		_spFailText->setOrder(1);
		this->addChild(_spFailText);
	}

	PlayMusic(L"BackGround", -1);

	// 添加消息监听EventCallback
	Listener::Callback cbKey = bind(&MainScene::KeyInputHandle, this, _1);
	addListener(cbKey, L"键盘事件");
}

void MainScene::FailGame()
{
	_spFailText->setVisible(true);

	PauseMusic(L"BackGround");
	PlayMusic(L"Fail");

	_spBoard->setAutoUpdate(false);
}
void MainScene::ResetGame()
{
	if (_spPauseText->isVisible() == true)
	{
		return;
	}
	_spFailText->setVisible(false);
	_spPauseText->setVisible(false);

	ResumeMusic(L"BackGround");

	_spBoard->ResetBoard();
}

void MainScene::PauseGame()
{
	if (_spFailText->isVisible() == true)
	{
		return;
	}
	_spFailText->setVisible(false);
	_spPauseText->setVisible(true);
	PauseMusic(L"BackGround");
	_spBoard->setAutoUpdate(false);
}

void MainScene::ResumeGame()
{
	_spPauseText->setVisible(false);
	_spFailText->setVisible(false);
	ResumeMusic(L"BackGround");
	_spBoard->setAutoUpdate(true);
}

void MainScene::KeyInputHandle(Event* evt)
{
	if (evt->type != Event::Type::KeyDown)
		return;

	switch (((KeyDownEvent*)evt)->key)
	{
	case KeyCode::P:
		PauseGame();
		break;
	case KeyCode::S:
		ResumeGame();
		break;
	case KeyCode::R:
		ResetGame();
		break;
	case KeyCode::Up:
		_spBoard->MoveBuilding(Direction_t::UP);
		break;
	case KeyCode::Down:
		_spBoard->MoveBuilding(Direction_t::DOWN);
		break;
	case KeyCode::Left:
		_spBoard->MoveBuilding(Direction_t::LEFT);
		break;
	case KeyCode::Right:
		_spBoard->MoveBuilding(Direction_t::RIGHT);
		break;
	case KeyCode::Space:
		_spBoard->MoveBuilding(Direction_t::DROP);
		break;
	default:
		break;
	}
}

void MainScene::onUpdate()
{
}

void MainScene::onExit()
{
}
