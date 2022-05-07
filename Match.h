//Copyright Sam Collier 2022
#pragma once

#include "Set.h"

class Match
{
	public:
		Match(Player& p1, Player& p2);
		void play();
		void simulate();
		std::string getWinner();
		int getSetsPlayed();
		bool isMatchOver();

	private:
		std::vector<Set*> sets;
		Player* p1;
		Player* p2;
};

