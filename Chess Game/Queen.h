#pragma once

#include "GamePiece.h"

class Queen : public GamePiece
{
public:
	Queen(Team team, int initX, int initY);
	~Queen();

private:
	virtual void SetupPieceMoves();
};