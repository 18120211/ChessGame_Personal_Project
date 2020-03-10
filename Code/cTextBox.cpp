#include "cTextBox.h"
using namespace std;
using namespace sf;


std::string cTextBox::getString()
{
	return this->Text.str();
}

cTextBox::cTextBox()
{
	this->LimitCharacter = 0;
	this->IsSelected = 0;
	//this->HasLimited = 0;
}

void cTextBox::setTextBox(sf::Font &font, int Size, sf::Vector2f Posittion,  sf::Color Color, bool IsSelected)
{
	this->DisplayText.setCharacterSize(Size);
	this->DisplayText.setPosition(Posittion);
	this->DisplayText.setFont(font);
	this->DisplayText.setFillColor(Color);
	this->IsSelected = IsSelected;
	if (IsSelected)
	{
		DisplayText.setString("[]");
	}
	else
	{
		DisplayText.setString("");
	}
}

void cTextBox::setFont(sf::Font & Font)
{
	this->DisplayText.setFont(Font);
}

void cTextBox::setPosition(sf::Vector2f Position)
{
	this->DisplayText.setPosition(Position);
}

void cTextBox::setSize(int size)
{
	this->DisplayText.setCharacterSize(size);
}

void cTextBox::setColor(sf::Color color)
{
	this->DisplayText.setFillColor(color);
}


void cTextBox::setLimitCharacter(int LimitCharacter)
{
	this->LimitCharacter = LimitCharacter;
}

void cTextBox::draw(sf::RenderWindow & Window)
{
	Window.draw(this->DisplayText);
}

int cTextBox::getLimit()
{
	return this->LimitCharacter;
}

void cTextBox::InputLogic(int charTyped)
{
	if (charTyped != DELETEKEY && charTyped != ENTERKEY && charTyped != ESCAPEKEY) {
		Text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETEKEY) {
		if (Text.str().length() > 0) {
			DeleteLastChar();
		}
	}
	DisplayText.setString(Text.str() + "[]");
}

void cTextBox::DeleteLastChar()
{
	string newT = Text.str();
	newT.erase(newT.end() - 1);
	Text.str("");
	Text << newT;
	DisplayText.setString(Text.str());
}

void cTextBox::typeText(Event input)
{
	if (this->IsSelected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (Text.str().length() <= this->LimitCharacter) {
				InputLogic(charTyped);
			}
			else if (Text.str().length() > this->LimitCharacter && charTyped == DELETEKEY) {
				DeleteLastChar();
			}
		}
	}
}