#pragma once
#include "TinyEngine.h"
#include "Grid.h"

class Player
{
public:
	Player();
	~Player();

	void Input(int& x, int& y);
	void Draw();
	void Perform(Grid &grid, int x, int y);

	void Move(int x, int y);
	void Destroy(Grid& grid, int x, int y);
	void Eat();
	void Dig();
	void DigGold();
	void Restart();

	int playerX;
	int playerY;
	int energy = 25;
	int gold = 0;

private:
	int speed;
	int startX;
	int startY;
};

