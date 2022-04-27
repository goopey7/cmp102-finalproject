//Copyright Sam Collier 2022

#include "ThreeHundredOneBoard.h"

DartBoard ThreeHundredOneBoard::initializeTargetsAndNeighbors(const std::string& player1, const std::string& player2)
{
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

ThreeHundredOneBoard::~ThreeHundredOneBoard()
{
}

int ThreeHundredOneBoard::placeDart(std::string& playerName, int successRate, int ptsWanted)
{
	int r = rand() % 100 + 1;

	int hitVal = 0;

	// if a bullseye is desired
	if(ptsWanted == 25)
	{
		if(r <= successRate - 10)
		{
			hitVal = ptsWanted;
		}
		// you're more likely to miss completely if your successRate is low
		else if(r <= successRate + successRate*.5f)
		{
			hitVal = rand() % 20 + 1;
		}
	}
	else
	{
		// you get what you want
		if(r <= successRate)
		{
			hitVal = ptsWanted;
		}
		// more likely to hit a neighbor if you have high accuracy
		else if(r <= successRate + .1f * successRate)
		{
			// coin flip
			bool bIsHeads = rand() % 2;

			// hit left neighbor
			if(bIsHeads)
				hitVal = (*neighbors)[0][ptsWanted];
			else // hit right neighbor
				hitVal = (*neighbors)[1][ptsWanted];
		}
		// you hit a random target on the board
		else if (r <= successRate + successRate * .5f)
		{
			hitVal = rand() % 20 + 1;
		}
		// Otherwise player has missed the board entirely and there's nothing to do
	}
	int newScore = getPlayerPoints(playerName) - hitVal;
	if(newScore == 0)
	{
		bGameOver = true;
		winner = playerName;
	}
	if(newScore >= 0)
	{
		(*hitList)[playerName][hitVal]++;
	}
	return hitVal;
}

