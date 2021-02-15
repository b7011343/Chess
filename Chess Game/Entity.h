#pragma once

#include "EasyGraphics.h"

class Entity
{
public:
	Entity(int xPosition, int yPosition, int boxWidth, int boxHeight);
	~Entity();
	virtual void Draw(EasyGraphics* canvas) = 0;
	int GetX();
	int GetY();
	bool MouseIsOver(int mX, int mY);

protected:
	int GetWidth();
	int GetHeight();
	void SetX(int x);
	void SetY(int y);
	
private:
	int xPosition, yPosition;
	int boxWidth, boxHeight;
};

inline int Entity::GetX() { return xPosition; }

inline int Entity::GetY() { return yPosition; }

inline int Entity::GetWidth() { return boxWidth; }

inline int Entity::GetHeight() { return boxHeight; }

inline void Entity::SetX(int x)
{
	xPosition = x;
}

inline void Entity::SetY(int y)
{
	yPosition = y;
}

inline bool Entity::MouseIsOver(int mX, int mY)
{
	mX -= xPosition;
	mY -= yPosition;
	return(mX >= 0 && mX < boxWidth && mY >= 0 && mY < boxHeight);
}