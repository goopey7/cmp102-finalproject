//Copyright Sam Collier 2022
#pragma once

#include "Game.h"

class Set
{
	public:
		Set(Player* p1, Player* p2);
		void addGame(Game* game);
		std::string getWinner();
		int getGamesPlayed();

		void simulate();
		void play();
		bool isSetOver();
	private:
		std::vector<Game*> games;
		bool bIsSetOver = false;
		Player* p1;
		Player* p2;
		int whoGoesFirst(); // returns 1 for p1 and 2 for p2
};

