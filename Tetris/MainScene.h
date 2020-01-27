#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_
#include "resource.h"
#include <easy2d/easy2d.h>

#include "TypeDefine.h"
#include "BackGround.h"
#include "Board.h"

using namespace easy2d;

class Board;
class MainScene : public easy2d::Scene
{
public:
    MainScene();
    void onEnter() override;
    void onUpdate() override;
    void onExit() override;

    void KeyInputHandle(Event* evt);

    void FailGame();
    void ResetGame();

    void PauseGame();
    void ResumeGame();

    Text* GetStartText();
    Text* GetPauseText();
    Text* GetFailText();

	void PlayMusic(const String& music, int count = 0);
	void PauseMusic(const String& music);
	void ResumeMusic(const String& music);
	int GetMusicResID(const String& music);

private:
    ~MainScene();

    BackGround* _spBackGround;
    PreviewBackGround* _spPreviewBackGround;

    Board* _spBoard;
    Text* _spStartText;
    Text* _spPauseText;
    Text* _spFailText;

	MusicPlayer _MusicPlayer;
};
#endif
