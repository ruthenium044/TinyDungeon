#pragma once
#include "TinyEngine.h"
#include "Grid.h"
#include "Coords.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

class Grid
{
private:

	static constexpr int width{ 50 };
	static constexpr int height{ 50 };
	using BoolArr2D = bool[width][height];
	int grid[width][height];

	int randomFill;
	int lifeCycles;

public:
	int tileSizeX;
	int tileSizeY;

	Grid();
	Grid(int randomFill, int life, int sizeX, int sizeY);
	~Grid();

	void RandomFill();
	void SmoothMap();
	void FloodFill(int x, int y, BoolArr2D& visited, std::vector<Coords>& cave);
	void ClearSmallCaves();

	void GenerateMap();
	void DrawMap();
	int GetNeighbourWallCount(int gridX, int gridY);

	int GetTile(int x, int y);
	void SetTile(int x, int y, int value);
	bool CheckBounds(int x, int y);
};
