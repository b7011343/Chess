#include "Queen.h"

Queen::Queen(Team team, int initX, int initY) : GamePiece(team, initX, initY)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\Queen.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\Queen.bmp");
	}
	SetupPieceMoves();
}

Queen::~Queen() {}

void Queen::SetupPieceMoves()
{
	for (int i = 1; i < 8; i++)
	{
		AddMove(i, 0);
		AddMove(0, i);
		AddMove(-i, 0);
		AddMove(0, -i);
	}

	for (int i = 1; i < 8; i++)
	{
		AddMove(i, i);
		AddMove(-i, -i);
		AddMove(-i, i);
		AddMove(i, -i);
	}
}