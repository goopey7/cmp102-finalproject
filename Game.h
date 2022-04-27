//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "ThreeHundredOneBoard.h"
#include "Player.h"

class Game
{
	public:
		Game(Player* p1, Player* p2, GameType type, int id, bool p1First);
		~Game();

		const std::string& getWinner() const;
		int getID() const;
		DartBoard* getBoard() const;

		void simulate();
		void play();

	private:
		std::pair<Player*, Player*> players;
		std::map<std::string,int> points;
		std::string winner;
		int id;
		DartBoard* board;
		bool bP1First = true;
};

