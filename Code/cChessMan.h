#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

const int OneCell = 100;

enum PLAYER { PLAYER1, PLAYER2 };

class cChessMan
{
protected:
	sf::RectangleShape Chess;	
	sf::Texture * texture;
public:
	PLAYER player;
	int originX;
	int originY;
	virtual bool checkNextMove(bool Free[8][8], bool Confrontation) = 0;
	virtual std::string getChessName() = 0;
	cChessMan() {
		this->player;
		this->originX = 0;
		this->originY = 0;
		this->texture = new sf::Texture;
		this->texture->loadFromFile("Chess.png");
		this->Chess.setTexture(this->texture);
		this->Chess.setSize(sf::Vector2f(OneCell, OneCell));
		this->Chess.setPosition(sf::Vector2f(originX, originY));
	}
	void setPosition(sf::Vector2f pos) {
		this->Chess.setPosition(pos);
	}
	void setPosition(int x, int y) {
		this->Chess.setPosition(x, y);
	}
	sf::FloatRect getGlobalBounds() {
		return this->Chess.getGlobalBounds();
	}
	void draw(sf::RenderWindow &window) {
		window.draw(this->Chess);
	}
	void backToPriviousStep() {
		this->Chess.setPosition(originX, originY);
	}
	void update() {
		this->originX = int((this->Chess.getPosition().x + OneCell / 2) / OneCell) * OneCell;
		this->originY = int((this->Chess.getPosition().y + OneCell / 2) / OneCell) * OneCell;
		this->Chess.setPosition(originX, originY);
	}
	void setFillColor(sf::Color color) {
		this->Chess.setFillColor(color);
	}
	sf::Vector2f getPosition() {
		return this->Chess.getPosition();
	}
	virtual void setImageChess() {}
	void move() {}
};

class cCar : public cChessMan
{
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		if (!Confrontation) {
			return false;
		}
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2) / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2) / OneCell)) - (this->originY / OneCell);
		if (tmpX != 0 && tmpY != 0) {
			return false;
		}
		if (tmpX == 0 && tmpY < 0) {
			int k = -1;
			while (k > tmpY) {
				if (!Free[originY / OneCell + k][originX / OneCell]) {
					return false;
				}
				--k;
			}
		}
		else if (tmpX == 0 && tmpY > 0) {
			int k = 1;
			while (k < tmpY) {
				if (!Free[originY / OneCell + k][originX / OneCell]) {
					return false;
				}
				++k;
			}
		}
		if (tmpY == 0 && tmpX < 0) {
			int k = -1;
			while (k > tmpX) {
				if (!Free[originY / OneCell][originX / OneCell + k]) {
					return false;
				}
				--k;
			}
		}
		else if (tmpY == 0 && tmpX > 0) {
			int k = 1;
			while (k < tmpX) {
				if (!Free[originY / OneCell][originX / OneCell + k]) {
					return false;
				}
				++k;
			}
		}
		return true;
	}
	cCar() : cChessMan() {}
	std::string getChessName() {
		return "Car";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 0, top, size, size));
	}
};

class cKnight : public cChessMan
{
private:
	int dx[8] = { 2, 2, 1, 1, -1, -1, -2, -2 };
	int dy[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		if (!Confrontation) {
			return false;
		}
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2)  / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2)  / OneCell)) - (this->originY / OneCell);
		for (int i = 0; i < 8; ++i) {
			if (tmpX == this->dx[i] && tmpY == this->dy[i]) {
				return true;
			}
		}
		return false;
	}
	cKnight() : cChessMan() {}
	std::string getChessName() {
		return "Knight";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 1, top, size, size));
	}
};

class cBisopp : public cChessMan
{
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		if (!Confrontation) {
			return false;
		}
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2) / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2) / OneCell)) - (this->originY / OneCell);
		
		if (tmpX < 0 && tmpY > 0) {
			int a = -1, b = 1;
			while (a > tmpX && b < tmpY) {
				if (!Free[originY / OneCell + b][originX / OneCell + a]) {
					return false;
				}
				--a; ++b;
			}
		}
		else if (tmpX < 0 && tmpY < 0) {
			int a = -1, b = -1;
			while (a > tmpX && b > tmpY) {
				if (!Free[originY / OneCell + b][originX / OneCell + a]) {
					return false;
				}
				--a; --b;
			}
		}
		else if (tmpX > 0 && tmpY > 0) {
			int a = 1, b = 1;
			while (a < tmpX && b < tmpY) {
				if (!Free[originY / OneCell + b][originX / OneCell + a]) {
					return false;
				}
				++a; ++b;
			}
		}
		else if (tmpX > 0 && tmpY < 0) {
			int a = 1, b = -1;
			while (a < tmpX && b > tmpY) {
				if (!Free[originY / OneCell + b][originX / OneCell + a]) {
					return false;
				}
				++a; --b;
			}
		}
		if (tmpX == tmpY || tmpX == -1 * tmpY) {
			return true;
		}
		return false;
	}
	cBisopp() : cChessMan() {}
	std::string getChessName() {
		return "Bisopp";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 2, top, size, size));
	}
};

class cQueen : public cChessMan
{
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		if (!Confrontation) {
			return false;
		}
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2) / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2) / OneCell)) - (this->originY / OneCell);
		if (tmpX == tmpY || tmpX == -1 * tmpY) {
			if (tmpX < 0 && tmpY > 0) {
				int a = -1, b = 1;
				while (a > tmpX && b < tmpY) {
					if (!Free[originY / OneCell + b][originX / OneCell + a]) {
						return false;
					}
					--a; ++b;
				}
			}
			else if (tmpX < 0 && tmpY < 0) {
				int a = -1, b = -1;
				while (a > tmpX && b > tmpY) {
					if (!Free[originY / OneCell + b][originX / OneCell + a]) {
						return false;
					}
					--a; --b;
				}
			}
			else if (tmpX > 0 && tmpY > 0) {
				int a = 1, b = 1;
				while (a < tmpX && b < tmpY) {
					if (!Free[originY / OneCell + b][originX / OneCell + a]) {
						return false;
					}
					++a; ++b;
				}
			}
			else if (tmpX > 0 && tmpY < 0) {
				int a = 1, b = -1;
				while (a < tmpX && b > tmpY) {
					if (!Free[originY / OneCell + b][originX / OneCell + a]) {
						return false;
					}
					++a; --b;
				}
			}
			if (tmpX == tmpY || tmpX == -1 * tmpY) {
				return true;
			}
		}
		else if (tmpX == 0 || tmpY == 0) {
			if (tmpX == 0 && tmpY < 0) {
				int k = -1;
				while (k > tmpY) {
					if (!Free[originY / OneCell + k][originX / OneCell]) {
						return false;
					}
					--k;
				}
			}
			else if (tmpX == 0 && tmpY > 0) {
				int k = 1;
				while (k < tmpY) {
					if (!Free[originY / OneCell + k][originX / OneCell]) {
						return false;
					}
					++k;
				}
			}
			if (tmpY == 0 && tmpX < 0) {
				int k = -1;
				while (k > tmpX) {
					if (!Free[originY / OneCell][originX / OneCell + k]) {
						return false;
					}
					--k;
				}
			}
			else if (tmpY == 0 && tmpX > 0) {
				int k = 1;
				while (k < tmpX) {
					if (!Free[originY / OneCell][originX / OneCell + k]) {
						return false;
					}
					++k;
				}
			}
		}
		if (tmpX == tmpY || tmpX == -1 * tmpY ||
			(tmpX == 0 && tmpY != 0) || (tmpY == 0 && tmpX != 0)) {
			return true;
		}
		return false;
	}
	cQueen() : cChessMan() {}
	std::string getChessName() {
		return "Queen";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 4, top, size, size));
	}
};

class cKing : public cChessMan
{
private:
	int dy[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
	int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2) / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2) / OneCell)) - (this->originY / OneCell);
		for (int i = 0; i < 8; ++i) {
			if (tmpX == dx[i] && tmpY == dy[i]) {
				return true;
			}
		}
		return false;
	}
	cKing() : cChessMan() {}
	std::string getChessName() {
		return "King";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 3, top, size, size));
	}
};

class cPawn : public cChessMan
{
private:
	int dx[8] = { 1, 0, -1, 0, 0, -1, 0, 1 };
	int dy[8] = { 1, 1, 1, 2, -2, -1, -1, -1 };
public:
	bool checkNextMove(bool Free[8][8], bool Confrontation) {
		if (!Confrontation) {
			return false;
		}
		int tmpX = (int((this->Chess.getPosition().x + OneCell / 2) / OneCell)) - (this->originX / OneCell);
		int tmpY = (int((this->Chess.getPosition().y + OneCell / 2) / OneCell)) - (this->originY / OneCell);
		if (this->player == PLAYER1) {
			if (this->originY / OneCell == 1) {
				if (tmpX == dx[3] && tmpY == dy[3] && Free[originY / OneCell + 1][originX / OneCell]) {
					return true;
				}
			}
			if (tmpX == 1 && tmpY == 1) {
				if (!Free[originY / OneCell + 1][originX / OneCell + 1]) {
					return true;
				}
			}
			else if (tmpX == -1 && tmpY == 1) {
				if (!Free[originY / OneCell + 1][originX / OneCell - 1]) {
					return true;
				}
			}
			else if (tmpX == 0 && tmpY == 1) {
				if (Free[originY / OneCell + 1][originX / OneCell]) {
					return true;
				}
			}
		}
		else if (this->player == PLAYER2) {
			if (this->originY / OneCell == 6) {
				if (tmpX == dx[4] && tmpY == dy[4]) {
					return true;
				}
			}
			if (tmpX == 1 && tmpY == -1) {
				if (!Free[originY / OneCell - 1][originX / OneCell + 1]) {
					return true;
				}
			}
			else if (tmpX == -1 && tmpY == -1) {
				if (!Free[originY / OneCell - 1][originX / OneCell - 1]) {
					return true;
				}
			}
			else if (tmpX == 0 && tmpY == -1) {
				if (Free[originY / OneCell - 1][originX / OneCell]) {
					return true;
				}
			}
		}
		return false;
	}
	cPawn() : cChessMan() {}
	std::string getChessName() {
		return "Pawn";
	}
	void setImageChess() {
		int top = this->texture->getSize().y * 0;
		if (this->player == PLAYER2) {
			top = this->texture->getSize().y / 2;
		}
		int size = 56;
		this->Chess.setTextureRect(sf::IntRect(size * 5, top, size, size));
	}
};