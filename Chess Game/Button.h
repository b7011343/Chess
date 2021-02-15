#pragma once

#include "Entity.h"
#include "EasyGraphics.h"

template <typename T>
class Button : public Entity
{
public:
	Button(T displayData, int textXOfset, int colour, int textColour, int xPosition, int yPosition, int boxWidth, int boxHeight);
	~Button();
	void Draw(EasyGraphics* canvas);
	void Hovering(bool mouseOver);
	bool IsMouseOver();

private:
	T displayData;
	int textXOfset;
	int textColour;
	int colour;
	bool mouseOver;
};

template <typename T>
Button<T>::Button(T displayData, int textXOfset, int colour, int textColour, int xPosition, int yPosition, int boxWidth, int boxHeight) : Entity(xPosition, yPosition, boxWidth, boxHeight), displayData(displayData), textXOfset(textXOfset), colour(colour), textColour(textColour), mouseOver(false)
{}

template <typename T>
Button<T>::~Button()
{}

template <typename T>
inline void Button<T>::Draw(EasyGraphics* canvas)
{
	canvas->setBackColour(colour);

	if (mouseOver)
	{
		canvas->setPenColour(EasyGraphics::BLACK, 4);
	}
	else
	{
		canvas->setPenColour(EasyGraphics::BLACK, 2);
	}

	canvas->drawRectangle(Entity::GetX(), Entity::GetY(), Entity::GetWidth(), Entity::GetHeight(), true);
	canvas->setFont(20, L"");
	canvas->setTextColour(textColour);

	if constexpr (std::is_same<T, const wchar_t*>::value)
	{
		// If button overlay is bitmap/image
		canvas->drawBitmap((const wchar_t*)displayData, Entity::GetX() + textXOfset, Entity::GetY(), 50, 50, 0x0000FF00);
	}
	else if constexpr (std::is_same<T, const char*>::value)
	{
		// If button overlay is text
		canvas->drawText(displayData, Entity::GetX() + textXOfset, Entity::GetY() + (Entity::GetHeight() / 4) - 3);
	}
}

template <typename T>
inline void Button<T>::Hovering(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

template <typename T>
inline bool Button<T>::IsMouseOver()
{
	return mouseOver;
}
