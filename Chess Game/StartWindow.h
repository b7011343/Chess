#pragma once

#include "EasyGraphics.h"
#include "InputBox.h"
#include "Button.h"
#include "PlayerManager.h"
#include "GameWindow.h"
#include "HighscoresWindow.h"

class StartWindow : public EasyGraphics
{
public:
	StartWindow(HINSTANCE hInstance);
	~StartWindow();

private:
	static const int WIN_WIDTH = 640;
	static const int WIN_HEIGHT = 500;

	InputBox* player1NameInput;
	InputBox* player2NameInput;
	Button<const char*>* playButton;
	Button<const char*>* highscoresButton;
	HINSTANCE hInstance;
	GameWindow* gameWindow;
	HighscoresWindow* highscoresWindow;
	bool windowBusy;

	virtual void onDraw();
	virtual void onDestroy();
	virtual void onChar(UINT nChar, UINT nRepCnt, UINT nFlags);    
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onCreate();
	void PlayGame();
	void Highscores();
};

inline void StartWindow::onMouseMove(UINT nFlags, int x, int y)
{
	bool currentHoverStatusPlay = playButton->IsMouseOver();
	if (playButton->Entity::MouseIsOver(x, y))
	{
		playButton->Hovering(true);
	}
	else
	{
		playButton->Hovering(false);
	}

	bool currentHoverStatusHS = highscoresButton->IsMouseOver();
	if (highscoresButton->Entity::MouseIsOver(x, y))
	{
		highscoresButton->Hovering(true);
	}
	else
	{
		highscoresButton->Hovering(false);
	}

	if (currentHoverStatusPlay != playButton->IsMouseOver() || currentHoverStatusHS != highscoresButton->IsMouseOver())
	{
		onDraw();
	}
}

inline void StartWindow::onChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (player1NameInput->IsSelected())
	{
		player1NameInput->ModifyText(nChar);
	}
	if (player2NameInput->IsSelected())
	{
		player2NameInput->ModifyText(nChar);
	}
	onDraw();
}

inline void StartWindow::onLButtonDown(UINT nFlags, int x, int y)
{
	player1NameInput->Select(false);
	player2NameInput->Select(false);
	if (player1NameInput->Entity::MouseIsOver(x, y))
	{
		player1NameInput->Select(true);
	}
	else if (player2NameInput->Entity::MouseIsOver(x, y))
	{
		player2NameInput->Select(true);
	}
	else if (playButton->Entity::MouseIsOver(x, y))
	{
		PlayGame();
	}
	else if (highscoresButton->Entity::MouseIsOver(x, y))
	{
		Highscores();
	}
	onDraw();
}
