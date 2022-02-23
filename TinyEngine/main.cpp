#include "TinyEngine.h"
#include "Grid.h"
#include "Player.h"
#include "UI.h"

int main()
{
	// Initialize the engine and open up a window
	engInit();

	Grid grid{};
	Player player{};
	UI ui{};

	bool running = true;
	int inputX, inputY;

	int timerInitial = 600;
	int timer = timerInitial;

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
		player.Perform(grid, inputX, inputY);

		if (player.energy <= 0)
		{
			if (timer <= 0)
			{
				grid.GenerateMap();
				player.Restart();
				timer = timerInitial;
			}
			else
			{
				timer -= engDelta();
			}
		}
		
		grid.DrawMap();
		player.Draw();
		ui.Draw(player.energy, player.gold);
	}
	
	// Don't quit right away
	//engWaitKey();

	// Make a clean exit
	engDestroy();
	return 0;
}


