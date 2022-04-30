//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <map>
#include <vector>

#include "GameType.h"

enum Zone
{
	Bullseye=0,
	Single=1,
	Double=2,
	Treble=3
};

class DartBoard
{
	public:
		DartBoard(const std::string& player1, const std::string& player2);
		~DartBoard() = default;

		virtual int placeDart(std::string& playerName, int accuracy, int ptsWanted, Zone zone = Zone::Single);
		
		int getPlayerPoints(std::string& playerName);
		bool isGameOver() const;
		GameType getGameType() const;
		const std::string& getWinner() const;

	protected:
		GameType gameType;
		std::vector<std::vector<int>>* neighbors;
		std::map<std::string,std::map<int,int>>* hitList;
		bool bGameOver = false;
		std::string winner;
};

