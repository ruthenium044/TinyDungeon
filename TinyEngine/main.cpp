#include "TinyEngine.h"
#include "Grid.h"
#include "Player.h"

int main()
{
	// Initialize the engine and open up a window
	engInit();

	Grid grid{49, 6, 10, 10};
	Player player{ grid.tileSizeX, 70, 70 };

	bool running = true;
	int inputX, inputY;

	while (running)
	{
		engUpdate();

		if (engGetKeyDown(Key::Escape))
		{
			running = false;
		}
			
		inputX = player.playerX;
		inputY = player.playerY;
		player.Input(inputX, inputY);
		player.Perform(grid);

		//regenerate map
		if (engGetKeyDown(Key::Space))
		{
			grid.GenerateMap();
		}
		
		grid.DrawMap();
		player.Draw();
	}
	
	// Don't quit right away
	//engWaitKey();

	// Make a clean exit
	engDestroy();
	return 0;
}


