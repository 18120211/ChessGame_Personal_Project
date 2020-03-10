#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

class BeginWindow
{
private:
	int option = 0;
public:
	int OpenWindow() {
		sf::RenderWindow window(sf::VideoMode(1000, 800), "uou");
		sf::Event event;
		sf::RectangleShape background;
		sf::Texture * texture = new sf::Texture;
		texture->loadFromFile("background.jpg");
		texture->setSmooth(true);
		background.setTexture(texture);
		background.setSize(sf::Vector2f(1000, 800));
		sf::Text text[5];
		sf::Font font;
		font.loadFromFile("OCRAEXT.TTF");
		text[0].setFont(font);
		text[1].setFont(font);
		text[2].setFont(font);
		text[3].setFont(font);
		text[4].setFont(font);
		text[0].setString("> Player 1 vs Player 2");
		text[1].setString("Play with Computer(Easy)");
		text[2].setString("Play with Computer(Hard)");
		text[3].setString("Exit");
		text[4].setString("CHESSGAME");
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);
		text[0].setCharacterSize(30);
		text[1].setCharacterSize(30);
		text[2].setCharacterSize(30);
		text[3].setCharacterSize(30);
		text[4].setCharacterSize(100);
		text[0].setPosition(350, 370);
		text[1].setPosition(350, 420);
		text[2].setPosition(350, 470);
		text[3].setPosition(350, 520);
		text[4].setPosition(280, 150);
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case::sf::Event::KeyPressed: {
					if (event.key.code == sf::Keyboard::Down) {
						std::string tmp;
						tmp = text[option].getString();
						tmp.erase(tmp.begin());
						tmp.erase(tmp.begin());
						text[option].setString(tmp);
						if (option == 3) {
							option = 0;
						}
						else {
							option += 1;
						}
						tmp = text[option].getString();
						tmp = "> " + tmp;
						text[option].setString(tmp);
					}
					else if (event.key.code == sf::Keyboard::Up) {
						std::string tmp;
						tmp = text[option].getString();
						tmp.erase(tmp.begin());
						tmp.erase(tmp.begin());
						text[option].setString(tmp);
						if (option == 0) {
							option = 3;
						}
						else {
							option -= 1;
						}
						tmp = text[option].getString();
						tmp = "> " + tmp;
						text[option].setString(tmp);
					}
					else if (event.key.code == sf::Keyboard::Enter) {
						window.close();
						return option;
					}
					break;
				}
				case::sf::Event::Closed: {
					window.close();
					break;
				}
				}
			}
			window.clear();
			window.draw(background);
			for (int i = 0; i < 5; ++i) {
				window.draw(text[i]);
			}
			window.display();
		}
		return option;
	}
};

