//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <map>
#include <vector>

class DartBoard
{
	public:
		DartBoard(const std::string& player1, const std::string& player2);
		~DartBoard();

		void placeDart(std::string& playerName, int successRate, int ptsWanted);
		int getPlayerPoints(std::string& playerName);
		int getNumTargets();
		bool isGameOver();

	private:
		std::vector<std::vector<int>> neighbors = {
			{0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			{0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1}};

		std::vector<int> targets = {20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5};
		std::map<std::string,std::map<int,int>> hits;
		bool bGameOver = false;;
};

