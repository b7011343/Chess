#pragma once

#include "GamePiece.h"

class Pawn : public GamePiece
{
public:
	Pawn(Team team, int initX, int initY);
	~Pawn();
	bool HasMoved();
	virtual void Move(int newX, int newY);

private:
	bool moved;

	virtual void SetupPieceMoves();
};