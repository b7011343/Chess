#pragma once

#include "EasyGraphics.h"
#include "PlayerManager.h"
#include "Button.h"

class HighscoresWindow : public EasyGraphics
{
public:
	HighscoresWindow(HINSTANCE hInstance);
	~HighscoresWindow();

private:
	static const int WIN_WIDTH = 740;
	static const int WIN_HEIGHT = 500;
	int hsStartIndex;
	Button<const wchar_t*>* scrollForward;
	Button<const wchar_t*>* scrollBackward;
	std::vector<std::vector<std::string>> highscores;

	virtual void onDraw();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onCreate();
	void DrawScores();
};

inline void HighscoresWindow::onDraw()
{
	clearScreen(EasyGraphics::GREY);
	scrollForward->Draw(this);
	scrollBackward->Draw(this);
	setTextColour(EasyGraphics::BLACK);
	setFont(50, L"");
	drawText(L"HIGHSCORES", 150, 10);
	DrawScores();
	EasyGraphics::onDraw();
}

inline void HighscoresWindow::onLButtonDown(UINT nFlags, int x, int y)
{
	if (scrollForward->Entity::MouseIsOver(x, y) && (hsStartIndex + 10) < highscores.size())
	{
		hsStartIndex += 10;
	}
	else if (scrollBackward->Entity::MouseIsOver(x, y) && hsStartIndex - 10 >= 0)
	{
		hsStartIndex -= 10;
	}
	onDraw();
}

inline void HighscoresWindow::onMouseMove(UINT nFlags, int x, int y)
{
	bool currentHoverStatusNext = scrollForward->IsMouseOver();
	if (scrollForward->Entity::MouseIsOver(x, y))
	{
		scrollForward->Hovering(true);
	}
	else
	{
		scrollForward->Hovering(false);
	}

	bool currentHoverStatusBack = scrollBackward->IsMouseOver();
	if (scrollBackward->Entity::MouseIsOver(x, y))
	{
		scrollBackward->Hovering(true);
	}
	else
	{
		scrollBackward->Hovering(false);
	}

	if (currentHoverStatusNext != scrollForward->IsMouseOver() || currentHoverStatusBack != scrollBackward->IsMouseOver())
	{
		onDraw();
	}
}