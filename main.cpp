#include <iostream>

#include "Player.h"
#include "Match.h"

int main()
{
	Player sid("Sid",50);
	Player joe("Joe",50);

	Set set(&sid,&joe);
	set.simulate();

	/*
	Match match(sid,joe);
	match.simulate();
	*/
	return 0;
}
