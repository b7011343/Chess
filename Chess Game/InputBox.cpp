#include "InputBox.h"

InputBox::InputBox(const char* defaultText, int xPosition, int yPosition, int boxWidth, int boxHeight) : Entity(xPosition, yPosition, boxWidth, boxHeight), currentLength(0), text(""), isSelected(false), defaultText(defaultText)
{}

InputBox::~InputBox()
{}

void InputBox::Draw(EasyGraphics* canvas)
{
	canvas->setBackColour(EasyGraphics::WHITE);

	if (isSelected)
	{
		canvas->setPenColour(EasyGraphics::BLACK, 4);
	}
	else
	{
		canvas->setPenColour(EasyGraphics::BLACK, 2);
	}
	canvas->drawRectangle(Entity::GetX(), Entity::GetY(), Entity::GetWidth(), Entity::GetHeight(), true);

	canvas->setFont(12, L"");

	const char* displayText;

	if (currentLength == 0)
	{
		canvas->setTextColour(EasyGraphics::DARK_GREY);
		displayText = defaultText;
	}
	else
	{
		canvas->setTextColour(EasyGraphics::BLACK);
		displayText = text;
	}
	canvas->drawText(displayText, Entity::GetX() + 5, Entity::GetY() + (Entity::GetHeight()/4)-2);
}

void InputBox::ModifyText(UINT nChar)
{
	// Backspace character
	if (nChar == 8 && currentLength > 0)
	{
		text[currentLength-1] = 0;
		currentLength--;
	}
	else if (nChar != 8 && currentLength < MAX_NO_OF_CHARACTERS)
	{
		text[currentLength] = nChar;
		text[currentLength + 1] = 0;
		currentLength++;
	}
	
}