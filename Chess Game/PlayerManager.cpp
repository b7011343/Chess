#include "PlayerManager.h"

PlayerManager* PlayerManager::playerManager = nullptr;

PlayerManager::PlayerManager() : currentBlackPlayer(nullptr), currentWhitePlayer(nullptr), movesMade(0)
{
	timer = new Timer();
}

PlayerManager::~PlayerManager()
{}

void PlayerManager::CleanupMemory()
{
	delete timer;
	delete playerManager;
}

void PlayerManager::InitialiseGame(const char* player1Name, const char* player2Name)
{
	movesMade = 0;
	currentWhitePlayer = player1Name;
	currentBlackPlayer = player2Name;

	*timer = 0; // Reset timer time
	*timer = true; // Start timer
}

void PlayerManager::SaveResult(const char* winner)
{
	*timer = false; // Stop timer

	std::fstream hsFileOStream;
	
	hsFileOStream.open("Highscores.csv", std::ios::out | std::ios::app);

	/*
		CSV FORMAT:
			p1Name, p2Name, winerName, numberOfMoves, gameDuration
	*/

	hsFileOStream << currentWhitePlayer << ","
				 << currentBlackPlayer << ","
				 << winner << ","
				 << movesMade << ","
				 << timer->TimeStr() <<"\n";

	hsFileOStream.close();
}

std::vector<std::vector<std::string>> PlayerManager::GetSortedHighscores()
{
	std::vector<std::vector<std::string>> sortedHighscores;

	std::fstream hsFileIStream;

	hsFileIStream.open("Highscores.csv", std::ios::in);

	if (hsFileIStream.fail())
	{
		return sortedHighscores;
	}

	std::string line;

	while (std::getline(hsFileIStream, line))
	{
		std::vector<std::string> lineV;
		std::stringstream s(line);
		std::string data;

		while (std::getline(s, data, ','))
		{
			lineV.push_back(data);
		}

		sortedHighscores.push_back(lineV);
	}

	// Ordering records from lowest number of moves to highest
	std::sort(sortedHighscores.begin(), sortedHighscores.end(), CompareRecord);
	return sortedHighscores;
}