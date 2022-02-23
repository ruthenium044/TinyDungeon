#include "Grid.h"

Grid::Grid()
{
	randomFill = 49;
	lifeCycles = 7;
	tileSizeX = 10;
	tileSizeY = 10;

	srand(time(NULL));
	GenerateMap();
}

Grid::~Grid()
{
}

void Grid::RandomFill()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
			{
				grid[x][y] = 1;
			}
			else
			{
				grid[x][y] = (rand() % 100 + 1 < randomFill) ? 1 : 0;
			}
		}
	}
}

void Grid::RandomFillValue(int layerValue, int tileValue, int fillValue)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (grid[x][y] == layerValue)
			{
				grid[x][y] = (rand() % 100 + 1 < fillValue) ? tileValue : layerValue;
			}
		}
	}
}

void Grid::SmoothMap()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int neighbourWallTiles = GetNeighbourWallCount(x, y);

			if (neighbourWallTiles > 4)
				grid[x][y] = 1;
			else if (neighbourWallTiles < 4)
				grid[x][y] = 0;
		}
	}
}

void Grid::GenerateMap()
{
	RandomFill();
	for (int i = 0; i < lifeCycles; i++)
	{
		SmoothMap();
	}

	RandomFillValue(0, 2, 5);
	RandomFillValue(1, 3, 3);
}

void Grid::DrawMap()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (grid[x][y] == 1)
			{
				engSetColor(20, 20, 20);
				engDrawRect(x * tileSizeX, y * tileSizeY, tileSizeX, tileSizeY);
			}
			else if (grid[x][y] == 2)
			{
				engSetColor(100, 0, 0);
				engDrawRect(x * tileSizeX, y * tileSizeY, tileSizeX, tileSizeY);
			}
			else if (grid[x][y] == 3)
			{
				engSetColor(80, 70, 0);
				engDrawRect(x * tileSizeX, y * tileSizeY, tileSizeX, tileSizeY);
			}
		}
	}
}

int Grid::GetNeighbourWallCount(int gridX, int gridY) //moore
{
	int wallCount = 0;
	for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX++)
	{
		for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY++)
		{
			if (neighbourX >= 0 && neighbourX < width &&
				neighbourY >= 0 && neighbourY < height)
			{
				if (neighbourX != gridX || neighbourY != gridY)
				{
					wallCount += grid[neighbourX][neighbourY];
				}
			}
			else
			{
				wallCount++;
			}
		}
	}
	return wallCount;
}

int Grid::GetTile(int x, int y)
{
	return grid[x / tileSizeX][y / tileSizeY];
}

void Grid::SetTile(int x, int y, int value)
{
	grid[x / tileSizeX][y / tileSizeY] = value;
}

bool Grid::CheckBounds(int x, int y)
{
	x /= tileSizeX;
	y /= tileSizeY;
	return x >= 0 && x < width && y >= 0 && y < height;
}