//Copyright Sam Collier 2022
#pragma once

#include "DartBoard.h"



class FiveHundredOneBoard : public DartBoard
{

public:
		DartBoard initializeTargetsAndNeighbors(const std::string& player1, const std::string& player2);
		FiveHundredOneBoard(const std::string& player1, const std::string& player2);
		virtual int placeDart(const std::string& playerName, int successRate, int ptsWanted, Zone zone = Zone::Single, Zone* hitZone = nullptr, ThrowError* error = nullptr, std::vector<std::pair<int,Zone>>* throws = nullptr) override;
};

