#include "HighscoresWindow.h"

HighscoresWindow::HighscoresWindow(HINSTANCE hInstance) : hsStartIndex(0)
{
	setImmediateDrawMode(false);
	scrollForward = new Button<const wchar_t*>(L".\\Images\\NextArrow.bmp", 35, DARK_GREY, WHITE, 375, 365, 120, 50);
	scrollBackward = new Button<const wchar_t*>(L".\\Images\\BackArrow.bmp", 35, DARK_GREY, WHITE, 225, 365, 120, 50);
	highscores = PlayerManager::GetPlayerManager()->GetSortedHighscores();
	create(hInstance, WIN_WIDTH, WIN_HEIGHT, 100, false);
}

HighscoresWindow::~HighscoresWindow()
{
	delete scrollForward;
	delete scrollBackward;
	SendMessage(getHWND(), WM_CLOSE, 0, 0);
}

void HighscoresWindow::onCreate()
{
	SetWindowTextA(getHWND(), "Chess - Highscores (OOP4CS)");
	EasyGraphics::onCreate();
}

void HighscoresWindow::DrawScores()
{
	setTextColour(BLACK);
	setFont(10, L"");

	// Draw headings
	drawText("Player 1", 80, 100);
	drawText("Player 2", 230, 100);
	drawText("Winner", 380, 100);
	drawText("No. of Moves", 530, 100);
	drawText("Duration", 630, 100);

	// Draw table
	setPenColour(EasyGraphics::BLACK, 3);
	drawLine(10, 120, 715, 120);
	drawLine(75, 103, 75, 325);
	drawLine(225, 103, 225, 325);
	drawLine(375, 103, 375, 325);
	drawLine(525, 103, 525, 325);
	drawLine(625, 103, 625, 325);

	const int INCREMENT = 20;
	const int INITIAL_Y = 125;

	for (int i = hsStartIndex; i < hsStartIndex + 10 && i < highscores.size(); i++)
	{
		int y = INITIAL_Y + ((i - hsStartIndex) * INCREMENT);
		
		drawText("#", 10, y);
		drawText(std::to_string(i+1).c_str(), 17, y);
		drawText(highscores[i][0].c_str(), 80, y);
		drawText(highscores[i][1].c_str(), 230, y);
		drawText(highscores[i][2].c_str(), 380, y);
		drawText(highscores[i][3].c_str(), 530, y);
		drawText(highscores[i][4].c_str(), 630, y);
	}
}