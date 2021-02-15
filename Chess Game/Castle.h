#pragma once

#include "GamePiece.h"

class Castle : public GamePiece
{
public:
	Castle(Team team, int initX, int initY);
	~Castle();

private:
	virtual void SetupPieceMoves();
};

