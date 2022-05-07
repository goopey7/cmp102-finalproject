//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "ThreeHundredOneBoard.h"
#include "FiveHundredOneBoard.h"

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

		std::string getWinner();

	private:
		std::pair<Player*, Player*> players;
		std::map<std::string,int> points;
		std::string winner;
		int id;
		GameType gameType;
		DartBoard* board;
		bool bP1First = true;
		std::string zoneToString(Zone zoneIn);
};

