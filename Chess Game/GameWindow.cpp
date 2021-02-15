#include "GameWindow.h"

GameWindow::GameWindow(HINSTANCE hInstance)
{
	setImmediateDrawMode(false);
	board = new ChessBoard(100, 100);
	create(hInstance, WIN_WIDTH, WIN_HEIGHT, 100, false);
}

GameWindow::~GameWindow()
{
	killTimer(GAME_TIMER_ID);
	delete board;
	SendMessage(getHWND(), WM_CLOSE, 0, 0);
}

 void GameWindow::onCreate()
{
	 SetWindowTextA(getHWND(), "Chess - Play Game (OOP4CS)");
	 setTimer(GAME_TIMER_ID, 1000);
	 EasyGraphics::onCreate();
}

void GameWindow::DrawStats()
{
	// Player names
	drawBitmap(L".\\Images\\White\\King.bmp", 410, 1, 35, 35, 0x0000FF00);
	drawBitmap(L".\\Images\\Black\\King.bmp", 410, 45, 35, 35, 0x0000FF00);
	setFont(15, L"");
	setTextColour(EasyGraphics::BLACK);
	drawText(PlayerManager::GetPlayerManager()->GetPlayerName(GamePiece::WHITE_TEAM), 450, 10);
	drawText(L"vs", 450, 33);
	drawText(PlayerManager::GetPlayerManager()->GetPlayerName(GamePiece::BLACK_TEAM), 450, 56);

	// Current turn
	setFont(26, L"");
	setBackColour(EasyGraphics::GREY);
	setPenColour(EasyGraphics::BLACK, 3);
	drawRectangle(500, 150, 260, 60, true);
	const char* turnStr = (board->GetTurn() == GamePiece::WHITE_TEAM) ? "WHITE TURN" : "BLACK TURN";
	drawText(turnStr, 520, 160);

	// Time and move stats
	setFont(13, L"");
	drawRectangle(720, 10, 130, 75, true);
	drawText(PlayerManager::GetPlayerManager()->GetCurGameDuration().c_str(), 752, 20);
	drawText(std::to_string(PlayerManager::GetPlayerManager()->GetMovesMade()).c_str(), 780, 60);
	setFont(10, L"");
	drawText("Turns Completed:", 735, 45);
	
	// Message box
	drawRectangle(410, 285, 440, 100, true);
	setFont(13, L"");
	drawText(L"Latest Message:", 420, 295);
	setBackColour(EasyGraphics::WHITE);
	setPenColour(EasyGraphics::WHITE, 0);
	drawRectangle(420, 320, 420, 50, true);
	drawText(board->GetGameMessage(), 430, 335);
}