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
	return (wins.begin()->second > std::next(wins.begin(),1)->second) ? (wins.begin()->first) : (std::next(wins.begin(),1)->first);
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
	while(!checkIsSetOver())
	{
		Game* game = new Game(p1,p2,FiveHundredOne,0,p1GoesFirstThisGame);
		games.push_back(game);
		game->simulate();
		p1GoesFirstThisGame = !p1GoesFirstThisGame;
	}
}

bool Set::isSetOver()
{
	return bIsSetOver;
}

Set::Set(Player* p1, Player* p2) : p1(p1), p2(p2) {
}

bool Set::checkIsSetOver()
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
	return 1;
}

