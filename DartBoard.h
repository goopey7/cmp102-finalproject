//Copyright Sam Collier 2022
#pragma once
#include <string>
#include <map>
#include <vector>

#include "GameType.h"

enum Zone
{
	OuterBullseye=-1,
	Bullseye=0,
	Single=1,
	Double=2,
	Treble=3,
};

enum ThrowError
{
	None,
	SurpassedZero,
	NotEndOnDouble,
	ImpossibleToFinish,
};

class DartBoard
{
	public:
		DartBoard(const std::string& player1, const std::string& player2);
		~DartBoard();

		virtual int placeDart(std::string& playerName, int accuracy, int ptsWanted, Zone zone = Zone::Single, Zone* hitZone = nullptr,ThrowError* error = nullptr,std::vector<int>* throws = nullptr);
		void undoLastThreeThrows(const std::string& playerName,std::vector<int>* throws);
		
		int getPlayerPoints(std::string& playerName);
		bool isGameOver() const;
		GameType getGameType() const;
		const std::string& getWinner() const;
		std::vector<std::vector<int>>* getNeighbors() const;
		int getClosestTarget(int numToCheck) const;

	protected:
		GameType gameType;
		std::vector<std::vector<int>>* neighbors;
		std::map<std::string,std::map<int,int>>* hitList;
		bool bGameOver = false;
		std::string winner;
};

