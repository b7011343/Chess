#pragma once

#include "Entity.h"
#include <stdlib.h>
#include <tuple>
#include <vector>

class GamePiece : public Entity
{
public:
	static enum Team { BLACK_TEAM, WHITE_TEAM };

	GamePiece(Team team, int initX, int initY);
	~GamePiece();
	void Draw(EasyGraphics* canvas);
	void SetSelect(bool selected);
	bool IsSelected();
	Team GetTeam();
	std::vector<std::tuple<int, int>> GetPossibleMoves();
	virtual void Move(int newX, int newY);

protected:
	virtual void SetupPieceMoves() = 0;
	void AddMove(int rowChange, int colChange);
	void SetImage(const wchar_t* imageFile);

private:
	const static int TRANSPARENT_BG_COLOUR = 0x0000FF00;
	std::vector<std::tuple<int, int>> possibleMoves;
	Team team;
	bool taken;
	bool selected;
	const wchar_t* imageFile;
};

inline void GamePiece::Draw(EasyGraphics* canvas)
{
	canvas->drawBitmap(imageFile, Entity::GetX(), Entity::GetY(), Entity::GetWidth(), Entity::GetHeight(), TRANSPARENT_BG_COLOUR);
}

inline void GamePiece::SetImage(const wchar_t* imageFile)
{
	this->imageFile = imageFile;
}

inline void GamePiece::SetSelect(bool selected)
{
	this->selected = selected;
}

inline bool GamePiece::IsSelected()
{
	return selected;
}

inline void GamePiece::Move(int newX, int newY)
{
	Entity::SetX(newX);
	Entity::SetY(newY);
}

inline GamePiece::Team GamePiece::GetTeam()
{
	return team;
}

inline std::vector<std::tuple<int, int>> GamePiece::GetPossibleMoves()
{
	return possibleMoves;
}

inline void GamePiece::AddMove(int rowChange, int colChange)
{
	possibleMoves.push_back(std::make_tuple(rowChange, colChange));
}