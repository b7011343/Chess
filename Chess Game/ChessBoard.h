#pragma once

#include "ChessBoardTile.h"
#include"GamePiece.h"
#include "Pawn.h"
#include "Castle.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <tuple>

class ChessBoard : public Entity
{
public:
	const static int NO_OF_ROWS = 8;
	const static int NO_OF_COLUMNS = 8;

	ChessBoard(int xPosition, int yPostition);
	~ChessBoard();
	void UpdateBoard(EasyGraphics* canvas, int mX, int mY);	
	void Draw(EasyGraphics* canvas);
	ChessBoardTile* GetTile(int row, int column);
	GamePiece::Team GetTurn();
	const char* GetGameMessage();

private: 
	const static int BOARD_TILE_WIDTH = 50;
	const static int BOARD_TILE_HEIGHT = 50;
	const static int MAX_MESSAGE_LENGTH = 100;

	ChessBoardTile* selectedTile;
	std::vector<ChessBoardTile*> boardTiles;
	GamePiece::Team currentMove;
	King* whiteKing;
	King* blackKing;
	const char* latestGameMessage;
	
	void SetupBoard();
	bool PieceInWay(ChessBoardTile* currentTile, ChessBoardTile* targetTile, bool ignoreKing);
	bool PieceInWay_Helper(int rowDirection, int colDirection, ChessBoardTile* startTile, ChessBoardTile* targetTile, bool ignoreKing);
	int GetDirectionValue(int movement);
	std::vector<std::tuple<int, int>> GetPossibleMoves(GamePiece* piece, int currentRow, int currentColumn, bool ignoreKing = false);
	std::vector<ChessBoardTile*> GetCheckedTiles(King* king);
	bool NotDoubleCheck(King* king, ChessBoardTile* newTile);
	ChessBoardTile* FindTile(GamePiece* piece);
	bool IsKingChecked(King* king);
	bool IsKingCheckMate(King* king);
	bool WouldKingBeChecked(King* king, ChessBoardTile* originalTile, ChessBoardTile* possibleTile);
	King* GetOppositeKing();
	King* GetCurrentKing();
	void ChangeTurn();
};

inline void ChessBoard::Draw(EasyGraphics* canvas)
{
	std::for_each(boardTiles.begin(), boardTiles.end(), [canvas](ChessBoardTile* t) { t->Draw(canvas); });
}

inline ChessBoardTile* ChessBoard::GetTile(int row, int column)
{
	// "boardTiles" is a vector of all tiles on the board, which are stored linearly.
	// This formula can return a given tile pointer from the data structure from a row and column number.
	return boardTiles[(column + (row * 8))];
}

inline King* ChessBoard::GetOppositeKing()
{
	return (currentMove == GamePiece::BLACK_TEAM) ? whiteKing : blackKing;
}

inline King* ChessBoard::GetCurrentKing()
{
	return (currentMove == GamePiece::WHITE_TEAM) ? whiteKing : blackKing;
}

inline void ChessBoard::ChangeTurn()
{
	currentMove = (currentMove == GamePiece::BLACK_TEAM) ? GamePiece::WHITE_TEAM : GamePiece::BLACK_TEAM;
}

inline GamePiece::Team ChessBoard::GetTurn()
{
	return currentMove;
}

inline const char* ChessBoard::GetGameMessage()
{
	return latestGameMessage;
}

inline bool ChessBoard::WouldKingBeChecked(King* king, ChessBoardTile* originalTile, ChessBoardTile* possibleTile)
{
	// Temporarily moves piece to possible location to determine if check would occur
	GamePiece* tempStartPiece = originalTile->GetPiece();
	GamePiece* tempDestinationPiece = possibleTile->GetPiece();
	originalTile->ChangePieceOnTile(nullptr);
	possibleTile->ChangePieceOnTile(tempStartPiece);
	bool wouldKingBeChecked = IsKingChecked(king);
	originalTile->ChangePieceOnTile(tempStartPiece);
	possibleTile->ChangePieceOnTile(tempDestinationPiece);
	return wouldKingBeChecked;
}

inline int ChessBoard::GetDirectionValue(int movement)
{
	if (movement > 0)
	{
		return 1;
	}
	else if (movement < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}