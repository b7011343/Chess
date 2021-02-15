#include "StartWindow.h"

StartWindow::StartWindow(HINSTANCE hInstance) : windowBusy(false), hInstance(hInstance), gameWindow(nullptr), highscoresWindow(nullptr)
{
	player1NameInput = new InputBox("P1", 230, 160, 300, 30);
	player2NameInput = new InputBox("P2", 230, 200, 300, 30);
	playButton = new Button<const char*>("Play", 70, EasyGraphics::DARK_GREEN, EasyGraphics::WHITE, 210, 290, 200, 60);
	highscoresButton = new Button<const char*>("Highscores", 30, EasyGraphics::DARK_GREY, EasyGraphics::WHITE, 210, 370, 200, 60);
	create(hInstance, WIN_WIDTH, WIN_HEIGHT, 100, true);
}

StartWindow::~StartWindow()
{
	delete player1NameInput;
	delete player2NameInput;
	delete playButton;
	delete highscoresButton;
	delete gameWindow;
	PlayerManager::GetPlayerManager()->CleanupMemory();
}

void StartWindow::onCreate()
{
	SetWindowTextA(getHWND(), "Chess - Menu (OOP4CS)");
	EasyGraphics::onCreate();
}

void StartWindow::onDraw()
{
	clearScreen(GREY);

	if (windowBusy)
	{
		setTextColour(BLACK);
		setFont(13, L"");
		drawText(L"Window busy, please close other windows to return to home menu...", 70, 220);
	}
	else
	{
		setTextColour(BLACK);
		setFont(100, L"");
		drawText(L"CHESS", 75, 10);
		drawBitmap(L".\\Images\\White\\King.bmp", 65, 153, 35, 35, 0x0000FF00);
		drawBitmap(L".\\Images\\Black\\King.bmp", 65, 193, 35, 35, 0x0000FF00);
		setFont(13, L"");
		drawText(L"Input your names if you wish them to be recorded in the high scores...", 55, 250);
		drawText(L"Player 1 Name: ", 100, 165);
		drawText(L"Player 2 Name: ", 100, 205);
		player1NameInput->Draw(this);
		player2NameInput->Draw(this);
		playButton->Draw(this);
		highscoresButton->Draw(this);
	}

	EasyGraphics::onDraw();
}

void StartWindow::Highscores()
{
	windowBusy = true;
	onDraw();
	highscoresWindow = new HighscoresWindow(hInstance);
	if (highscoresWindow)
	{
		highscoresWindow->waitForClose();
		delete highscoresWindow;
	}
	highscoresWindow = nullptr;
	windowBusy = false;
}

void StartWindow::PlayGame()
{
	windowBusy = true;
	onDraw();
	PlayerManager::GetPlayerManager()->InitialiseGame(player1NameInput->GetText(), player2NameInput->GetText());
	gameWindow = new GameWindow(hInstance);
	if (gameWindow)
	{
		gameWindow->waitForClose();
		delete gameWindow;
	}
	player1NameInput->Reset();
	player2NameInput->Reset();
	gameWindow = nullptr;
	windowBusy = false;
}

void StartWindow::onDestroy()
{
	delete gameWindow;
	gameWindow = nullptr;
	delete highscoresWindow;
	highscoresWindow = nullptr;
	EasyGraphics::onDestroy();
}