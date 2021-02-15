#include "ChessBoardTile.h"

ChessBoardTile::ChessBoardTile(int row, int column, int colour, int boxWidth, int boxHeight) : row(row), column(column), colour(colour), highlighted(false), Entity((GetX() + (boxWidth * column)), (GetY() + (boxHeight * row)), boxWidth, boxHeight)
{}

ChessBoardTile::~ChessBoardTile()
{
	if (pieceOnTile)
		delete pieceOnTile;
}

void ChessBoardTile::Draw(EasyGraphics* canvas)
{
	int tempColour = colour;
	if (highlighted)
	{
		colour = EasyGraphics::DARK_YELLLOW;
	}

	if (pieceOnTile && pieceOnTile->IsSelected())
	{
		canvas->setBackColour(colour);
		canvas->setPenColour(EasyGraphics::RED, 2);
		canvas->drawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), true);
		pieceOnTile->Draw(canvas);
	}
	else if (pieceOnTile)
	{
		canvas->setBackColour(colour);
		canvas->setPenColour(EasyGraphics::BLACK, 1);
		canvas->drawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), true);
		pieceOnTile->Draw(canvas);
	}
	else
	{
		canvas->setBackColour(colour);
		canvas->setPenColour(EasyGraphics::BLACK, 1);
		canvas->drawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), true);
	}
	colour = tempColour;
}