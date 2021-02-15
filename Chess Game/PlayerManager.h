#pragma once

#include "GamePiece.h"
#include "Timer.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

class PlayerManager
{
public:
	static PlayerManager* GetPlayerManager();
	void InitialiseGame(const char* player1Name, const char* player2Name);
	void CleanupMemory();
	const char* GetPlayerName(GamePiece::Team team);
	void SaveResult(const char* winner);
	std::vector<std::vector<std::string>> GetSortedHighscores();
	const void IncrementMoves();
	const void Tick();
	std::string GetCurGameDuration();
	int GetMovesMade();

private:
	static PlayerManager* playerManager;
	const char* currentWhitePlayer;
	const char* currentBlackPlayer;
	Timer* timer;
	int movesMade;

	PlayerManager();
	~PlayerManager();
	static bool CompareRecord(const std::vector<std::string>& record1, const std::vector<std::string>& record2);
};

inline PlayerManager* PlayerManager::GetPlayerManager()
{
	if (!playerManager)
	{
		playerManager = new PlayerManager();
	}
	return playerManager;
}

inline bool PlayerManager::CompareRecord(const std::vector<std::string>& record1, const std::vector<std::string>& record2)
{
	const int MOVE_INDEX = 3;
	return (std::stoi(record1[MOVE_INDEX]) < std::stoi(record2[MOVE_INDEX]));
}

inline const void PlayerManager::IncrementMoves()
{
	movesMade++;
}

inline const void PlayerManager::Tick()
{
	if (timer)
		*timer += 1;
}

inline std::string PlayerManager::GetCurGameDuration()
{
	return timer->TimeStr();
}

inline int PlayerManager::GetMovesMade()
{
	return movesMade;
}

inline const char* PlayerManager::GetPlayerName(GamePiece::Team team)
{
	return (team == GamePiece::BLACK_TEAM) ? currentBlackPlayer : currentWhitePlayer;
}