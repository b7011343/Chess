#include "ChessBoard.h"

ChessBoard::ChessBoard(int xPosition, int yPostition) : Entity(xPosition, yPostition, 0, 0), latestGameMessage(nullptr), selectedTile(nullptr), currentMove(GamePiece::WHITE_TEAM)
{
	int colourTracker = EasyGraphics::WHITE;
	for (int rowIndex = 0; rowIndex < NO_OF_ROWS; rowIndex++)
	{
		for (int colIndex = 0; colIndex < NO_OF_COLUMNS; colIndex++)
		{
			boardTiles.push_back(new ChessBoardTile(rowIndex, colIndex, colourTracker, BOARD_TILE_WIDTH, BOARD_TILE_HEIGHT));
			colourTracker = (colourTracker == EasyGraphics::WHITE) ? EasyGraphics::GREY : EasyGraphics::WHITE;
		}
		colourTracker = (colourTracker == EasyGraphics::WHITE) ? EasyGraphics::GREY : EasyGraphics::WHITE;
	}
	SetupBoard();
}

ChessBoard::~ChessBoard()
{
	std::for_each(boardTiles.begin(), boardTiles.end(), [](ChessBoardTile* t) { delete t; });
	delete latestGameMessage;
}

void ChessBoard::SetupBoard()
{
	// Kings
	whiteKing = new King(GamePiece::WHITE_TEAM, GetTile(0, 4)->GetX(), GetTile(0, 4)->GetY());
	blackKing = new King(GamePiece::BLACK_TEAM, GetTile(7, 4)->GetX(), GetTile(7, 4)->GetY());
	GetTile(0, 4)->ChangePieceOnTile(whiteKing);
	GetTile(7, 4)->ChangePieceOnTile(blackKing);

	// Pawns
	for (int i = 0; i < NO_OF_COLUMNS; i++)
	{
		GetTile(1, i)->ChangePieceOnTile(new Pawn(GamePiece::WHITE_TEAM, GetTile(1, i)->GetX(), GetTile(1, i)->GetY()));
		GetTile(6, i)->ChangePieceOnTile(new Pawn(GamePiece::BLACK_TEAM, GetTile(6, i)->GetX(), GetTile(6, i)->GetY()));
	}

	// Rucks/Castles
	GetTile(0, 0)->ChangePieceOnTile(new Castle(GamePiece::WHITE_TEAM, GetTile(0, 0)->GetX(), GetTile(0, 0)->GetY()));
	GetTile(0, 7)->ChangePieceOnTile(new Castle(GamePiece::WHITE_TEAM, GetTile(0, 7)->GetX(), GetTile(0, 7)->GetY()));
	GetTile(7, 0)->ChangePieceOnTile(new Castle(GamePiece::BLACK_TEAM, GetTile(7, 0)->GetX(), GetTile(7, 0)->GetY()));
	GetTile(7, 7)->ChangePieceOnTile(new Castle(GamePiece::BLACK_TEAM, GetTile(7, 7)->GetX(), GetTile(7, 7)->GetY()));
	
	// Bishops
	GetTile(0, 2)->ChangePieceOnTile(new Bishop(GamePiece::WHITE_TEAM, GetTile(0, 2)->GetX(), GetTile(0, 2)->GetY()));
	GetTile(0, 5)->ChangePieceOnTile(new Bishop(GamePiece::WHITE_TEAM, GetTile(0, 5)->GetX(), GetTile(0, 5)->GetY()));
	GetTile(7, 2)->ChangePieceOnTile(new Bishop(GamePiece::BLACK_TEAM, GetTile(7, 2)->GetX(), GetTile(7,2 )->GetY()));
	GetTile(7, 5)->ChangePieceOnTile(new Bishop(GamePiece::BLACK_TEAM, GetTile(7, 5)->GetX(), GetTile(7, 5)->GetY()));

	// Queens
	GetTile(0, 3)->ChangePieceOnTile(new Queen(GamePiece::WHITE_TEAM, GetTile(0, 3)->GetX(), GetTile(0, 3)->GetY()));
	GetTile(7, 3)->ChangePieceOnTile(new Queen(GamePiece::BLACK_TEAM, GetTile(7, 3)->GetX(), GetTile(7, 3)->GetY()));

	// Kights
	GetTile(0, 1)->ChangePieceOnTile(new Knight(GamePiece::WHITE_TEAM, GetTile(0, 1)->GetX(), GetTile(0, 1)->GetY()));
	GetTile(0, 6)->ChangePieceOnTile(new Knight(GamePiece::WHITE_TEAM, GetTile(0, 6)->GetX(), GetTile(0, 6)->GetY()));
	GetTile(7, 1)->ChangePieceOnTile(new Knight(GamePiece::BLACK_TEAM, GetTile(7, 1)->GetX(), GetTile(7, 1)->GetY()));
	GetTile(7, 6)->ChangePieceOnTile(new Knight(GamePiece::BLACK_TEAM, GetTile(7, 6)->GetX(), GetTile(7, 6)->GetY()));
}

void ChessBoard::UpdateBoard(EasyGraphics* canvas, int mX, int mY)
{
	bool tileClicked = false;

	for (int tile = 0; tile < boardTiles.size(); tile++)
	{
		ChessBoardTile* currentTile = boardTiles[tile];

		// Piece on "selectedTile" is being moved to "currentTile"
		if (selectedTile != nullptr && currentTile->IsPossibleMove() && currentTile->Entity::MouseIsOver(mX, mY))
		{
			selectedTile->MovePiece(currentTile);
			
			if (currentMove == GamePiece::BLACK_TEAM)
			{
				PlayerManager::GetPlayerManager()->IncrementMoves();
			}

			selectedTile = currentTile;
			for (int i2 = 0; i2 < boardTiles.size(); i2++)
			{
				boardTiles[i2]->Highlight(false);
				if (boardTiles[i2]->GetPiece() != nullptr)
				{
					boardTiles[i2]->GetPiece()->SetSelect(false);
				}
			}

			tileClicked = true;

			if (IsKingChecked(GetOppositeKing()))
			{
				if (IsKingCheckMate(GetOppositeKing()))
				{
					// End game / check mate
					GetOppositeKing()->Check(true);
					char message[MAX_MESSAGE_LENGTH];
					strcpy_s(message, PlayerManager::GetPlayerManager()->GetPlayerName(GetOppositeKing()->GetTeam()));
					strcat_s(message, ", your king is in check mate. ");
					strcat_s(message, PlayerManager::GetPlayerManager()->GetPlayerName(GetCurrentKing()->GetTeam()));
					strcat_s(message, " wins!\0");

					if (latestGameMessage)
					{
						delete latestGameMessage;
					}
					latestGameMessage = _strdup(message);
					PlayerManager::GetPlayerManager()->SaveResult(PlayerManager::GetPlayerManager()->GetPlayerName(GetCurrentKing()->GetTeam()));
				}
				else
				{
					// Place opposition's king into check
					GetOppositeKing()->Check(true);
					char message[MAX_MESSAGE_LENGTH];
				    strcpy_s(message, PlayerManager::GetPlayerManager()->GetPlayerName(GetOppositeKing()->GetTeam()));
					strcat_s(message, ", your king is in check.\0");
					if (latestGameMessage)
					{
						delete latestGameMessage;
					}
					latestGameMessage = _strdup(message);
				}
			}
			else
			{
				GetOppositeKing()->Check(false);
				delete latestGameMessage;
				latestGameMessage = nullptr;
			}

			if (GetCurrentKing()->IsChecked() && !IsKingChecked(GetCurrentKing()))
			{
				GetCurrentKing()->Check(false);
				delete latestGameMessage;
				latestGameMessage = nullptr;
			}

			ChangeTurn();
			break;
		}
		// Piece/tile is selected
		else if (currentTile->GetPiece() != nullptr && currentTile->GetPiece()->Entity::MouseIsOver(mX, mY) && currentTile->GetPiece()->GetTeam() == currentMove)
		{
			selectedTile = currentTile;
		
			for (int i2 = 0; i2 < boardTiles.size(); i2++)
			{
				boardTiles[i2]->Highlight(false);
				if (boardTiles[i2]->GetPiece() != nullptr)
				{
					boardTiles[i2]->GetPiece()->SetSelect(false);
				}
			}

			currentTile->GetPiece()->SetSelect(true);
			tileClicked = true;
	
			auto possibleMoves = GetPossibleMoves(currentTile->GetPiece(), currentTile->GetRow(), currentTile->GetColumn());
			for (int i2 = 0; i2 < possibleMoves.size(); i2++)
			{
				int row = std::get<0>(possibleMoves[i2]);
				int column = std::get<1>(possibleMoves[i2]);
				if ((GetTile(row, column)->GetPiece() == nullptr || (currentTile->GetPiece() != nullptr && GetTile(row, column)->GetPiece() != nullptr && currentTile->GetPiece()->GetTeam() != GetTile(row, column)->GetPiece()->GetTeam())) && !WouldKingBeChecked(GetCurrentKing(), currentTile, GetTile(row, column)))
				{
					GetTile(row, column)->Highlight(true);
				}
			}
			break;
		}
	}

	// If the user has clicked, but not hit any clickable screen element
	if (!tileClicked)
	{
		for (int i2 = 0; i2 < boardTiles.size(); i2++)
		{
			boardTiles[i2]->Highlight(false);
			if (boardTiles[i2]->GetPiece() != nullptr)
			{
				boardTiles[i2]->GetPiece()->SetSelect(false);
			}
		}
	}

	Draw(canvas);
}

std::vector<std::tuple<int, int>> ChessBoard::GetPossibleMoves(GamePiece* piece, int currentRow, int currentColumn, bool ignoreKing) //= false
{
	std::vector<std::tuple<int, int>> availableMoves;

	int direction = (piece->GetTeam() == GamePiece::BLACK_TEAM) ? -1 : 1;

	Pawn* possiblePawn = dynamic_cast<Pawn*>(piece);

	/* Pawns must be treated differently to all other pieces, as their moves can differ depending on
		the positions of other pieces around it, and whether is has moved already */
	if (possiblePawn != nullptr)
	{
		//If not moved (+2, 0) and no piece 2 places in front
		if (!possiblePawn->HasMoved() && currentRow + (2 * direction) > -1 && currentRow + (2 * direction) < NO_OF_ROWS && GetTile(currentRow + (1 * direction), currentColumn)->GetPiece() == nullptr && GetTile(currentRow + (2 * direction), currentColumn)->GetPiece() == nullptr && !ignoreKing)
		{
			availableMoves.push_back(std::make_tuple(currentRow + (2 * direction), currentColumn));
		}

		//If no piece in front (+1, 0)
		if (currentRow + (1 * direction) > -1 && currentRow + (1 * direction) < NO_OF_ROWS && GetTile(currentRow + (1 * direction), currentColumn)->GetPiece() == nullptr && !ignoreKing)
		{
			availableMoves.push_back(std::make_tuple(currentRow + (1 * direction), currentColumn));
		}

		//If piece at (+1, -1), add (+1, -1)
		if (currentRow + (1 * direction) > -1 && currentRow + (1 * direction) < NO_OF_ROWS && currentColumn -1 > -1 && (GetTile(currentRow + (1 * direction), currentColumn - 1)->GetPiece() != nullptr || ignoreKing))
		{
			availableMoves.push_back(std::make_tuple(currentRow + (1 * direction), currentColumn - 1));
		}

		//If piece at (+1, +1), add (+1, +1)
		if (currentRow + (1 * direction) > -1 && currentRow + (1 * direction) < NO_OF_ROWS && currentColumn + 1 < NO_OF_COLUMNS && (GetTile(currentRow + (1 * direction), currentColumn + 1)->GetPiece() != nullptr || ignoreKing))
		{
			availableMoves.push_back(std::make_tuple(currentRow + (1 * direction), currentColumn + 1));
		}

	}
	else
	{
		King* possibleKing = dynamic_cast<King*>(piece);
		std::vector<ChessBoardTile*> checkedTiles;
		if (!ignoreKing && possibleKing)
		{	
			checkedTiles = GetCheckedTiles(possibleKing);
		}

		for (int i = 0; i < piece->GetPossibleMoves().size(); i++)
		{
			int newRow = currentRow + (std::get<0>(piece->GetPossibleMoves()[i]) * direction);
			int newCol = currentColumn + std::get<1>(piece->GetPossibleMoves()[i]);
			ChessBoardTile* t = nullptr;

			if (ignoreKing)
			{
				t = FindTile(piece);
			}
			else
			{
				t = selectedTile;
			}
		
			if (newRow > -1 && newRow < NO_OF_ROWS && newCol > -1 && newCol < NO_OF_COLUMNS && !PieceInWay(t, GetTile(newRow, newCol), (ignoreKing)))
			{
				// If piece is a king, dont allow it to move into check
				if (possibleKing != nullptr)
				{
					ChessBoardTile* possibleMove = GetTile(newRow, newCol);
					if (checkedTiles.size() > 0 && (std::find(checkedTiles.begin(), checkedTiles.end(), possibleMove) == checkedTiles.end()) && NotDoubleCheck(possibleKing, GetTile(newRow, newCol)))
					{
						std::tuple<int, int> move = std::make_tuple(newRow, newCol);
						availableMoves.push_back(move);
					}
				}
				else
				{
					std::tuple<int, int> move = std::make_tuple(newRow, newCol);
					availableMoves.push_back(move);
				}
			}
		}
	}
	return availableMoves;
}

bool ChessBoard::PieceInWay(ChessBoardTile* currentTile, ChessBoardTile* tarGetTile, bool ignoreKing)
{
	int curTileRow = currentTile->GetRow();
	int curTileCol = currentTile->GetColumn();
	int tarTileRow = tarGetTile->GetRow();
	int tarTileCol = tarGetTile->GetColumn();

	int rowMovement = tarTileRow - curTileRow;
	int colMovement = tarTileCol - curTileCol;

	//Diagnal, vertical or horizontal movement
	if (abs(rowMovement) == abs(colMovement) || rowMovement == 0 || colMovement == 0)
	{
		return PieceInWay_Helper(GetDirectionValue(rowMovement), GetDirectionValue(colMovement), currentTile, tarGetTile, ignoreKing);
	}
	//Jump style movement (e.g. knight)
	else
	{
		return false;
	}
}

bool ChessBoard::PieceInWay_Helper(int rowDirection, int colDirection, ChessBoardTile* startTile, ChessBoardTile* tarGetTile, bool ignoreKing) // remove ignore king
{
	ChessBoardTile* currentTile = startTile;

	while (currentTile != tarGetTile)
	{
		int curRow = currentTile->GetRow();
		int curCol = currentTile->GetColumn();
		currentTile = GetTile(curRow + rowDirection, curCol + colDirection);

		if (currentTile != tarGetTile && dynamic_cast<King*>(currentTile->GetPiece()) && currentTile->GetPiece()->GetTeam() != startTile->GetPiece()->GetTeam())
		{
			return false;
		}

		// If collision
		if (currentTile != tarGetTile && currentTile->GetPiece() != nullptr || currentTile->GetPiece() != nullptr && currentTile == tarGetTile && (currentTile->GetPiece()->GetTeam() == startTile->GetPiece()->GetTeam())) 
		{
			return true;
		}
	}
	return false;
}

ChessBoardTile* ChessBoard::FindTile(GamePiece* piece)
{
	std::vector<ChessBoardTile*>::iterator it;
	it = std::find_if(boardTiles.begin(), boardTiles.end(), 
		[piece](ChessBoardTile* t) { return t->GetPiece() != nullptr && t->GetPiece() == piece; });

	if (it == boardTiles.end())
	{
		return nullptr;
	}
	else
	{
		return *it;
	}
}

std::vector<ChessBoardTile*> ChessBoard::GetCheckedTiles(King* king)
{
	std::vector<ChessBoardTile*> checkedTiles;
	for (int i = 0; i < boardTiles.size(); i++)
	{
		if (boardTiles[i]->GetPiece() != nullptr && boardTiles[i]->GetPiece()->GetTeam() != king->GetTeam())
		{
			std::vector<std::tuple<int, int>> pieceMoves = GetPossibleMoves(boardTiles[i]->GetPiece(), boardTiles[i]->GetRow(), boardTiles[i]->GetColumn(), true);
			for (int i2 = 0; i2 < pieceMoves.size(); i2++)
			{
				ChessBoardTile* tile = GetTile(std::get<0>(pieceMoves[i2]), std::get<1>(pieceMoves[i2]));
				checkedTiles.push_back(tile);
			}
		}
	}
	return checkedTiles;
}

bool ChessBoard::NotDoubleCheck(King* king, ChessBoardTile* newTile)
{
	// Gets executed to assure king doesn't put itself in check while checking opposite king
	
	int direction = (king->GetTeam() == GamePiece::BLACK_TEAM) ? -1 : 1;
	int row = newTile->GetRow();
	int col = newTile->GetColumn();

	for (int i = 0; i < king->GetPossibleMoves().size(); i++)
	{
		int newRow = row + (std::get<0>(king->GetPossibleMoves()[i]) * direction);
		int newCol = col + std::get<1>(king->GetPossibleMoves()[i]);
		if (newRow > -1 && newRow < NO_OF_ROWS && newCol > -1 && newCol < NO_OF_COLUMNS)
		{
			ChessBoardTile* tileToCheck = GetTile(newRow, newCol);
			if (tileToCheck->GetPiece() != nullptr && tileToCheck->GetPiece() != king && dynamic_cast<King*>(tileToCheck->GetPiece()))
			{
				return false;
			}
		}
	}
	return true;
}

bool ChessBoard::IsKingChecked(King* king)
{
	std::vector<ChessBoardTile*> checkedTiles = GetCheckedTiles(king);
	ChessBoardTile* kingsTile = FindTile(king);
	return (std::find(checkedTiles.begin(), checkedTiles.end(), kingsTile) != checkedTiles.end());
}

bool ChessBoard::IsKingCheckMate(King* king)
{
	ChessBoardTile* kingsTile = FindTile(king);
	int kingRow = kingsTile->GetRow();
	int kingCol = kingsTile->GetColumn();
	selectedTile = kingsTile;

	ChessBoardTile* tempSelectedTile = selectedTile;
	
	int noOfPossibleMoves = 0;

	for (int i = 0; i < boardTiles.size(); i++)
	{
		if (boardTiles[i]->GetPiece() != nullptr && boardTiles[i]->GetPiece()->GetTeam() == king->GetTeam())
		{
			selectedTile = boardTiles[i];
			auto possibleMoves = GetPossibleMoves(boardTiles[i]->GetPiece(), boardTiles[i]->GetRow(), boardTiles[i]->GetColumn());
			for (int i2 = 0; i2 < possibleMoves.size(); i2++)
			{
				int row = std::get<0>(possibleMoves[i2]);
				int col = std::get<1>(possibleMoves[i2]);;
				if (!WouldKingBeChecked(king, boardTiles[i], GetTile(row, col)))
				{
					noOfPossibleMoves++;
				}
			}
		}
	}

	bool kingCheckMate = IsKingChecked(king) && noOfPossibleMoves == 0;
	selectedTile = tempSelectedTile;
	return kingCheckMate;
}