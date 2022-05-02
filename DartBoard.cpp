//Copyright Sam Collier 2022

#include "DartBoard.h"

DartBoard::DartBoard(const std::string& player1, const std::string& player2)
{
	hitList = new std::map<std::string,std::map<int,int>>();
	auto hits = *hitList;
	// set all targets hit to 0 (players haven't hit anything)
	for(int i=1; i<(*neighbors)[0].size(); i++)
	{
		hits[player1][(*neighbors)[0][i]] = 0;
		hits[player1][25]=0;
		hits[player1][50]=0;

		hits[player2][(*neighbors)[0][i]] = 0;
		hits[player2][25]=0;
		hits[player2][50]=0;
	}

	// initialize random seed
	srand(time(0));
}
int DartBoard::getPlayerPoints(std::string& playerName)
{
	int total = gameType;
	for(auto target : (*hitList)[playerName])
	{
		total -= target.first * target.second;
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

int DartBoard::placeDart(std::string& playerName, int accuracy, int wantedNumber, Zone zone, std::vector<int>* throws)
{
	return -1;
}

const std::string& DartBoard::getWinner() const
{
	return winner;
}

DartBoard::~DartBoard()
{
	delete neighbors;
	delete hitList;
}

