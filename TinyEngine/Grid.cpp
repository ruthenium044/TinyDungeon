#include "Grid.h"

Grid::Grid()
{
	this->randomFill = 49;
	lifeCycles = 7;
	tileSizeX = 10;
	tileSizeY = 10;

	srand(time(NULL));
	GenerateMap();
}

Grid::Grid(int randomFill, int life, int sizeX, int sizeY)
{
	this->randomFill = randomFill;
	lifeCycles = life;
	tileSizeX = sizeX;
	tileSizeY = sizeY;

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

void Grid::FloodFill(int x, int y, BoolArr2D& visited, std::vector<Coords>& cave)
{
	if (visited[x][y])
	{
		return;
	}
	visited[x][y] = true;

	cave.push_back({ x, y });

	Coords neighbours[4] = { {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1} };
	for (int i = 0; i < 4; i++)
	{
		if (neighbours[i].x == x && neighbours[i].y == y)
		{
			continue;
		}

		if (neighbours[i].x >= 0 && neighbours[i].y >= 0 &&
			neighbours[i].x <= width && neighbours[i].y <= height)
		{
			if (grid[neighbours[i].x][neighbours[i].y] == 0)
			{
				FloodFill(neighbours[i].x, neighbours[i].y, visited, cave);
			}
		}
	}
}	

void Grid::ClearSmallCaves()
{
	bool visited[width][height];

	std::vector<std::vector<Coords>> caves;
	std::vector<Coords> biggestCave;
	int biggestIndex = 0;
	int count = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (!visited[x][y])
			{
				std::vector<Coords> tempCave;
				FloodFill(x, y, visited, tempCave);
				caves.push_back(tempCave);
				count++;
			}

			int currentIndex = count - 1;
			std::vector<Coords> currentCave = caves[currentIndex];
			if (count > 1)
			{
				if (currentCave.size() > biggestCave.size())
				{
					biggestIndex = currentIndex;
					biggestCave = currentCave;
				}
				else
				{
					//grid[currentCave[currentIndex].x][currentCave[currentIndex].y] = 1;
				}
			}
			else
			{
				biggestCave = currentCave;
			}
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
	//ClearSmallCaves();
}

void Grid::DrawMap()
{
	engSetColor(20, 20, 20);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (grid[x][y] == 1)
			{
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
	return x > 0 && x < width&& y > 0 && y < height;
}