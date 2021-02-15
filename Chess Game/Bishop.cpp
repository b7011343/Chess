#include "Bishop.h"

Bishop::Bishop(Team team, int initX, int initY) : GamePiece(team, initX, initY)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\Bishop.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\Bishop.bmp");
	}
	SetupPieceMoves();
}

Bishop::~Bishop() {}

void Bishop::SetupPieceMoves()
{
	for (int i = 1; i < 8; i++)
	{
		AddMove(i, i);
		AddMove(-i, -i);
		AddMove(-i, i);
		AddMove(i, -i);
	}
}