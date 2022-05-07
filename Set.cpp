//Copyright Sam Collier 2022

#include "Set.h"

void Set::addGame(Game* game)
{
	games.push_back(game);
}

std::string Set::getWinner()
{
	std::map<std::string,int> wins;
	for(Game* game : games)
	{
		wins[game->getWinner()]++;
	}
	
	// return the name of who has the most wins
	if(wins.begin()->second >= std::next(wins.begin())->second || wins.size() == 1)
		return wins.begin()->first;
	else
		return std::next(wins.begin())->first;
}

int Set::getGamesPlayed()
{
	return games.size();
}

void Set::simulate()
{
	// Determine who goes first for the set
	int first = whoGoesFirst();
	bool p1GoesFirstThisGame = (first == 1);
	while(!isSetOver())
	{
		srand(msSinceEpoch());
		Game* game = new Game(p1,p2,FiveHundredOne,p1GoesFirstThisGame);
		games.push_back(game);
		game->simulate();
		p1GoesFirstThisGame = !p1GoesFirstThisGame;
	}
}

void Set::play()
{
	// Determine who goes first for the set
	int first = whoGoesFirst();
	bool p1GoesFirstThisGame = (first == 1);
	while(!isSetOver())
	{
		srand(msSinceEpoch());
		Game* game = new Game(p1,p2,FiveHundredOne,p1GoesFirstThisGame);
		games.push_back(game);
		game->play();
		p1GoesFirstThisGame = !p1GoesFirstThisGame;
	}
}

Set::Set(Player* p1, Player* p2)
	: p1(p1), p2(p2)
{
}

bool Set::isSetOver()
{
	if(games.size() < 3)
		return false;

	int p1Wins=0,p2Wins=0;
	for(Game* game : games)
	{
		if(p1->getName() == game->getWinner())
			p1Wins++;
		else if(p2->getName() == game->getWinner())
			p2Wins++;
	}
	std::cout << "\n" << p1->getName() << " " << p1Wins << " : " << p2Wins << " " << p2->getName() << '\n';
	return (p1Wins >= 3 || p2Wins >= 3);
}

int Set::whoGoesFirst()
{
	// Both players go for bullseye
	FiveHundredOneBoard board(p1->getName(),p2->getName());
	Zone* hitZone1 = new Zone();
	Zone* hitZone2 = new Zone();
	int p1Hit = board.placeDart(p1->getName(),p1->getAccuracy(),50,Zone::Bullseye,hitZone1);
	int p2Hit = board.placeDart(p2->getName(),p2->getAccuracy(),50,Zone::Bullseye,hitZone2);
	if(abs(50 - (p1Hit*(*hitZone1))) < abs(50 - (p2Hit*(*hitZone2))))
		return 1;
	else
		return 2;
}

