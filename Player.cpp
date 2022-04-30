//Copyright Sam Collier 2022

#include "Player.h"

Player::Player(const std::string& name, int accuracy)
	: name(name),successRate(accuracy)
{
}

Player::~Player()
{
}

int Player::throwDart(int desiredPoints, Zone desiredZone)
{
	return currentBoard->placeDart(name,successRate,desiredPoints);
}

void Player::newGame(DartBoard* board)
{
	currentBoard = board;
	boardsPlayed.push_back(currentBoard);
}

int Player::getWins()
{
	int wins = 0;
	for(DartBoard* board : boardsPlayed)
	{
		if(board->getWinner() == name)
		{
			wins++;
		}
	}
	return wins;
}

int Player::getPointsInCurrentGame()
{
	return currentBoard->getPlayerPoints(name);
}

const std::string& Player::getName() const
{
	return name;
}

