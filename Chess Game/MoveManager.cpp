#include "MoveManager.h"

MoveManager* MoveManager::moveManager = nullptr;

MoveManager::MoveManager()
{

}

MoveManager::~MoveManager()
{
	delete moveManager;
}

MoveManager* MoveManager::GetMoveManager()
{
	if (!moveManager)
	{
		moveManager = new MoveManager();
	}
	return moveManager;
}

bool MoveManager::PieceOnMove(int newRow, int newCol)
{
	//return true;
	return board->getTile(newRow, newCol)->GetPiece() != nullptr;
}

void MoveManager::LinkBoard(ChessBoard* board)
{
	this->board = board;
}