#include <iostream>
#include "SFML/Graphics.hpp"
#include "cTextBox.h"
#include "cChessMan.h"
#include "BeginWindow.h"
#include <vector>

int ChessBoard[64] = { 1, 2, 3, 4, 5, 3, 2, 1,
						 6, 6, 6, 6, 6, 6, 6, 6, 
						 0, 0, 0, 0, 0, 0, 0, 0,						
						 0, 0, 0, 0, 0, 0, 0, 0,						
						 0, 0, 0, 0, 0, 0, 0, 0,						
						 0, 0, 0, 0, 0, 0, 0, 0,						
						 -1, -2, -3, -4, -5, -3, -2, -1,
						 -6, -6, -6, -6, -6, -6, -6, -6};

class Player
{
public:
	cChessMan *ChessMan[16];
	std::string PlayerName;
	int point = 0;
	PLAYER player;
};

class MasterGame
{
private:
	Player player1;
	Player player2;
	bool Free[8][8];
	bool dragging[32];
	int turn = 0;
	int winner;
public:

	MasterGame() {
		player1.player = PLAYER1;
		player1.PlayerName = "VO THE MINH";
		player1.ChessMan[0] = new cCar; player1.ChessMan[7] = new cCar; 
		player1.ChessMan[1] = new cKnight; player1.ChessMan[6] = new cKnight;
		player1.ChessMan[2] = new cBisopp; player1.ChessMan[5] = new cBisopp;
		player1.ChessMan[3] = new cQueen;
		player1.ChessMan[4] = new cKing;
		player1.ChessMan[8] = new cPawn; player1.ChessMan[9] = new cPawn; player1.ChessMan[10] = new cPawn;
		player1.ChessMan[11] = new cPawn; player1.ChessMan[12] = new cPawn; player1.ChessMan[13] = new cPawn;
		player1.ChessMan[14] = new cPawn; player1.ChessMan[15] = new cPawn;

		player2.player = PLAYER2;
		player2.PlayerName = "NGUYEN THUY DUONG";
		player2.ChessMan[0] = new cCar; player2.ChessMan[7] = new cCar;
		player2.ChessMan[1] = new cKnight; player2.ChessMan[6] = new cKnight;
		player2.ChessMan[2] = new cBisopp; player2.ChessMan[5] = new cBisopp;
		player2.ChessMan[3] = new cKing;
		player2.ChessMan[4] = new cQueen;
		player2.ChessMan[8] = new cPawn; player2.ChessMan[9] = new cPawn; player2.ChessMan[10] = new cPawn;
		player2.ChessMan[11] = new cPawn; player2.ChessMan[12] = new cPawn; player2.ChessMan[13] = new cPawn;
		player2.ChessMan[14] = new cPawn; player2.ChessMan[15] = new cPawn;

		for (int i = 0; i < 16; ++i) {
			player1.ChessMan[i]->player = PLAYER1;
			player1.ChessMan[i]->originX = OneCell * (i % 8);
			player1.ChessMan[i]->originY = OneCell * (i / 8);
			player1.ChessMan[i]->setPosition(sf::Vector2f(OneCell * (i % 8), OneCell * (i / 8)));
			player1.ChessMan[i]->setImageChess();

			player2.ChessMan[15 - i]->player = PLAYER2;
			player2.ChessMan[15 - i]->originX = OneCell * (i % 8);
			player2.ChessMan[15 - i]->originY = OneCell * ((i / 8) + 6);
			player2.ChessMan[15 - i]->setPosition(sf::Vector2f(OneCell * (i % 8), OneCell * ((i / 8) + 6)));
			player2.ChessMan[15 - i]->setImageChess();
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				Free[i][j] = 1;
				if (i == 0 || i == 1 || i == 6 || i == 7) {
					Free[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < 32; ++i) {
			dragging[i] = 0;
		}
	}
	int PlayeGame() {
		sf::RenderWindow window(sf::VideoMode(8 * OneCell, 8 * OneCell), "ChessGame");

		sf::Texture *texture = new sf::Texture;
		texture->loadFromFile("ChessBoard.png");
		texture->setSmooth(true);
		sf::RectangleShape background;
		background.setTexture(texture);
		background.setSize(sf::Vector2f(8 * OneCell, 8 * OneCell));
		background.setPosition(sf::Vector2f(0, 0));

		sf::Event event;
		bool MouseClick = 0;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case::sf::Event::Closed:{
					window.close();
					break;
				}
				case::sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Left) {
						MouseClick = 1;
					}
					if (turn % 2 == 0) {
						for (int i = 0; i < 16; ++i) {
							if (player1.ChessMan[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								dragging[i] = 1;
							}
						}
					}
					else if (turn % 2 == 1) {
						for (int i = 0; i < 16; ++i) {
							if (player2.ChessMan[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								dragging[i + 16] = 1;
							}
						}
					}
					break;
				}
				case::sf::Event::MouseMoved: {
					std::cout << Free[sf::Mouse::getPosition(window).y / int(OneCell)][sf::Mouse::getPosition(window).x / int(OneCell)] << " ";
					std::cout << sf::Mouse::getPosition(window).y / OneCell << " " << sf::Mouse::getPosition(window).x / OneCell << std::endl;
					if (MouseClick) {
						if (turn % 2 == 0) {
							for (int i = 0; i < 16; ++i) {
								if (dragging[i]) {
									player1.ChessMan[i]->setPosition(sf::Mouse::getPosition(window).x - OneCell/ 2,
										sf::Mouse::getPosition(window).y - OneCell / 2);
								}
							}
						}
						else if (turn % 2 == 1) {
							for (int i = 0; i < 16; ++i) {
								if (dragging[i + 16]) {
									player2.ChessMan[i]->setPosition(sf::Mouse::getPosition(window).x - OneCell / 2,
										sf::Mouse::getPosition(window).y - OneCell / 2);
								}
							}
						}
					}
					break;
				}
				case::sf::Event::MouseButtonReleased: {
					int mousex = event.mouseButton.x;
					int mousey = event.mouseButton.y;
					if (turn % 2 == 0) {	
						for (int i = 0; i < 16; ++i) {
							if (dragging[i]) {
								for (int j = 0; j < 32; ++j) {
									dragging[j] = 0;
								}
								if (player1.ChessMan[i]->checkNextMove(Free, 1)) {
									if (Free[mousey / OneCell][mousex / OneCell]) {
										Free[player1.ChessMan[i]->originY / OneCell][player1.ChessMan[i]->originX / OneCell] = 1;
										Free[mousey / OneCell][mousex / OneCell] = 0;
										player1.ChessMan[i]->update();
										turn += 1;
										break;
									}
									else {
										for (int j = 0; j < 16; ++j) {
											if (i == j) {
												continue;
											}
											if (player1.ChessMan[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												player1.ChessMan[i]->backToPriviousStep();
												break;
											}
										}
										for (int j = 0; j < 16; ++j) {
											if (player2.ChessMan[j]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												Free[player1.ChessMan[i]->originY / OneCell][player1.ChessMan[i]->originX / OneCell] = 1;
												Free[mousey / OneCell][mousex / OneCell] = 0;
												player1.ChessMan[i]->setPosition(mousex - OneCell / 2, mousey - OneCell / 2);
												player1.ChessMan[i]->update();
												player2.ChessMan[j]->setPosition(-100, -100);
												turn += 1;
												break;
											}
										}
									}
									break;
								}
								else {
									player1.ChessMan[i]->backToPriviousStep();

								}
							}
						}
					}
					else if (turn % 2 == 1) {
						MouseClick = 0;
						for (int i = 0; i < 16; ++i) {
							if (dragging[i + 16]) {
								for (int j = 0; j < 32; ++j) {
									dragging[j] = 0;
								}
								if (player2.ChessMan[i]->checkNextMove(Free, 1)) {
									if (Free[mousey / OneCell][mousex / OneCell]) {
										Free[player2.ChessMan[i]->originY / OneCell][player2.ChessMan[i]->originX / OneCell] = 1;
										Free[mousey / OneCell][mousex / OneCell] = 0;
										player2.ChessMan[i]->update();
										turn += 1;
										break;
									}
									else {
										for (int j = 0; j < 16; ++j) {
											if (i == j) {
												continue;
											}
											if (player2.ChessMan[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												player2.ChessMan[i]->backToPriviousStep();
												break;
											}
										}
										for (int j = 0; j < 16; ++j) {
											if (player1.ChessMan[j]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												Free[player2.ChessMan[i]->originY / OneCell][player2.ChessMan[i]->originX / OneCell] = 1;
												Free[mousey / OneCell][mousex / OneCell] = 0;
												player2.ChessMan[i]->setPosition(mousex - OneCell / 2, mousey - OneCell / 2);
												player2.ChessMan[i]->update();
												player1.ChessMan[j]->setPosition(-100, -100);
												turn += 1;
												break;
											}
										}
									}
									break;
								}
								else {
									player2.ChessMan[i]->backToPriviousStep();
								}
							}
						}
					}
					break;
				}
				}
			}
			if (this->player1.ChessMan[4]->getPosition() == sf::Vector2f(-100, -100)) {
				return 2;
			}
			else if (this->player2.ChessMan[3]->getPosition() == sf::Vector2f(-100, -100)) {
				return 1;
			}
			for (int i = 8; i < 16; ++i) {
				if (player1.ChessMan[i]->getPosition().y / OneCell == 7 && player1.ChessMan[i]->getChessName() == "Pawn") {
					this->promotePawn(player1.ChessMan[i]);
					break;
				}
				if (player2.ChessMan[i]->getPosition().y / OneCell == 0 && player2.ChessMan[i]->getChessName() == "Pawn") {
					this->promotePawn(player2.ChessMan[i]);
					break;
				}
			}
			window.clear();
			window.draw(background);
			for (int i = 0; i < 16; ++i) {
				this->player1.ChessMan[i]->draw(window);
				this->player2.ChessMan[i]->draw(window);
			}
			window.display();
		}
		return 0;
	}
	void promotePawn(cChessMan *&chessman) {
		sf::RenderWindow window(sf::VideoMode(800, 300), "PROMOTEPAWN");
		sf::Event event;
		sf::Texture texture;
		texture.loadFromFile("Chess2.png");
		texture.setSmooth(true);
		sf::Sprite Car, Knight, Bisopp, Queen;
		Car.setTexture(texture);
		Knight.setTexture(texture);
		Bisopp.setTexture(texture);
		Queen.setTexture(texture);
		int top = 0;
		if (chessman->player == PLAYER2) {
			top = 1;
		}
		Car.setTextureRect(sf::IntRect(0, top * 100, 100, 100));
		Knight.setTextureRect(sf::IntRect(100, top * 100, 100, 100));
		Bisopp.setTextureRect(sf::IntRect(200, top * 100, 100, 100));
		Queen.setTextureRect(sf::IntRect(400, top * 100, 100, 100));
		Car.setPosition(sf::Vector2f(50, 100));
		Knight.setPosition(sf::Vector2f(250, 100));
		Bisopp.setPosition(sf::Vector2f(450, 100));
		Queen.setPosition(sf::Vector2f(650, 100));
		sf::RectangleShape shape[4];
		for (int i = 0; i < 4; ++i) {
			shape[i].setSize(sf::Vector2f(100, 100));
			shape[i].setPosition(sf::Vector2f(50 + 200 * i, 100));
			shape[i].setFillColor(sf::Color::Black);
		}
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case::sf::Event::Closed: {
					window.close();
					break;
				}
				case::sf::Event::MouseButtonPressed: {
					cChessMan * tmp = chessman;
					if (Car.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						chessman = new cCar;					
					}
					else if (Knight.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						chessman = new cKnight;
					}
					else if (Bisopp.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						chessman = new cBisopp;
					}
					else if (Queen.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						chessman = new cQueen;
					}
					else {
						break;
					}
					chessman->player = tmp->player;
					chessman->originX = tmp->originX;
					chessman->originY = tmp->originY;
					chessman->setPosition(tmp->getPosition());
					chessman->setImageChess();
					window.close();
					break;
				}
				}
			}
			int mouseX = sf::Mouse::getPosition(window).x;
			int mouseY = sf::Mouse::getPosition(window).y;
			if (shape[0].getGlobalBounds().contains(mouseX, mouseY)) {
				shape[0].setFillColor(sf::Color::Green);
			}
			else if (shape[1].getGlobalBounds().contains(mouseX, mouseY)) {
				shape[1].setFillColor(sf::Color::Green);
			}
			else if (shape[2].getGlobalBounds().contains(mouseX, mouseY)) {
				shape[2].setFillColor(sf::Color::Green);
			}
			else if (shape[3].getGlobalBounds().contains(mouseX, mouseY)) {
				shape[3].setFillColor(sf::Color::Green);
			}
			else {
				for (int i = 0; i < 4; ++i) {
					shape[i].setFillColor(sf::Color::Black);
				}
			}
			window.clear();
			for (int i = 0; i < 4; ++i) {
				window.draw(shape[i]);
			}
			window.draw(Car);
			window.draw(Knight);
			window.draw(Bisopp);
			window.draw(Queen);
			window.display();
		}
	}
	std::vector<std::string> FillNameTwoPlayer() {
		std::vector<std::string> name;
		sf::RenderWindow window(sf::VideoMode(800, 800), "FILLNAME");
		sf::Event event;
		sf::RectangleShape shape1, shape2;
		shape1.setFillColor(sf::Color::White);
		shape2.setFillColor(sf::Color::White);
		shape1.setSize(sf::Vector2f(300, 45));
		shape2.setSize(sf::Vector2f(300, 45));
		shape1.setPosition(300, 300);
		shape2.setPosition(300, 450);
		sf::Font font;
		font.loadFromFile("AGENCYR.TTF");
		sf::Text text1, text2, text;
		text.setFont(font);
		text1.setFont(font);
		text2.setFont(font);
		text.setCharacterSize(75);
		text1.setCharacterSize(25);
		text2.setCharacterSize(25);
		text.setPosition(200, 150);
		text1.setPosition(300, 270);
		text2.setPosition(300, 420);
		text.setFillColor(sf::Color::White);
		text1.setFillColor(sf::Color::White);
		text2.setFillColor(sf::Color::White);
		text.setString("FILL NAME TO BLANK:");
		text1.setString("PLAYER 1:");
		text2.setString("PLAYER 2:");
		cTextBox textbox1, textbox2;
		textbox1.setLimitCharacter(25);
		textbox2.setLimitCharacter(25);
		
		textbox1.setTextBox(font, 25, sf::Vector2f(300, 300), sf::Color::Red, 1);
		textbox2.setTextBox(font, 25, sf::Vector2f(300, 450), sf::Color::Red, 0);

		sf::RectangleShape nextButton;
		nextButton.setPosition(600, 600);
		nextButton.setFillColor(sf::Color::White);
		nextButton.setSize(sf::Vector2f(150, 100));


		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case::sf::Event::Closed: {
					name.push_back(textbox1.getString());
					name.push_back(textbox2.getString());
					return name;
					window.close();
					break;
				}
				case::sf::Event::TextEntered: {
					if (event.text.unicode == ENTERKEY) {
						if (textbox1.IsSelected == 1) {
							textbox1.IsSelected = 0;
							textbox2.IsSelected = 1;
						}
						else if (textbox2.IsSelected == 1) {
							textbox2.IsSelected = 0;
						}
					}
					if (textbox1.IsSelected == 1)
					{
						textbox1.typeText(event);
					}
					else if (textbox2.IsSelected == 1)
					{
						textbox2.typeText(event);
					}
					break;
				}
				case::sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							window.close();
							return name;
						}
					}
					break;
				}
				}
			}
			window.clear();
			window.draw(shape1);
			window.draw(shape2);
			window.draw(text);
			window.draw(text1);
			window.draw(text2);
			window.draw(nextButton);
			textbox1.draw(window);
			textbox2.draw(window);
			window.display();
		}
	}
	void EndGame(int winner) {
		sf::Text text;
		sf::Font font;
		font.loadFromFile("OCRAEXT.TTF");
		text.setFont(font);
		text.setCharacterSize(75);
		text.setFillColor(sf::Color::White);
		text.setPosition(200, 100);
		if (winner == 1) {
			text.setString("PLAYER1 WIN");
		}
		else if (winner == 2) {
			text.setString("PLAYER2 WIN");
		}

		sf::Text again;
		again.setFont(font);
		again.setCharacterSize(35);
		again.setPosition(300, 500);
		again.setFillColor(sf::Color::Black);
		again.setString("PLAYER AGAIN");
		sf::RectangleShape againBox;
		againBox.setPosition(300, 500);
		againBox.setSize(sf::Vector2f(300, 70));
		againBox.setFillColor(sf::Color::White);

		sf::RenderWindow window(sf::VideoMode(800, 800), "BACK");
		sf::Event event;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case::sf::Event::Closed: {
					window.close();
					break;
				}
				case::sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Left && againBox.getGlobalBounds().contains(event.mouseButton.x,
						event.mouseButton.y)) {
						window.close();
						this->launchGame();
						break;
					}
				}
				}
			}
			window.clear();
			window.draw(text);
			window.draw(againBox);
			window.draw(again);
			window.display();
		}
	}
	void launchGame() {
		BeginWindow beginwindow;
		int option = beginwindow.OpenWindow();
		switch (option) {
		case 0: {
			std::vector<std::string> name = FillNameTwoPlayer();
			int winner = PlayeGame();
			EndGame(winner);
			std::cout << "Anh yeu em" << std::endl;
			std::system("@pause");
			break;
		}
		case 1: {
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		}
		
	}
};


int main()
{
	//BeginWindow a;
	//a.OpenWindow();
	MasterGame game;
	game.launchGame();
	return 0;
}