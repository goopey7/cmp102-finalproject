//Copyright Sam Collier 2022

#include "Player.h"

Player::Player(const std::string& name, int accuracy)
	: name(name),successRate(accuracy)
{
}

Player::~Player()
{
}

int Player::throwDart(int desiredPoints, Zone desiredZone, Zone* hitZone, std::vector<std::pair<int,Zone>>* throws, ThrowError* error)
{
	if(throws == nullptr)
		return currentBoard->placeDart(name,successRate,desiredPoints,desiredZone);
	else
		return currentBoard->placeDart(name,successRate,desiredPoints,desiredZone,hitZone,error,throws);
}

void Player::newGame(DartBoard* board)
{
	currentBoard = board;
}

int Player::getPointsInCurrentGame()
{
	return currentBoard->getPlayerPoints(name);
}

const std::string& Player::getName() const
{
	return name;
}

int Player::getAccuracy() const
{
	return successRate;
}

