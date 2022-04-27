//Copyright Sam Collier 2022

#include "DartBoard.h"

DartBoard::DartBoard(const std::string& player1, const std::string& player2)
{
	// set all targets hit to 0 (players haven't hit anything)
	for(int i=0; i<targets.size(); i++)
	{
		hits[player1][targets[i]] = 0;
		hits[player1][25]=0;
		hits[player1][50]=0;

		hits[player2][targets[i]] = 0;
		hits[player2][25]=0;
		hits[player2][50]=0;

	}

	// initialize random seed
	srand(time(0));
}

void DartBoard::placeDart(std::string& playerName, int successRate, int ptsWanted)
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
		else if (r <= successRate + 10)
		{
			hitVal = 50;
		}
		else
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
		// you hit a neighbor
		else if(r <= successRate + 10)
		{
			// coin flip
			bool bIsHeads = rand() % 2;

			// hit left neighbor
			if(bIsHeads)
				hitVal = neighbors[0][ptsWanted];
			else // hit right neighbor
				hitVal = neighbors[1][ptsWanted];
		}
		// you hit a random target on the board
		else if (r <= successRate + 15)
		{
			hitVal = rand() % 20 + 1;
		}
		// Otherwise player has missed the board entirely and there's nothing to do
	}
	
	int newScore = getPlayerPoints(playerName) - hitVal;
	if(newScore > 50 || newScore == 0)
	{
		hits[playerName][hitVal]++;
		if(newScore == 0)
			bGameOver = false;
	}
}

int DartBoard::getPlayerPoints(std::string& playerName)
{
	int total = 301;
	for(std::pair<int,int> target : hits[playerName])
	{
		total -= target.second;
	}
	return total;
}

