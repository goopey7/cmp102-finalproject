//Copyright Sam Collier 2022

#include "DartBoard.h"
#include <iostream>

DartBoard::DartBoard(const std::string& player1, const std::string& player2)
{
	hitList = new std::map<std::string,std::map<std::pair<int,Zone>,int>>();
	auto hits = *hitList;

	// initialize random seed
	srand(time(0));
}
int DartBoard::getPlayerPoints(const std::string& playerName)
{
	int total = gameType;
	for(std::pair<std::pair<int,Zone>,int> target : (*hitList)[playerName])
	{
		if(target.first.second != Zone::OuterBullseye && target.first.second != Zone::Bullseye)
			// Zone * value * amount of hits
			total -= target.first.first * target.first.second * target.second;
		else
		{
			// value * amount of hits
			total -= target.first.first * target.second;
		}
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

int DartBoard::placeDart(const std::string& playerName, int accuracy, int wantedNumber, Zone zone, Zone* hitZone,ThrowError* error,std::vector<std::pair<int,Zone>>* throws)
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

std::vector<std::vector<int>>* DartBoard::getNeighbors() const
{
	return neighbors;
}

int DartBoard::getClosestTarget(int numToCheck) const
{
	int bestNum = INT32_MAX;
	int bestNumDiff = INT32_MAX;
	for(int i=1;i<neighbors->at(0).size();i++)
	{
		int targetNum = (*neighbors)[0][i];
		int difference = abs(numToCheck - targetNum);

		if(difference == 0)
			return targetNum;

		if(difference < bestNumDiff)
			bestNum = targetNum;
	}
	return bestNum;
}

void DartBoard::undoLastThreeThrows(const std::string& playerName,std::vector<std::pair<int,Zone>>* throws)
{
	for(std::pair<int,Zone> dart : *throws)
	{
		(*hitList)[playerName][dart]--;
	}
}

bool DartBoard::isTarget(int target) const
{
	for(int neighbor : (*neighbors)[0])
	{
		if(neighbor == target)
			return true;
	}
	return false;
}

