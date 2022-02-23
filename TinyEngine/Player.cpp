#include "Player.h"

Player::Player()
{
	playerX = 70;
	playerY = 70;
	this->speed = 10;
}

Player::Player(int speed, int x, int y)
{
	playerX = x;
	playerY = y;
	this->speed = speed;
}

Player::~Player()
{
}

void Player::Input(int& x, int& y)
{
	if (engGetKeyDown(Key::W))
	{
		y -= speed;
	}
	else if (engGetKeyDown(Key::S))
	{
		y += speed;
	}
	else if (engGetKeyDown(Key::A))
	{
		x -= speed;
	}
	else if (engGetKeyDown(Key::D))
	{
		x += speed;
	}
}

void Player::Draw()
{
	engSetColor(0, 255, 0);
	engDrawRect(playerX, playerY, 10, 10);
}

void Player::Perform(Grid &grid, int x, int y)
{
	if (grid.CheckBounds(x, y))
	{
		if (grid.GetTile(x, y) == 0)
		{
			Move(x, y);
		}
		else if (grid.GetTile(x, y) == 1)
		{
			Destroy(grid, x, y);
			Dig();
		}
		else if (grid.GetTile(x, y) == 1)
		{
			Move(x, y);
			Destroy(grid, x, y);
			Eat();
		}
	}
}

void Player::Move(int x, int y)
{
	playerX = x;
	playerY = y;
}

void Player::Destroy(Grid &grid, int x, int y)
{
	grid.SetTile(x, y, 0);
}

void Player::Eat()
{
	energy++;
}

void Player::Dig()
{
	energy--;
}
