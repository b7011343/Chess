#include "Pawn.h"

Pawn::Pawn(Team team, int initX, int initY) : GamePiece(team, initX, initY), moved(false)
{
	if (team == GamePiece::WHITE_TEAM)
	{
		GamePiece::SetImage(L".\\Images\\White\\Pawn.bmp");
	}
	else // Black team
	{
		GamePiece::SetImage(L".\\Images\\Black\\Pawn.bmp");
	}
	SetupPieceMoves();
}

Pawn::~Pawn() {}

void Pawn::SetupPieceMoves()
{
	AddMove(1, 0);
}

void Pawn::Move(int newX, int newY)
{
	GamePiece::Move(newX, newY);
	moved = true;
}

bool Pawn::HasMoved()
{
	return moved;
}