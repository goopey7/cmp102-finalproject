//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <vector>

#include "DartBoard.h"

class Player
{
	public:
		Player(const std::string& name, int accuracy);
		~Player();

		int throwDart(int desiredPoints, Zone desiredZone, Zone* hitZone = nullptr, std::vector<std::pair<int,Zone>>* throws = nullptr, ThrowError* error = nullptr);
		int getPointsInCurrentGame();
		void newGame(DartBoard* board);
		const std::string& getName() const;
		int getAccuracy() const;

	private:
		std::string name;
		int successRate;
		DartBoard* currentBoard = nullptr;
};

