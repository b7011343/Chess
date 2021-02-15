#pragma once
#include "ChessBoard.h"

class MoveManager
{



public:
	static MoveManager* GetMoveManager();

	bool PieceOnMove(int newRow, int newCol);

	void LinkBoard(ChessBoard* board);



private:
	MoveManager();
	~MoveManager();

	static MoveManager* moveManager;
	ChessBoard* board;

};

