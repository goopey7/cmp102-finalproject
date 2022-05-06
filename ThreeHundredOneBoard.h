//Copyright Sam Collier 2022
#pragma once

#include "DartBoard.h"

class ThreeHundredOneBoard : public DartBoard
{
	public:
		DartBoard initializeTargetsAndNeighbors(const std::string& player1, const std::string& player2);
		ThreeHundredOneBoard(const std::string& player1, const std::string& player2);

		virtual int placeDart(std::string& playerName, int successRate, int ptsWanted, Zone zone = Zone::Single, Zone* hitZone = nullptr, ThrowError* erorr = nullptr,std::vector<std::pair<int,Zone>>* throws = nullptr) override;
};

