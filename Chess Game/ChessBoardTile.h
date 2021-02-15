#pragma once

#include "GamePiece.h"
#include "Castle.h"
#include "Pawn.h"
#include "PlayerManager.h"

class ChessBoardTile : public Entity
{
public:
	ChessBoardTile(int row, int column, int colour, int boxWidth, int boxHeight);
	~ChessBoardTile();
	void Draw(EasyGraphics* canvas);
	int GetRow();
	int GetColumn();
	GamePiece* GetPiece();
	bool IsPossibleMove();
	void Highlight(bool status);
	void ChangePieceOnTile(GamePiece* newGamePiece);
	void MovePiece(ChessBoardTile* newTile);
	
private:
	int row, column, colour;
	bool highlighted;
	GamePiece* pieceOnTile; 
};

inline int ChessBoardTile::GetRow()
{
	return row;
}

inline int ChessBoardTile::GetColumn()
{
	return column;
}

inline GamePiece* ChessBoardTile::GetPiece()
{
	return pieceOnTile;
}

inline bool ChessBoardTile::IsPossibleMove()
{
	return highlighted;
}

inline void ChessBoardTile::Highlight(bool status)
{
	this->highlighted = status;
}

inline void ChessBoardTile::ChangePieceOnTile(GamePiece* newGamePiece)
{
	pieceOnTile = newGamePiece;
}

inline void ChessBoardTile::MovePiece(ChessBoardTile* newTile)
{
	if (newTile->GetPiece() == nullptr)
	{
		newTile->ChangePieceOnTile(pieceOnTile);
		pieceOnTile->Move(newTile->GetX(), newTile->GetY());
		pieceOnTile = nullptr;
	}
	else
	{
		delete newTile->GetPiece();
		newTile->ChangePieceOnTile(pieceOnTile);
		pieceOnTile->Move(newTile->GetX(), newTile->GetY());
		pieceOnTile = nullptr;
	}
}