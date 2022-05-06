//Copyright Sam Collier 2022

#include "ThreeHundredOneBoard.h"

DartBoard ThreeHundredOneBoard::initializeTargetsAndNeighbors(const std::string& player1, const std::string& player2)
{
	// neighbors are setup for each dartboard child
	// this means that it's very easy to make custom dartboards
	neighbors = new std::vector<std::vector<int>>();
	neighbors->push_back({0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5});
	neighbors->push_back({0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1});
	gameType = GameType::ThreeHundredOne;
	return DartBoard(player1,player2);
}

ThreeHundredOneBoard::ThreeHundredOneBoard(const std::string& player1, const std::string& player2)
	: DartBoard(initializeTargetsAndNeighbors(player1,player2))
{
}

int ThreeHundredOneBoard::placeDart(std::string& playerName, int accuracy, int wantedNumber, Zone zone, Zone* hitZone, ThrowError* error,std::vector<std::pair<int,int>>* throws)
{
	// Random number between 1 and 100 inclusive
	int r = rand() % 100 + 1;

	// 0 means that you've missed the board
	int hitVal = 0;

	// if a bullseye is desired
	if(zone == Zone::Bullseye)
	{
		// a bit harder to hit the bullseye
		if(r <= accuracy - 10)
		{
			hitVal = 50;
		}

		// you're more likely to miss the board completely than hit a target if your successRate is low
		else if(r <= accuracy + accuracy*.5f)
		{
			hitVal = rand() % 20 + 1;
		}
	}
	else
	{
		// you get what you want
		if(r <= accuracy)
		{
			hitVal = wantedNumber;
		}
		// more likely to hit a neighbor if you have high accuracy
		else if(r <= accuracy + .1f * accuracy)
		{
			// coin flip
			bool bGoLeft = rand() % 2;

			// hit left neighbor
			if(bGoLeft)
				hitVal = (*neighbors)[0][wantedNumber];
			else // hit right neighbor
				hitVal = (*neighbors)[1][wantedNumber];
		}
		// you hit a random target on the board
		else if (r <= accuracy + accuracy * .5f)
		{
			hitVal = rand() % 20 + 1;
		}
		// Otherwise player has missed the board entirely and there's nothing to do
	}
	int newScore = getPlayerPoints(playerName) - hitVal;

	// score cannot go below 50. Has to go from 50 to 0 with a bullseye
	if(newScore == 0 && hitVal == 50)
	{
		bGameOver = true;
		winner = playerName;
	}
	// if our new score is above 50, update it
	if(newScore >= 50)
	{
		(*hitList)[playerName][hitVal]++;
	}
	return hitVal;
}

