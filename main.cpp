#include <iostream>

#include "Player.h"
#include "Match.h"

int main()
{
	Player sid("Sid",50);
	Player joe("Joe",50);

	Match match(joe,sid);
	match.simulate();

	return 0;
}
