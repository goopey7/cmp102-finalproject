//Copyright Sam Collier 2022

#include "FiveHundredOneBoard.h"

#include <iostream>

DartBoard FiveHundredOneBoard::initializeTargetsAndNeighbors(const std::string& player1, const std::string& player2)
{
	// neighbors are setup for each dartboard child
	// this means that it's very easy to make custom dartboards
	neighbors = new std::vector<std::vector<int>>();
	neighbors->push_back({0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5});
	neighbors->push_back({0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1});
	gameType = GameType::FiveHundredOne;
	return DartBoard(player1,player2);
}

FiveHundredOneBoard::FiveHundredOneBoard(const std::string& player1, const std::string& player2)
	: DartBoard(initializeTargetsAndNeighbors(player1,player2))
{
}

int FiveHundredOneBoard::placeDart(const std::string& playerName, int accuracy, int wantedNumber, Zone zone, Zone* hitZone,ThrowError* error,std::vector<std::pair<int,Zone>>* throws)
{
	if(error!=nullptr)
		*error = ThrowError::None;
	// Random number between 1 and 100 inclusive
	int r = rand() % 100 + 1;

	// 0 means that you've missed the board
	int hitVal = 0;

	// if a bullseye is desired
	if(zone <= 0) // Bullseye = 0, OuterBullseye = -1
	{
		// a bit harder to hit the bullseye
		int bullseyeCheck = accuracy - 10;
		if(accuracy < 15)
			bullseyeCheck = accuracy - accuracy*.5f;
		if(r <= bullseyeCheck)
		{
			if(zone == Zone::Bullseye)
				hitVal = 50; // hit inner bullseye
			else
				hitVal = 25; // hit outer bullseye
		}
		else if(r <= bullseyeCheck + 10) // small chance to hit other bullseye
		{
			// have missed our bullseye but hit other bullseye instead
			if(zone == Zone::Bullseye)
				hitVal = 25;
			else
				hitVal = 50;
		}

		// you're more likely to miss the board completely than hit a target if your successRate is low
		else if(r <= accuracy + accuracy*.5f)
		{
			Zone newZone = Zone::Single;
			int oneInTen = rand() % 10;

			if(oneInTen == 0)
				newZone = Zone::Double;
			else if(oneInTen == 1)
				newZone = Zone::Treble;

			hitVal = (rand() % 20 + 1);
			zone = newZone;
		}
	}
	else
	{
		// you get what you want
		if(r <= accuracy)
		{
			hitVal = wantedNumber;
		}
		// more likely to hit a neighbor if you have high accuracy
		else if(r <= accuracy + .1f * accuracy)
		{
			bool bOffVertical, bOffHorizontal;

			// if you were going for a single, I think it's pretty unlikely to accidentally hit
			// a double or treble
			if(zone == Zone::Single)
				bOffVertical = (rand() % 10) == 0; 
			else
				bOffVertical = rand() % 2; // but it's pretty easy to miss a treble or a double 

			bOffHorizontal = (rand() % 3 == 0); // one in three chance of being off horizontal
			// as in, you've missed the number you were going for

			// provide a new zone that is not the desired zone
			Zone newZone = zone;
			int newNumber = wantedNumber;
			if(bOffVertical)
			{
				// if you missed your treble or double
				if(zone != Zone::Single)
				{
					// one in ten times go for the other special ring
					// nine in ten times go for a single
					newZone = (rand() % 10 == 0) ? ((zone == Zone::Double) ? Zone::Treble : Zone::Double) : Zone::Single;
				}
				else
				{
					int oneInTen = rand() % 10;
					if(oneInTen == 0)
						newZone = Zone::Treble;
					else if(oneInTen == 1)
						newZone = Zone::Double;
				}
			}

			if(bOffHorizontal)
			{
				// hit a different number
				bool bGoLeft = rand() % 2;

				// hit left neighbor
				if(bGoLeft)
					newNumber = (*neighbors)[0][wantedNumber];
				else // hit right neighbor
					newNumber = (*neighbors)[1][wantedNumber];
			}
			hitVal = newNumber;
			zone = newZone;
		}
		// you hit a random target on the board
		else if (r <= accuracy + accuracy * .5f)
		{
			// one in ten chance of getting either a treble or a double
			Zone newZone = (rand() % 10 == 0) ? ((rand() % 2) ? Zone::Treble : Zone::Double) : Zone::Single;
			hitVal = (rand() % 20 + 1);
			zone = newZone;
		}
		// Otherwise player has missed the board entirely and there's nothing to do
	}

	int hitValMultiplier = 1;
	if(zone != Zone::Bullseye && zone != Zone::OuterBullseye)
		hitValMultiplier = zone;

	int newScore = getPlayerPoints(playerName) - hitVal*hitValMultiplier;
	if(hitZone != nullptr)
		*hitZone = zone;
	(*hitList)[playerName][std::make_pair(hitVal,zone)]++;

	if(error != nullptr)
	{
		if(newScore == 0 && zone != Zone::Double && zone != Zone::Bullseye)
		{
			*error = ThrowError::NotEndOnDouble;
		}
		else if(newScore < 0)
		{
			*error = ThrowError::SurpassedZero; // indicates that player has gone past zero points, so doesn't count
		}
		else if(newScore == 1)
		{
			*error = ThrowError::ImpossibleToFinish; // indicates that player has not scored a double at the end
		}

		// if score has hit zero and player scored a double or bullseye
		if(newScore == 0 && *error == ThrowError::None)
		{
			bGameOver = true;
			winner = playerName;
		}
	}

	if(throws != nullptr)
		throws->push_back(std::make_pair(hitVal,zone));

	return hitVal;
}

