#include "Knight.h"

Knight::Knight(Team team, int initX, int initY) : GamePiece(team, initX, initY)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\Knight.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\Knight.bmp");
	}
	SetupPieceMoves();
}

Knight::~Knight() {}

void Knight::SetupPieceMoves()
{
	AddMove(-2, 1);
	AddMove(1, 2);
	AddMove(2, -1);
	AddMove(1, -2);
	AddMove(2, 1);
	AddMove(1, -2);
	AddMove(-2, -1);
	AddMove(-1, -2);
	AddMove(-1, 2);
	AddMove(-2, -1);
}