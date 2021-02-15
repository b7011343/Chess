#pragma once

#include "EasyGraphics.h"
#include "ChessBoard.h"

class GameWindow : public EasyGraphics
{
public:
	GameWindow(HINSTANCE hInstance);
	~GameWindow();

private:
	static const int WIN_WIDTH = 878;
	static const int WIN_HEIGHT = 439;
	static const int GAME_TIMER_ID = 1;
	ChessBoard* board;

	virtual void onDraw();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onCreate();
	void onTimer(UINT nIDEvent);
	void DrawStats();
};

inline void GameWindow::onDraw()
{
	clearScreen(WHITE);
	DrawStats();
	board->Draw(this);
	EasyGraphics::onDraw();
}

inline void GameWindow::onLButtonDown(UINT nFlags, int x, int y)
{
	board->UpdateBoard(this, x, y);
	onDraw();
}

inline void GameWindow::onTimer(UINT nIDEvent)
{
	if (nIDEvent == GAME_TIMER_ID)
	{
		PlayerManager::GetPlayerManager()->Tick();
		onDraw();
	}
}