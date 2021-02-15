#include "GamePiece.h"

GamePiece::GamePiece(Team team, int initX, int initY) : team(team), taken(false), selected(false), Entity(initX, initY, 50, 50)
{}

GamePiece::~GamePiece()
{}