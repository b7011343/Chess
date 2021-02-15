#pragma once

#include "GamePiece.h"

class Bishop : public GamePiece
{
public:
	Bishop(Team team, int initX, int initY);
	~Bishop();

private:
	virtual void SetupPieceMoves();
};

