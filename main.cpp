#include <iostream>

#include "Player.h"
#include "Game.h"

int main()
{
	Player sid("Sid",70);
	Player joe("Joe",60);
	Game game(&sid,&joe,GameType::ThreeHundredOne,0,true);
	game.play();
	return 0;
}
