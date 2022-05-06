#include <iostream>

#include "Player.h"
#include "Game.h"

int main()
{
	Player sid("Sid",50);
	Player joe("Joe",50);
	Game game(&sid,&joe,GameType::FiveHundredOne,0,true);
	game.simulate(GameType::FiveHundredOne);
	return 0;
}
