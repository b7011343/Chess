#include "Castle.h"

Castle::Castle(Team team, int initX, int initY) : GamePiece(team, initX, initY)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\Ruck.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\Ruck.bmp");
	}
	SetupPieceMoves();
}

Castle::~Castle() {}

void Castle::SetupPieceMoves()
{
	for (int i = 1; i < 8; i++)
	{
		AddMove(i, 0);
		AddMove(0, i);
		AddMove(-i, 0);
		AddMove(0, -i);
	}
}