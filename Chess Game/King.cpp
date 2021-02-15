#include "King.h"

King::King(Team team, int initX, int initY) : GamePiece(team, initX, initY), isChecked(false)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\King.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\King.bmp");
	}
	SetupPieceMoves();
}

King::~King() {}

void King::SetupPieceMoves()
{
	AddMove(1, 0);
	AddMove(0, 1);
	AddMove(-1, 0);
	AddMove(0, -1);
	AddMove(1, 1);
	AddMove(-1, -1);
	AddMove(1, -1);
	AddMove(-1, 1);
}

void King::Check(bool isChecked)
{
	this->isChecked = isChecked;
}

bool King::IsChecked()
{
	return isChecked;
}
