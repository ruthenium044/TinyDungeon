#pragma once
#include "TinyEngine.h"
#include "Grid.h"

class Player
{
public:
	Player();
	Player(int speed, int x, int y);
	~Player();

	void Input(int& x, int& y);
	void Draw();
	void Perform(Grid &grid, int x, int y);

	void Move(int x, int y);
	void Destroy(Grid& grid, int x, int y);
	void Eat();
	void Dig();

	int playerX;
	int playerY;
	int energy = 10;

private:
	int speed;
};

