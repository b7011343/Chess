#pragma once

#include "Entity.h"
#include <string>

class InputBox : public Entity
{
public:
	InputBox(const char* defaultText, int xPosition, int yPosition, int boxWidth, int boxHeight);
	~InputBox();
	void Draw(EasyGraphics* canvas);
	void ModifyText(UINT nChar);
	void Select(bool isSelected);
	bool IsSelected();
	const char* GetText();
	void Reset();

private:
	const static int MAX_NO_OF_CHARACTERS = 10;

	int currentLength;
	bool isSelected;
	char text[MAX_NO_OF_CHARACTERS + 1];
	const char* defaultText;
};

inline void InputBox::Select(bool isSelected)
{
	this->isSelected = isSelected;
}

inline bool InputBox::IsSelected()
{
	return isSelected;
}

inline const char* InputBox::GetText()
{
	if (currentLength > 0)
	{
		return text;
	}
	else
	{
		return defaultText;
	}
}

inline void InputBox::Reset()
{
	currentLength = 0;
	text[currentLength] = 0;
}