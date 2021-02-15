#pragma once

#include "GamePiece.h"

class Knight : public GamePiece
{
public:
	Knight(Team team, int initX, int initY);
	~Knight();

private:
	virtual void SetupPieceMoves();
};