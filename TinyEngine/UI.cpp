#include "UI.h"
#include "Player.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Draw(int value, int value2)
{
	engDrawStringFormat(520, 20, "Energy: %d", value);
	engDrawStringFormat(520, 60, "Gold: %d", value2);
	if (value <= 0)
	{
		engDrawStringFormat(100, 20, "Ya dead");
	}
	if (value2 >= 10)
	{
		engDrawStringFormat(100, 20, "Ya win");
	}
}
