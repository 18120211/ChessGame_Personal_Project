#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#define ENTERKEY 13
#define ESCAPEKEY 27
#define DELETEKEY 8

class cTextBox
{
private:
	int LimitCharacter; //So luong ki tu gioi han
	sf::Text DisplayText;	//Chuoi the hien ra man hinh
	std::stringstream Text; //Chuoi cho nguoi dung nhap
	void InputLogic(int CharTyped); 
	void DeleteLastChar(); //Xoa ki tu cuoi cung;
public:
	bool IsSelected; //Thuoc tinh kiem tra xem o da duoc chon chua
	std::string getString();
	cTextBox();
	void setTextBox(sf::Font &font, int Size, sf::Vector2f Posittion, sf::Color Color, bool IsSelected);
	void setFont(sf::Font &Font);
	void setPosition(sf::Vector2f Position);
	void setSize(int size);
	void setColor(sf::Color color);
	void setLimitCharacter(int LimitCharacter);
	void draw(sf::RenderWindow &Window);
	void typeText(sf::Event Input);
	int getLimit();

};

