#pragma once

#include "GamePiece.h"

class King : public GamePiece
{
public:
	King(Team team, int initX, int initY);
	~King();
	void Check(bool isChecked);
	bool IsChecked();

private:
	bool isChecked;

	virtual void SetupPieceMoves();
};

