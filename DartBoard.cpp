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

int DartBoard::getPlayerPoints(std::string& playerName)
{
	int total = gameType;
	for(std::pair<int,int> target : hits[playerName])
	{
		total -= target.second;
	}

	if(total <= 0)
		return 0;

	return total;
}

bool DartBoard::isGameOver() const
{
	return bGameOver;
}

GameType DartBoard::getGameType() const
{
	return gameType;
}

void DartBoard::placeDart(std::string& playerName, int successRate, int ptsWanted)
{
}

