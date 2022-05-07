//Copyright Sam Collier 2022

#include "Match.h"

std::string Match::getWinner()
{
	std::map<std::string,int> wins;
	for(Set* set : sets)
	{
		wins[set->getWinner()]++;
	}
	
	// return the name of who has the most wins
	return (wins.begin()->second > std::next(wins.begin(),1)->second) ? (wins.begin()->first) : (std::next(wins.begin(),1)->first);
}

int Match::getSetsPlayed()
{
	return sets.size();
}

Match::Match(Player& p1, Player& p2)
	: p1(&p1), p2(&p2)
{
}

void Match::simulate()
{
	srand(msSinceEpoch());
	while(!isMatchOver())
	{
		Set* set = new Set(p1,p2);
		sets.push_back(set);
		set->simulate();
	}
}

bool Match::isMatchOver()
{
	if(sets.size() < 7)
		return false;

	int p1Wins=0,p2Wins=0;
	for(Set* set : sets)
	{
		if(p1->getName() == set->getWinner())
			p1Wins++;
		else if(p2->getName() == set->getWinner())
			p2Wins++;
	}
	std::cout << "\nSETS\n";
	std::cout << p1->getName() << " " << p1Wins << " : " << p2Wins << " " << p2->getName() << '\n';
	return (p1Wins >= 7 || p2Wins >= 7);
}

