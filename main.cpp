#include <iostream>

#include "Player.h"
#include "Game.h"

int main()
{
	Player sid("Sid",50);
	Player joe("Joe",50);
	Game game(&sid,&joe,GameType::ThreeHundredOne,0,true);
	game.simulate(GameType::ThreeHundredOne);
	return 0;
}
